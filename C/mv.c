/** 
 * File with the implementation of Micali and Vazirani algorithm 
 * to find a maximum matching in a given graph. It is the fastest 
 * known algorithm for finding a maximum matching.
 */
#include <stdlib.h>
#include <time.h>
#include "mv_graph.h"

/*
 * Set some vertex attributes to default values 
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
 * Level(v) = min{Oddlevel(v), Evenlevel(v)}
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
 */
void
initialize_edge (Edge *e)
{
    e->used = UNUSED;
    e->visited = UNVISITED;
}

/*
 * Returns a list containing the free edges of 
 * a graph G
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
 * Returns a list containing the exposed vertices of 
 * a graph G.
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
 * Function to used to setup a initial matching from the given graph
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
 * the leftdfs or rightdfs discover a bloom.
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
 * Change the status of a list of vertices to ERASED
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
            if (z->status == UNERASED)
            {
                z->count--;
                if (z->count == 0)
                    list_add (Y, (void *) z);
            }
        }
    }
}

//computes the base*() of a bloom
Vertex *
base_p (Vertex *v, List* blooms)
{
    Vertex *top;
    Bloom *b;
    
}

void
open ()
{

}

void
findpath (Graph *G, Vertex *high, Vertex *low, Bloom *B)
{
    int m;
    Vertex *v, *u, *z;
    Edge *v_z;
    Element *el;
    Bloom *b;

    Bool have_unvisited_edges = False;
    Queue *path = queue_create ();
    if (high == low)
    {
        queue_enqueue (path, (void *) high);
        return;
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
    z = high->parent;
    queue_enqueue (path, (void *) z);
    while (z != low)
    {
        z = z->parent;
        queue_enqueue (path, (void *) z);
    }
    //adding low to the path
    queue_enqueue (path, (void *) z);

    for (m = 0; m < path->queue_size; m++)
    {
        u = (Vertex *) queue_n_get (path, m)->data;
        if (u->bloom != -1 && u->bloom != B->id)
        {
            v = (Vertex *) queue_n_get (path, m + 1)->data;
            //call open() and replace u and v with the returned values
        }

    }
}

Bool left_dfs (Graph *G, Vertex *s, Vertex *vl, Vertex *vr,
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

//maybe a void return...?
Bool right_dfs (Graph *G, Vertex *vl, Vertex *vr, 
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
        }

        if (u->side != LEFT && u->side != RIGHT)
        {
            u->side = RIGHT;
            list_add (bloom_vertices, (void *) u);
            u->parent = vr; 
            vr = u;
            return False;
        }
        else
        {
            if (u = vl)
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

    return False;
}

void
bloss_aug (Graph *G, Edge *e, List *candidates, List *bridges, int phase)
{
    Vertex *vl, *vr, *DCV, *barrier;
    Bool bloom_discovered = False;
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
    }
    else
        vl = e->v1;

    if ((e->v2->bloom != -1))
    {
        //vr = base*(t->bloom)
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
           bloom_discovered = right_dfs (G, vl, vr, DCV, 
                                         barrier, bloom_vertices);

       if (bloom_discovered)
           bloom_create (G, e, phase,
                         candidates, bridges,
                         bloom_vertices, DCV);

    }

    //findpath (); //find a path from High=s to Low=vl with B=undefined
    //findpath (); //find a path from High=t to Low=vr with B=undefined
}

/*
 * Subroutine SEARCH
 */
Bool
search (Graph *G, List *candidates, List *bridges)
{
    //mostly temporary or loop variables
    int i = 0, j;
    Element *el, *el_1; //el_1 is used for nested list iteration
    Vertex *v, *u;
    Edge *e;
    List *temp_list;
    
    //probably will become an external value
    Bool last_phase_has_augmenting_path = False;
    
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
           && !last_phase_has_augmenting_path)
    {
        if (i % 2 == 0)
        {
            for (el = candidates_el->head; el != NULL; el = el->next)
            {
                v = (Vertex *) el->data;

                //access unerased neighbors of v, and verify free edges between them
                temp_list = v->neighbors;
                for (el_1 = temp_list->head; el_1 != NULL; el_1 = el_1->next)
                {
                    u = (Vertex*) el_1->data;
                    if (u->status == ERASED)
                        continue;

                    e = get_edge_by_vertices(G, v, u);
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
                bloss_aug(G, e, candidates, bridges, i);
            }
        }
        i++;
    }
    

    return False;
}

/**
 * Main matching routine
 */
List * 
matching (Graph *G)
{
    //Loop variables
    int i;
    Bool has_augmenting_path = True;
    Vertex *v;
    List *M = initial_matching (G);
    
    //List of lists
    List *candidates;
    List *bridges;

    while(has_augmenting_path)
    {
        if (!list_is_empty (candidates))
            list_destroy (candidates);

        if (!list_is_empty (bridges))
            list_destroy (bridges);

        candidates = list_create ();
        bridges = list_create ();
            

        //setting the evenlevel and oddlevel of all vertices to infinity(-1)
        for (i = 0; i < G->vertex_n; i++)
        {
            initialize_vertex (&G->v[i]);

            list_add (candidates, (void *) list_create ());
            list_add (bridges, (void *) list_create ());
        }
        

        for (i = 0; i < G->edge_n; i++)
        {
            initialize_edge(&G->e[i]);
        }
        has_augmenting_path = search(G, candidates, bridges);
    }
    return M;
}
