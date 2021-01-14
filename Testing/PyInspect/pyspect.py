import sys
from PyGEL3D import gel
import time

def num_of_seps(graph: gel.Graph):
    return graph.__sizeof__()

if __name__ == "__main__":
    filename = input("Filename: (should end in .graph)\n")
    if filename == "":
        filename = "astest.graph"
    g = gel.graph_load(filename)
    s = gel.graph_LS_skeleton(g)
    v = gel.Viewer()

    # v.display(s)
