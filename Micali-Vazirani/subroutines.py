"""
Subroutines used in Micali and Vazirani's algorithm.
"""

def search():
    """
    Effect: Finds all augmenting paths of minimal length and increases the current
    matching along these paths.
    Calls: bloss_aug()
    """
    pass

def bloss_aug():
    """
    Input: A bridge (s, t)
    Effect: Either discovers a bloom or augments the current matching.
    Called by: search
    Calls: left_dfs(), right_dfs(), erase()
    """
    pass

def left_dfs():
    """
    Inputs: Vertices s, VL, VR, DCV, Barrier
    Effect: One step of left depth-first search process--advances VL to a predecessor
    or backtracks or signals the discovery of a bloom.
    Called by: bloss_aug()
    """
    pass

def right_dfs():
    """
    Inputs: Vertices VL, VR, DCV, Barrier
    Effect: One step of right depth-first search process--advances VRto a predecessor
    or backtracks.
    Called by: bloss_aug()
    """
    pass

def erase():
    """
    Input: Set Y of vertices to be erased [ Y can be implemented by a queue]
    Effect: Marks all vertices in Y "erased."
    Once all predecessors of a vertex z have been erased, z is erased too.
    Called by: bloss_aug()
    """
    pass

def findpath():
    """
    Inputs: Vertices High and Low with Level(High)>_ Level(Low), bloom B
    Output: An alternating Path from High to Low through Predecessors
    Called by: bloss_aug(), open()
    Calls: open() , which finds paths through blooms other than B
    """
    pass

def open():
    """
    Inputs: Vertex x
    Output: An alternating path Path from x through Bloom(x) to base(Bloom(x))
    Called by: findpath()
    Calls: findpath()
    """
    pass
