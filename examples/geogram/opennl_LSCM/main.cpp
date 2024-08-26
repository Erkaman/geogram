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

#include "nl.h"

#include "geobasic_common.h"

#include "mesh_mesh.h"


#include "mesh_geometry.h"

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

#include "param_mesh_atlas_maker.h"



int main(int argc, char** argv) {

    GEO::Attribute<double> tex_coord_;
    GEO::Attribute<double> vertex_tex_coord_;

    GEO::initialize(GEO::GEOGRAM_INSTALL_ALL);
    GEO::Logger::out("") << "Everything OK, Returning status 0" << std::endl;


  //  printf("lol\n");

    GEO::Mesh mesh;

    mesh.vertices.set_dimension(3);

    GEO::index_t first_v = mesh.vertices.create_vertices(6);

        GEO::Logger::out("") << "first_v " << first_v << std::endl;

    GEO::Geom::mesh_vertex_ref(mesh,first_v+0) = GEO::vec3(0.0, 0.0, 0.0);
    GEO::Geom::mesh_vertex_ref(mesh,first_v+1) = GEO::vec3(1.0, 0.0, 0.0);
    GEO::Geom::mesh_vertex_ref(mesh,first_v+2) = GEO::vec3(0.0, 1.0, 0.0);

    GEO::Geom::mesh_vertex_ref(mesh,first_v+3) = GEO::vec3(0.0, 0.0, 1.0);
    GEO::Geom::mesh_vertex_ref(mesh,first_v+4) = GEO::vec3(1.0, 0.0, 1.0);
    GEO::Geom::mesh_vertex_ref(mesh,first_v+5) = GEO::vec3(0.0, 1.0, 1.0);

    mesh.facets.create_triangle(first_v + 0, first_v + 1, first_v + 2);
    mesh.facets.create_triangle(first_v + 3, first_v + 4, first_v + 5);


mesh_make_atlas(
                mesh,
                 360.0,
                 GEO::PARAM_ABF ,
              GEO::PACK_XATLAS ,
                true // set to true to enable verbose messages
            );

            tex_coord_.bind_if_is_defined(
                mesh.facet_corners.attributes(), "tex_coord"
            );
            GEO::Logger::out("") << "vv " << tex_coord_.is_bound() << ", " <<tex_coord_.dimension()  << std::endl;
            if(tex_coord_.is_bound() && tex_coord_.dimension() != 2) {
                tex_coord_.unbind();
            }

for(GEO::index_t c: mesh.facet_corners) {
                   
                   GEO::Logger::out("") << "vt " << tex_coord_[2*c] << " "
                            << tex_coord_[2*c+1] << std::endl;
                }


    

}
