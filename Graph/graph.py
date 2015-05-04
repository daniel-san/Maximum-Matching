#Graph classes draft

class Node():
    def __init__(self,x,y,id):
        self.id = -1
        self.status = None #Status, used in algorithms like DFS
        self.X = x #X coordinate, if used
        self.Y = y #Y coordinate, if used
        self.adj = [] #List of adjacent vertices
    
#Designing graph without a Edge class for now...    
#class Edge():
#    def __init__(self,n1,n2):
#        self.n1 = n1
#        self.n2 = n2
#        self.weight = None
#        
#    def calcWeight(self):
#        self.weight = math.sqrt((self.n2.X - self.n1.X)**2 + (self.n2.Y - self.n1.Y)**2)
#	
#    def __cmp__(self,other):
#        if self.weight < other.weight:
#            return -1
#        elif self.weight > other.weight:
#            return 1
#        else:
#            return 0

class Graph():
    def __init__(self):
        self.nodes = [] #List of vertices
        self.edges = [] #List of edges. A dictionary can be used in case of Weighted Edges
        
