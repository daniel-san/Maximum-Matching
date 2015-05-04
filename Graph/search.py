#Graph Search Algorithms

def dfs(G, v):
    """
    Iterative Depth-First Search base implementation
    """
    s = []
    s.append(v)
    while s:
        v = s.pop()
        if v.status != "visited":
            v.status = "visited"
            for i in v.adj:
                s.append(i)

    

def bfs():
    """
    Breadth-First Search base implementation
    """
    q = []
    q.append(v) #Enqueue
    while q:
        v = q.pop(0) #Dequeue
        for i in v.adj:
            if i.status != "visited":
                q.append(i)
                i.status = "visited"
        
