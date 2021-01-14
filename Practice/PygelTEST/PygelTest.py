import sys
from PyGEL3D import gel
import time

begin = time.time()
print("Skeletonizing: ", sys.argv[1])
m = gel.obj_load(sys.argv[1])
g = gel.graph_from_mesh(m)
s = gel.graph_LS_skeleton(g)
v = gel.Viewer()

end = time.time()

print(f"Total runtime: {end-begin} seconds")
v.display(m)
v.display(s)

# gel.graph_save("skelSkeleton.graph", s)
# gel.graph_save("skelMesh.graph", m)
