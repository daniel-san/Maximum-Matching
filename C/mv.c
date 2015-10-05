/** 
 * File with the implementation of Micali and Vazirani algorithm 
 * to find a maximum matching in a given graph. It is the fastest 
 * known algorithm for finding a maximum matching.
 */
#include <stdlib.h>
#include <time.h>
#include "mv.h"

/**
 * Destroy a list, such that each element in the list stores 
 * a pointer to another list.
 *
 * @param[in] l The list of lists to be destroyed
 */
void
destroy_list_of_lists (List *l)
{
    Element *el;
    for (el = l->head; el != NULL; el = el->next)
    {
        list_destroy ((List *) el->data);
    }
}

/**
 * Set some vertex attributes to default values.
 *
 * @param[in] v The vertex to be initialized
 */
void
initialize_vertex (Vertex *v)
{
    v->evenlevel = v->oddlevel = INFINITY;
    v->bloom = -1;
    list_destroy (v->predecessors);
    list_destroy (v->successors);
    list_destroy (v->anomalies);

    v->predecessors = list_create();
    v->successors = list_create();
    v->anomalies = list_create();
    
    v->count = 0;
    v->status = UNERASED;
    v->visited = UNVISITED;
    v->side = -1;

}


/**
 * Returns the Level of v, such that:
 * Level(v) = min{Oddlevel(v), Evenlevel(v)}.
 *
 * @param[in] v The vertex which we want to get the level of
 * @param[out] The Level of the input vertex
 */
int 
vertex_level (Vertex *v)
{
    if (v->evenlevel < v->oddlevel)
        return v->evenlevel;
    return v->oddlevel;
}

/*
 * Set some edge attributes to default values
 *
 * @param[in] e The edge to be initialized
 */
void
initialize_edge (Edge *e)
{
    e->used = UNUSED;
    e->visited = UNVISITED;
}

/**
 * Reverse the status of an edge from Matched to Unmatched.
 * This function is used to increase the matching along a 
 * augmenting path.
 *
 * @param[in] e The edge to be reversed
 */
void
reverse_edge (Edge *e)
{
    if (e->matched == MATCHED)
        e->matched = UNMATCHED;
    else
        e->matched = MATCHED;
}

/*
 * Returns a list containing the free edges of a graph G.
 *
 * @param[in] G The graph used to find the free edges
 * @param[out] A list containing the edges that are free
 */
List * 
get_free_edges (Graph *G)
{
    int i;
    List *free_edges = list_create();
    for (i = 0; i < G->edge_n; i++)
    {
        if (G->e[i].matched != MATCHED)
        {
            list_add (free_edges, (void*) &G->e[i]);
        }
    }

    return free_edges;
}

/*
 * Returns a list containing the exposed vertices of a graph G.
 * 
 * @param[in] G The graph used to find the exposed vertices
 * @param[out] A list containing the vertices that are exposed
 */
List * 
get_exposed_vertices (Graph *G)
{
    int i;
    List *exposed_vertices = list_create();
    for (i = 0; i < G->vertex_n; i++)
    {
        if (G->v[i].matched != MATCHED)
        {
            list_add (exposed_vertices, (void*) &G->v[i]);
        }
    }

    return exposed_vertices;
}


/*
 * Function to used to setup a initial matching from the given graph.
 *
 * @param[in] G The graph to get the initial matching
 * @param[out] A list containing the initial set of matched edges
 */
List *
initial_matching (Graph *G)
{

    srand(time(NULL));
    
    List *M = list_create ();
    int n;
    int i;
    Edge *e;

    n = rand () % G->edge_n;
    /*
     * TODO: Create a function to add the edge to the matching list, 
     *       and set its vertices matched label to MATCHED.
     */
    e = &G->e[n];
    e->v1->matched = e->v2->matched = MATCHED;
    e->matched = MATCHED;
    e->v1->mate = e->v2;
    e->v2->mate = e->v1;
    e->v1->matched_edge = e;
    e->v2->matched_edge = e;
    
    list_add (M, (void *) e);
    
    for (i = 0; i < n; i++)
    {
        n = rand () % G->edge_n;
        e = &G->e[n];
        //verifying if one of the vertices of the selected edge is already matched
        if ( (e->v1->matched == UNMATCHED) && (e->v2->matched == UNMATCHED) )
        {
            //if both vertices are not matched, add e to M
            e->v1->matched = e->v2->matched = MATCHED;
            e->matched = MATCHED;
            e->v1->mate = e->v2;
            e->v2->mate = e->v1;
            e->v1->matched_edge = e;
            e->v2->matched_edge = e;
            list_add (M, (void *) e);
        }
    }

    return M;
}

