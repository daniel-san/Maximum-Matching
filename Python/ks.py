"""
File with the implementation of Karp-Sipser's greedy algorithm
to find a matching in a graph. Used by Chebolu et al. to develop a
O(n) algorithm to find a maximum matching on a given graph.
"""
import random

class Vertex ():
    def __init__(self,id):
        self.id = id 

class Edge ():
    def __init__(self,u,v):
        self.u = u
        self.v = v

class Graph ():
    def __init__(self):
        self.V = []
        self.V1 = []
        self.E = []

def greedy_matching (G):
    M = []
    
