import os
from os.path import join
from PyGEL3D import gel


if __name__ == "__main__":
    # Be sure to include the TestFiles folder in the same folder as test.py
    src_path = os.path.dirname(os.path.realpath(__file__))

    # Only adds files, that end in .obj
    test_file_names = [join(f"{src_path}/TestFiles", x) for x in os.listdir(src_path + "/TestFiles") if x[-4:] == ".obj"]

    # Initting gel
    viewer = gel.Viewer()

    for name in test_file_names:
        print(name)
        m = gel.obj_load(name)
        print(f"Displaying {name}")
        viewer.display(m)