/**
 * Creates a bloom. It's called by bloss-aug in case
 * the leftdfs discover a bloom.
 *
 * @param[in] G The graph whose matching is being augmented
 * @param[in] bridge The edge used to start the double DFS process
 * @param[in] phase The number of the current execution phase
 * @param[in] candidates The list of candidates
 * @param[in] bridges The list of bridges
 * @param[in] bloom_vertices A list that contain vertices that were marked 'left'
 *                           or 'right' during the DFS and are used to create 
 *                           a new bloom.
 * @param[in] DCV The Deepes Common Vertex found during the DFS process
 */
void
bloom_create (Graph *G, Edge* bridge, int phase,
              List *candidates, List *bridges,
              List *bloom_vertices, Vertex *DCV)
{
    int j;
    Element *el, *el_1;
    Vertex *z, *y;
    Edge *y_z;
    Bloom *B = malloc (sizeof (Bloom));

    DCV->side = -1; //undefining the side mark
    B->vertices = bloom_vertices; //vertices marked left or right during bloss_aug
    B->id = G->blooms->queue_size;
    B->left_peak = bridge->v1;//s
    B->right_peak = bridge->v2; //t
    B->base = DCV;

    for (el = B->vertices->head; el != NULL; el = el->next)
    {
        y = (Vertex *) el->data;
        y->bloom = B->id;

        if (vertex_level (y) % 2 == 0)//if y is outer
            y->oddlevel = 2 * phase + 1 - y->evenlevel;
        else //if y is inner
        {
            y->evenlevel = 2 * phase + 1 - y->oddlevel;
            list_add ((List *) list_n_get (candidates, y->evenlevel)->data,
                         (void *) y);
            for (el_1 = y->anomalies->head; el_1 != NULL; el_1 = el_1->next)
            {
                z = (Vertex *) el_1->data;
                j = (y->evenlevel + z->evenlevel)/2;
                //mark the edge (y,z) used and add it to bridges(j)
                y_z = get_edge_by_vertices (G, y, z);
                list_add ((List *) list_n_get (bridges, j)->data, (void *) y_z);
                y_z->used = USED;
            }
        }
    }
}

/**
 * Change the status of a list of vertices to ERASED.
 *
 * @param[in] Y A list of vertices to be marked as ERASED
 */
void
erase (List *Y)
{
    Vertex *y, *z;
    Element *el, *el_1;
    for (el = Y->head; el != NULL; el = el->next)
    {
        y = (Vertex *) el->data;
        y->status = ERASED;
        for (el_1 = y->successors->head; el_1 != NULL; el_1 = el_1->next)
        {
            z = (Vertex *) el_1->data;
            if (z->status == UNERASED)
            {
                z->count--;
                if (z->count == 0)
                    list_add (Y, (void *) z);
            }
        }
    }
}

/**
 * Computes the base* of a vertex.
 *
 * @param[in] v The vertex which the base* have to be found
 * @param[in] blooms A queue containing the blooms created up to this point
 * @param[out] The vertex that is the base* of v
 */
Vertex *
base_p (Vertex *v, Queue* blooms)
{
    Vertex *base;
    Bloom *b;
    if (v->bloom == -1)
        return v;
    b = (Bloom *) queue_n_get(blooms, v->bloom)->data;
    base = b->base;

    return base_p (base, blooms);
}

/**
 * Find an alternating path from x through Bloom(x) to base(Bloom(x))
 * 
 * @param[in] G The graph whose matching is being augmented
 * @param[in] x A vertex used to find an alternating path from it to 
 *              the base of the bloom it belongs
 * @param[out] A queue that contains the vertices forming the path found
 */
