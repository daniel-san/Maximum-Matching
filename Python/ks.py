"""
File with the implementation of Karp-Sipser's greedy algorithm
to find a matching in a graph. Used by Chebolu et al. to develop a
O(n) algorithm to find a maximum matching on a given graph.
"""
from random import randint as rand

class Vertex ():
    def __init__(self,id):
        self.id = id
        self.degree = 0
        self.edges = []

    def set_degree(self):
        self.degree = len(self.edges)

class Edge ():
    def __init__(self,u,v):
        self.u = u
        self.v = v

class Graph ():
    def __init__(self, vertex_n, edge_n):
        self.vertex_n = vertex_n
        self.vertex1_n = 0
        self.edge_n = edge_n
        self.V = []
        self.V1 = []
        self.E = []

def greedy_matching (G):
    M = []

    while(G.edge_n > 0):
        if G.vertex1_n > 0:
            n = rand(vertex1_n - 1)
            v = G.V1[n]
            G.V1[n], G.V1[G.vertex1_n - 1] = G.V1[G.vertex1_n - 1], G.V1[n]
            G.vertex1_n -= 1

            edge = pop(v.edges)

        else:
            n = rand(G.edge_n - 1)
            edge = G.E[n]

        G.E[n], G.E[G.edge_n - 1] = G.E[G.edge_n - 1], G.E[n]
        G.edge_n -= 1
        M.append(edge)
