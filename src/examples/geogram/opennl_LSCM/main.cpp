/*
 *  Copyright (c) 2000-2022 Inria
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *  * Neither the name of the ALICE Project-Team nor the names of its
 *  contributors may be used to endorse or promote products derived from this
 *  software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  Contact: Bruno Levy
 *
 *     https://www.inria.fr/fr/bruno-levy
 *
 *     Inria,
 *     Domaine de Voluceau,
 *     78150 Le Chesnay - Rocquencourt
 *     FRANCE
 *
 */

#include <geogram/NL/nl.h>

#include <geogram/basic/common.h>

#include <geogram/mesh/mesh.h>


#include <geogram/mesh/mesh_geometry.h>

#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>

#include <geogram/parameterization/mesh_atlas_maker.h>



int main(int argc, char** argv) {

    GEO::Attribute<double> tex_coord_;
    GEO::Attribute<double> vertex_tex_coord_;

    GEO::initialize(GEO::GEOGRAM_INSTALL_ALL);
    GEO::Logger::out("") << "Everything OK, Returning status 0" << std::endl;


  //  printf("lol\n");

    GEO::Mesh mesh;

    mesh.vertices.set_dimension(3);

    GEO::index_t first_v = mesh.vertices.create_vertices(3);

    GEO::Geom::mesh_vertex_ref(mesh,first_v+0) = GEO::vec3(0.0, 0.0, 0.0);

    GEO::Geom::mesh_vertex_ref(mesh,first_v+1) = GEO::vec3(1.0, 0.0, 1.0);
    GEO::Geom::mesh_vertex_ref(mesh,first_v+2) = GEO::vec3(0.0, 1.0, 1.0);

mesh.facets.create_triangle(
                        first_v + 0,
                        first_v + 1,
                        first_v + 2);

                        
/*

                index_t first_v = mesh_.vertices.create_vertices(12);
                for(index_t v=0; v<12; ++v) {
                    Geom::mesh_vertex_ref(mesh_,first_v+v) =
                        vec3(points[3*v], points[3*v+1], points[3*v+2]) ;
                }

                for(index_t f=0; f<20; ++f) {
                    mesh_.facets.create_triangle(
                        first_v + facets[3*f],
                        first_v + facets[3*f+1],
                        first_v + facets[3*f+2]
                    );
                }


*/

    /*

    bool spectral = false;
    bool OK = true;
    std::vector<std::string> filenames;

    nlInitialize(argc, argv);

    for(int i=1; i<argc; ++i) {
        if(!strcmp(argv[i],"spectral=true")) {
            spectral = true;
        } else if(!strcmp(argv[i],"spectral=false")) {
            spectral = false;
        } else if(strchr(argv[i],'=') == nullptr) {
            filenames.push_back(argv[i]);
        }
    }

    OK = OK && (filenames.size() >= 1) && (filenames.size() <= 2);

    if(!OK) {
        std::cerr << "usage: " << argv[0]
                  << " infile.obj <outfile.obj> <spectral=true|false>"
                  << std::endl;
        return -1;
    }

    if(filenames.size() == 1) {
        filenames.push_back("out.obj");
    }

    IndexedMesh mesh;
    std::cout << "Loading " << filenames[0] << "   ..." << std::endl;
    mesh.load(filenames[0]);

    LSCM lscm(mesh);
    lscm.set_spectral(spectral);
    lscm.apply();

    std::cout << "Saving " << filenames[1] << "   ..." << std::endl;
    mesh.save(filenames[1]);
    */
/*
    if(mesh()->facets.nb() == 0 && mesh()->cells.nb() == 0) {
            show_vertices();
    }
    */


mesh_make_atlas(
                mesh,
                 360.0,
                 GEO::PARAM_ABF ,
              GEO::PACK_XATLAS ,
                true // set to true to enable verbose messages
            );


int a= 2;
float f = 2.2;
    GEO::Logger::out("") << "lorem " << a << ", " << f << std::endl;

            
            tex_coord_.bind_if_is_defined(
                mesh.facet_corners.attributes(), "tex_coord"
            );
            GEO::Logger::out("") << "vv " << tex_coord_.is_bound() << ", " <<tex_coord_.dimension()  << std::endl;
            if(tex_coord_.is_bound() && tex_coord_.dimension() != 2) {
                tex_coord_.unbind();
            }

for(GEO::index_t c: mesh.facet_corners) {
                   // if(vt_old2new[c] == c) {
                        /*
                        out << "vt " << tex_coord_[2*c] << " "
                            << tex_coord_[2*c+1] << std::endl;x§
                        vt_index[c] = cur_vt;
                        ++cur_vt;
                        */
                   // }
                   GEO::Logger::out("") << "vt " << tex_coord_[2*c] << " "
                            << tex_coord_[2*c+1] << std::endl;
                }
/*
            for(index_t c: M.facet_corners) {

            }
            
            GEO::Logger::out("") << "vt " << tex_coord_[0] << ", " << tex_coord_[0] << std::endl;
*/

/*
            vertex_tex_coord_.bind_if_is_defined(
                mesh.vertices.attributes(), "tex_coord"
            );

            GEO::Logger::out("") << "vv " << vertex_tex_coord_.is_bound() << ", " <<vertex_tex_coord_.dimension()  << std::endl;

            if(
                vertex_tex_coord_.is_bound() &&
                vertex_tex_coord_.dimension() != 2
            ) {
                vertex_tex_coord_.unbind();
            }
            */




//    printf("facet %d\n",mesh.facets.nb() );


  //  printf("vertices %d\n",mesh.vertices.nb() );

  //  cmake -DCMAKE_BUILD_TYPE:STRING=Release -DVORPALINE_PLATFORM:STRING=Darwin-clang-dynamic ../
//



    

}