Queue *
open (Graph *G, Vertex *x)
{
    Element *el;
    Queue *path, *path_half1, *path_half2;
    Vertex *b;
    Bloom *B;

    B = (Bloom *) queue_n_get (G->blooms, x->bloom)->data;
    b = B->base;

    //x is outer
    if (vertex_level (x) % 2 == 0)
    {
        path = findpath (G, x, b, B);
        return path;
    }
    //x is inner
    else
    {
        if (x->side == LEFT)
        {
            path_half1 = findpath (G, B->left_peak, x, B);
            path_half2 = findpath (G, B->right_peak, b, B);
        }
        else if (x->side == RIGHT)
        {
            path_half1 = findpath (G, B->right_peak, x, B);
            path_half2 = findpath (G, B->left_peak, b, B);
        }

        path = queue_create();

        //joining path and path_half1
        el = queue_dequeue (path_half1);
        while (el != NULL)
        {
            b = (Vertex *) el->data;
            queue_enqueue (path, (void*) b);
            el = queue_dequeue (path_half1);
        }

        //joining path and path_half2
        el = queue_dequeue (path_half2);
        while (el != NULL)
        {
            b = (Vertex *) el->data;
            queue_enqueue (path, (void*) b);
            el = queue_dequeue (path_half2);
        }
        
        queue_destroy (path_half1);
        queue_destroy (path_half2);
        return path;
    }

}

/**
 * Finds augmenting paths, and use these paths to augment the current 
 * matching.
 *
 * @param[in] G The graph whose matching is being augmented
 * @param[in] high A vertex such that Level(high) > Level(low)
 * @param[in] low A vertex such that Level(low) < Level(high)
 * @param[in] B A bloom, used by open to find paths through blooms
 *              other than B
 */
Queue *
findpath (Graph *G, Vertex *high, Vertex *low, Bloom *B)
{
    int m;
    Vertex *v, *u, *z;
    Edge *v_z, *u_v;
    Element *el;
    Bloom *b;

    Bool have_unvisited_edges = False;
    //path contains the vertices that form a path.
    //The edges themselves need to be fetched from the graph 
    //using these vertices
    Queue *path = queue_create (), *temp;
    
    if (high == low)
    {
        queue_enqueue (path, (void *) high);
        return path;
    }

    v = high;
    do
    {
        //verify this loop...
        while (!have_unvisited_edges)
        {
            for (el = v->predecessors->head; el != NULL; el = el->next)
            {
                z = (Vertex *) el->data;
                v_z = get_edge_by_vertices (G, v, z);
                if (v_z->visited == VISITED)
                    continue;
                else
                {
                    have_unvisited_edges = True;
                    break;
                }
            }

            if (!have_unvisited_edges)
                v = v->parent;
        }
        
        if (v->bloom == B->id || v->bloom == -1)
        {
            //choose an "unvisited" predecessor edge (u,v), and mark it as visited
            for (el = v->predecessors->head; el != NULL; el = el->next)
            {
                u = (Vertex *) el->data;
                u_v = get_edge_by_vertices (G, u, v);
                if (u_v->visited == UNVISITED)
                {
                    u_v->visited = VISITED;
                    break;
                }
            }
        }
        else
        {
            b = (Bloom *) queue_n_get (G->blooms, v->bloom)->data;
            u = b->base;
        }

        if (u->visited == UNVISITED && u->status == UNERASED
                && vertex_level (u) > vertex_level (low)
                && u->side == high->side)
        {
            u->visited = VISITED;
            u->parent = v;
            v = u;
        }

    } while (u != low);
    
    //creating the path from high to low, using parent pointers
    queue_enqueue (path, (void*) high);
    z = high->parent;
    queue_enqueue (path, (void *) z);
    while (z != low)
    {
        z = z->parent;
        queue_enqueue (path, (void *) z);
    }
    //adding low to the path
    queue_enqueue (path, (void *) z);

    //u == xj and v = xj+1
    for (m = 0; m < path->queue_size; m++)
    {
        u = (Vertex *) queue_n_get (path, m)->data;
        if (u->bloom != -1 && u->bloom != B->id)
        {
            v = (Vertex *) queue_n_get (path, m + 1)->data;
            temp = open (G, u);
            u = (Vertex *) queue_dequeue (temp)->data;
            v = (Vertex *) queue_dequeue (temp)->data;
            queue_destroy (temp);
        }

    }

    return path;
}

