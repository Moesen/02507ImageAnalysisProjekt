//
//  skeletor.cpp
//  skeletor
//
//  Created by Andreas Bærentzen on 02/03/2020.
//  Copyright © 2020 J. Andreas Bærentzen. All rights reserved.
//

#include <GEL/CGLA/CGLA.h>
#include <GEL/Geometry/Graph.h>
#include <GEL/HMesh/HMesh.h>

#include "graph_io.h"
#include "graph_skeletonize.h"
#include "graph_util.h"

using namespace std;
using namespace HMesh;
using namespace Geometry;
using namespace CGLA;

using NodeID = AMGraph3D::NodeID;

double quality_noise_level = 0.0875;


void mesh_skeleton(const AMGraph3D& g, const std::string& fname) {
    Manifold m;
    auto [c,r] = approximate_bounding_sphere(g);
    graph_to_mesh_cyl(g, m, 0.005 * r);
    obj_save(fname, m);
}


int main(int argc, char* argv[]) {
    const string fn = argv[1];
    const string fn_out = argv[2];

    AMGraph3D g;

    auto l = fn.length();
    if(fn.substr(l-5,5) == "graph") {
        g = graph_load(fn);
        mesh_skeleton(g,fn_out);
        exit(0);
    }
    else {
        Manifold m;
        load(fn, m);
        
        VertexAttributeVector<NodeID> v2n;
        for(auto v : m.vertices())
            v2n[v] = g.add_node(m.pos(v));
        for(auto h: m.halfedges()) {
            Walker w = m.walker(h);
            if(h<w.opp().halfedge())
                g.connect_nodes(v2n[w.opp().vertex()], v2n[w.vertex()]);
        }
    }
    NodeSetVec nsv = local_separators(g, quality_noise_level);
    

    using hrc = chrono::high_resolution_clock;
    auto t1 = hrc::now();
    AMGraph3D skel = skeleton_from_node_set_vec(g, nsv, 1, 1);
    auto t2 = hrc::now();
    cout << "Making skeleton: " << (t2-t1).count()*1e-9 << endl;
    graph_save(fn_out, skel);
//    
//    t1 = hrc::now();
//    AMGraph3D skel_smooth = skeleton_from_node_set_vec(g, nsv, 1, 1);
//    t2 = hrc::now();
//    cout << "Making smooth skeleton: " << (t2-t1).count()*1e-9 << endl;
//    graph_save(fn_out_smooth, skel_smooth);

}
