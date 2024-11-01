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

#include "geobasic_common.h"
#include "geobasic_process.h"
#include "geobasic_logger.h"
#include "geobasic_progress.h"
#include "geobasic_command_line.h"
#include "geobasic_file_system.h"
#include "geobasic_stopwatch.h"
#include "numerics_multi_precision.h"
#include "numerics_predicates.h"
#include "delaunay_delaunay.h"
 
#include "geo_version.h"
#include "bib_bibliography.h"


#include <sstream>
#include <iomanip>
#include <optional>

#ifdef GEO_OS_EMSCRIPTEN
#include <emscripten.h>
#endif

namespace GEO {

    namespace {

        /**
         * \brief A global object that manages initialization and
         *   termination of the Geogram library
         */
        struct GeogramLibSingleton {

            static std::optional<GeogramLibSingleton>& instance(int flags) {
                static std::optional<GeogramLibSingleton> instance(flags);
                return instance;
            }

            GeogramLibSingleton(int flags) {

                // When locale is set to non-us countries,
                // this may cause some problems when reading
                // floating-point numbers (some locale expect
                // a decimal ',' instead of a '.').
                // This restores the default behavior for
                // reading floating-point numbers.
#ifdef GEO_OS_UNIX
                if (flags & GEOGRAM_INSTALL_LOCALE) {
                    setenv("LC_NUMERIC","POSIX",1);
                }
#endif

#ifndef GEOGRAM_PSM
                Environment* env = Environment::instance();
                env->set_value("version", VORPALINE_VERSION);
                env->set_value("release_date", VORPALINE_BUILD_DATE);
                env->set_value("SVN revision", VORPALINE_SVN_REVISION);
#endif
                FileSystem::initialize();
                Logger::initialize();
                Process::initialize(flags);
                Progress::initialize();
                CmdLine::initialize();
                Stopwatch::initialize();
                PCK::initialize();
                Delaunay::initialize();

#ifndef GEOGRAM_PSM
                if (flags & GEOGRAM_INSTALL_BIBLIO) {
                    Biblio::initialize();
                }
#endif

#ifndef GEOGRAM_PSM
#endif

                // Clear lastest system error
                if (flags & GEOGRAM_INSTALL_ERRNO) {
                    errno = 0;
                }

#ifndef GEOGRAM_PSM
/*
                // Register attribute types that can be saved into files.
                geo_register_attribute_type<Numeric::uint8>("bool");
                geo_register_attribute_type<char>("char");
                geo_register_attribute_type<int>("int");
                geo_register_attribute_type<unsigned int>("unsigned int");
                geo_register_attribute_type<index_t>("index_t");
                geo_register_attribute_type<signed_index_t>("signed_index_t");
                geo_register_attribute_type<float>("float");
                geo_register_attribute_type<double>("double");

                geo_register_attribute_type<vec2>("vec2");
                geo_register_attribute_type<vec3>("vec3");
                */
#endif

#ifdef GEO_OS_EMSCRIPTEN

                // This mounts the local file system when an emscripten-compiled
                // program runs in node.js.
                // Current working directory is mounted in /working,
                // and root directory is mounted in /root

                EM_ASM(
                    if(typeof module !== 'undefined' && this.module !== module) {
                        FS.mkdir('/working');
                        FS.mkdir('/root');
                        FS.mount(NODEFS, { root: '.' }, '/working');
                        FS.mount(NODEFS, { root: '/' }, '/root');
                    }
                );
#endif

#ifndef GEOGRAM_PSM

#endif
            }

            ~GeogramLibSingleton() {

                if(
                    CmdLine::arg_is_declared("sys:stats") &&
                    CmdLine::get_arg_bool("sys:stats")
                ) {
                    Logger::div("System Statistics");
                    PCK::show_stats();
                    Process::show_stats();
                }

                PCK::terminate();

#ifndef GEOGRAM_PSM
                Biblio::terminate();
#endif

                Progress::terminate();
                Process::terminate();
                CmdLine::terminate();
                Logger::terminate();
                FileSystem::terminate();
                Environment::terminate();

            }
        };

    }

    void initialize(int flags) {
        GeogramLibSingleton::instance(flags);
    }

    void terminate() {
        GeogramLibSingleton::instance(GEOGRAM_INSTALL_NONE).reset();
    }
}