/**
 * Executes one step of the left DFS search process. It advances vl to a 
 * predecessor or backtracks or signals the discovery of a bloom.
 *
 * @param[in] G The graph whose matching is being augmented
 * @param[in] s The left vertex of the bridge (s,t)
 * @param[in] vl A vertex with a 'left' mark
 * @param[in] vr A vertex with a 'right' mark
 * @param[in] DCV The Deepest Common Vertex found during the dfs
 * @param[in] barrier The vertex used to stop the backtracking from going
 *                    further than barrier.
 * @param[in] bloom_vertices A list that contain vertices that were marked 'left'
 *                           or 'right' during the DFS and are used to create 
 *                           a new bloom.
 * @param[out] A boolean value signing that a new bloom was created
 */
Bool
left_dfs (Graph *G, Vertex *s, Vertex *vl, Vertex *vr,
               Vertex *DCV, Vertex *barrier, List *bloom_vertices)
{
    Vertex *u;
    Edge *e;
    Element *predecessor_el = list_pop (vl->predecessors);
    while (predecessor_el != NULL)
    {
        u = (Vertex *) predecessor_el->data;
        if (u->status == ERASED)
            continue;

        e = get_edge_by_vertices (G, vl, u);
        if (e->used == UNUSED)
        {
            e->used = USED;
        }

        if (u->bloom != -1)
        {
            //u = base*(u->bloom)
            u = base_p (u, G->blooms);
        }

        if (u->side != LEFT && u->side != RIGHT)
        {
            u->side = LEFT;
            list_add (bloom_vertices, (void *) u);
            u->parent = vl; 
            vl = u;
        }
        predecessor_el = list_pop (vl->predecessors);
    }

    if (vl == s)
    {
        vl = vl->parent;
        return True;
    }

    return False;
}

/**
 * One step of right DFS search process. Advances vr to a predecessor
 * or backtracks.
 *
 * @param[in] G The graph whose matching is being augmented
 * @param[in] vl A vertex with a 'left' mark
 * @param[in] vr A vertex with a 'right' mark
 * @param[in] DCV The Deepest Common Vertex found during the dfs
 * @param[in] barrier The vertex used to stop the backtracking from going
 *                    further than barrier.
 * @param[in] bloom_vertices A list that contain vertices that were marked 'left'
 *                           or 'right' during the dfs and are used to create 
 *                           a new bloom.
 */
void 
right_dfs (Graph *G, Vertex *vl, Vertex *vr, 
                Vertex *DCV, Vertex *barrier, List *bloom_vertices)
{
    Vertex *u;
    Edge *e;
    Element *predecessor_el = list_pop (vr->predecessors);
    while (predecessor_el != NULL)
    {
        u = (Vertex *) predecessor_el->data;
        if (u->status == ERASED)
            continue;

        e = get_edge_by_vertices (G, vr, u);
        if (e->used == UNUSED)
        {
            e->used = USED;
        }

        if (u->bloom != -1)
        {
            //u = base*(u->bloom)
            u = base_p (u, G->blooms);
        }

        if (u->side != LEFT && u->side != RIGHT)
        {
            u->side = RIGHT;
            list_add (bloom_vertices, (void *) u);
            u->parent = vr; 
            vr = u;
            //return False;
            return;
        }
        else
        {
            if (u == vl)
                DCV = u;
        }
    }

    if (vr == barrier)
    {
        vr = DCV;
        barrier = DCV;
        vr->side = RIGHT;
        list_add (bloom_vertices, (void *) vr);
        vl = vl->parent;
    }
    else
        vr = vr->parent;

    //return False;
}

/**
 * Either discovers a bloom or augments the initial matching.
 *
 * @param[in] G The graph whose matching is being augmented
 * @param[in] e The bridge (s, t) discovered at the current level of execution
 * @param[in] candidates The list of candidates
 * @param[in] bridges The list of bridges
 * @param[in] M The initial matching of the graph
 * @param[out] A boolean value signing if the current matching was augmented
 */
Bool
bloss_aug (Graph *G, Edge *e, List *candidates, List *bridges, 
           List *M, int phase)
{
    //B is used when the bloom passed to left or right_dfs is undefined
    Bloom B; B.id = -1;
    Element *el;
    Edge *temp;
    Vertex *vl, *vr, *DCV, *barrier, *v1, *v2;
    Bool bloom_discovered = False;
    Queue *path_half1, *path_half2;
    //used in case a bloom is discovered
    List *bloom_vertices = list_create ();
    //s = e->v1;
    //t = e->v2;

    if ((e->v1->bloom != -1) && (e->v2->bloom != -1) 
        && (e->v1->bloom == e->v2->bloom))
        return;

    if ((e->v1->bloom != -1))
    {
        //vl = base*(s->bloom)
        vl = base_p (e->v1, G->blooms);
    }
    else
        vl = e->v1;

    if ((e->v2->bloom != -1))
    {
        //vr = base*(t->bloom)
        vr = base_p (e->v2, G->blooms);
    }
    else
        vr = e->v2;

    vr->side = LEFT;
    vr->side = RIGHT;

    barrier = vr;

    while (vl->matched == UNMATCHED && vr->matched == UNMATCHED)
    {
        if (vertex_level (vl) >= vertex_level (vr))
           bloom_discovered = left_dfs (G, e->v1, vl, vr, DCV, 
                                        barrier, bloom_vertices);
        else
           right_dfs (G, vl, vr, DCV, barrier, bloom_vertices);

        if (bloom_discovered)
        {
            bloom_create (G, e, phase,
                            candidates, bridges,
                            bloom_vertices, DCV);
            list_destroy (bloom_vertices);
            return False;
        }

    }
    //find a path Pl from High=s to Low=vl with B=undefined
    path_half1 = findpath (G, e->v1, vl, &B);
    //find a path Pr from High=t to Low=vr with B=undefined
    path_half2 = findpath (G, e->v2, vr, &B);

    //increase the current matching M, reversing Pl through e ending with Pr
    //joining paths into one single queue
    while (!queue_is_empty (path_half2))
    {
        queue_enqueue (path_half1, queue_dequeue (path_half2)->data);
    }

    //freeing memory
    queue_destroy (path_half2);

    for (el = path_half1->first; el->next != NULL; el = el->next)
    {
        v1 = (Vertex *) el->data;
        v2 = (Vertex *) el->next->data;
        temp = get_edge_by_vertices (G, v1, v2);
        if (temp->checked == UNCHECKED)
        {
            reverse_edge (temp);
            if (temp->matched == MATCHED)
                list_add (M, (void *) temp);
        }
    }

    queue_destroy (path_half1);

    //run through M and delete edges that are unmatched, so M contain
    //only edges that have been reversed and are matched
    el = M->head;
    while (el != NULL)
    {
        temp = (Edge *) el->data;
        if (temp->matched == UNMATCHED)
            list_delete (M, temp);
        el = el->next;
    }

    return True;
}

/*
 * Finds all augmenting paths of minimal length and uses these paths 
 * to augment the current matching.
 *
 * @param[in] G The graph whose the matching is being augmented
 * @param[in] candidates The list of candidates
 * @param[in] bridges The list of bridges
 * @param[in] M The initial matching of the graph
 */
Bool
search (Graph *G, List *candidates, List *bridges, List* M)
{
    //mostly temporary or loop variables
    int i = 0, j;
    Element *el, *el_1; //el_1 is used for nested list iteration
    Vertex *v, *u;
    Edge *e;
    List *temp_list;
    
    //probably will become an external value
    Bool augmentation_occurred = False;
    
    //used to access one of the lists inside bridges or candidates list
    List *bridges_el;
    List *candidates_el = (List *) list_n_get(candidates, 0)->data;

    List *exposed_vertices = get_exposed_vertices (G);

    for (el = exposed_vertices->head; el != NULL; el = el->next)
    {
        v = (Vertex *) el->data;
        v->evenlevel = 0;
        list_add (candidates_el, (void *) v);
    }

    candidates_el = (List *) list_n_get(candidates, i)->data;

    while (!list_is_empty (candidates_el) 
           && !augmentation_occurred)
    {
        //if i is even
        if (i % 2 == 0)
        {
            for (el = candidates_el->head; el != NULL; el = el->next)
            {
                v = (Vertex *) el->data;

                //access unerased neighbors of v, and verify free edges between them
                for (el_1 = v->neighbors->head; el_1 != NULL; el_1 = el_1->next)
                {
                    u = (Vertex*) el_1->data;
                    //if u is erased, verify the next neighbor
                    if (u->status == ERASED)
                        continue;

                    e = get_edge_by_vertices(G, u, v);
                    if (e->matched == UNMATCHED)
                    {
                        if (u->evenlevel != INFINITY)
                        {
                            j = (u->oddlevel + v->oddlevel)/2;
                            bridges_el = (List *) list_n_get (bridges, j)->data;
                            list_add (bridges_el, e);
                        }
                        else
                        {
                            if (u->oddlevel == INFINITY)
                            {
                                u->oddlevel = i + 1;
                            }
                            if (u->oddlevel == i + 1)
                            {
                                u->count++;
                                list_add (u->predecessors, (void *) v);
                                list_add (v->successors, (void *) u);
                                list_add ((List *) list_n_get (candidates, i + 1)->data,
                                          (void *) u);
                            }
                            if (u->oddlevel < i)
                                list_add (u->anomalies, (void *) v);
                        }
                    }
                }
            }
        }
        //i is odd
        else
        {
            for (el = candidates_el->head; el != NULL; el = el->next)
            {
                v = (Vertex *) el->data;
                if (v->bloom == -1 && v->matched == MATCHED)
                {
                    u = v->mate;
                    if (u->oddlevel != INFINITY)
                    {
                        j = (u->oddlevel + v->oddlevel)/2;
                        bridges_el = (List *) list_n_get(bridges, j)->data;
                        //insert edge (u,v) in bridges_el
                        list_add (bridges_el, (void*) u->matched_edge);
                    }
                    if (u->evenlevel == INFINITY)
                    {
                        list_destroy (u->predecessors);
                        u->predecessors = list_create();
                        list_add (u->predecessors, (void *) v);

                        list_destroy (v->successors);
                        v->successors = list_create();
                        list_add (v->successors, (void *) u);

                        u->count = 1;
                        u->evenlevel = i + 1;
                        
                        temp_list = (List *) list_n_get (candidates, i + 1)->data;
                        list_add (temp_list, (void *) u);
                    }
                }
            }
        }

        bridges_el = (List *) list_n_get(bridges, i)->data;
        for (el = bridges_el->head; el != NULL; el = el->next)
        {
            //for each edge with both vertices unerased, call BLOSS-AUG
            e = (Edge *) el->data;
            if (e->v1->status != ERASED && e->v2->status != ERASED)
            {
                augmentation_occurred = bloss_aug(G, e, candidates, bridges, M, i);
            }
        }
        i++;
    }
    
    return augmentation_occurred;
}

/**
 * Main matching routine.
 *
 * @param[in] G The graph to find the maximum matching
 * @param[out] M The matching of the graph
 */
List * 
matching (Graph *G)
{
    //Loop variables
    int i;
    Bool augmentation_occurred = False;

    //setup a initial matching on the graph
    List *M = initial_matching (G);
    
    //Bridges and Candidates are Lists of lists. Which means that 
    //each element in both lists stores a pointer to another list
    List *candidates;
    List *bridges;

    do
    {
        //in case the lists are not empty, destroy them
        if (!list_is_empty (candidates))
            destroy_list_of_lists (candidates);

        if (!list_is_empty (bridges))
            destroy_list_of_lists (bridges);

        candidates = list_create ();
        bridges = list_create ();   

        for (i = 0; i < G->vertex_n; i++)
        {
            //initializing vertex with default values
            initialize_vertex (&G->v[i]);

            //recreating the group of lists
            list_add (candidates, (void *) list_create ());
            list_add (bridges, (void *) list_create ());
        }
        

        for (i = 0; i < G->edge_n; i++)
        {
            initialize_edge(&G->e[i]);
        }
        augmentation_occurred = search(G, candidates, bridges, M);

    } while (!augmentation_occurred);

    return M;
}
