#include <iostream>
#include <string>

#include <amgcl_backend_builtin.hpp>
#include <amgcl_adapter_crs_tuple.hpp>
#include <amgcl_value_type_static_matrix.hpp>
#include <amgcl_adapter_block_matrix.hpp>
#include <amgcl/preconditioner/schur_pressure_correction.hpp>
#include <amgcl_make_solver.hpp>
#include <amgcl/make_block_solver.hpp>
#include <amgcl_amg.hpp>
#include <amgcl/solver/bicgstab.hpp>
#include <amgcl/solver/preonly.hpp>
#include <amgcl_coarsening_aggregation.hpp>
#include <amgcl/relaxation/ilu0.hpp>
#include <amgcl_relaxation_spai0.hpp>
#include <amgcl_relaxation_as_preconditioner.hpp>

#include <amgcl_io_mm.hpp>
#include <amgcl_profiler.hpp>

//---------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    // The command line should contain the matrix file name:
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <matrix.mtx> <nu>" << std::endl;
        return 1;
    }

    // The profiler:
    amgcl::profiler<> prof("CoupCons3D");

    // Read the system matrix:
    ptrdiff_t rows, cols;
    std::vector<ptrdiff_t> ptr, col;
    std::vector<double> val;

    prof.tic("read");
    std::tie(rows, cols) = amgcl::io::mm_reader(argv[1])(ptr, col, val);
    std::cout << "Matrix " << argv[1] << ": " << rows << "x" << cols << std::endl;
    prof.toc("read");

    // The RHS is filled with ones:
    std::vector<double> f(rows, 1.0);

    // The number of unknowns in the U subsystem
    ptrdiff_t nu = std::stoi(argv[2]);

    // We use the tuple of CRS arrays to represent the system matrix.
    // Note that std::tie creates a tuple of references, so no data is actually
    // copied here:
    auto A = std::tie(rows, ptr, col, val);

    // Compose the solver type
    typedef amgcl::backend::builtin<double> SBackend; // the outer iterative solver backend
    typedef amgcl::backend::builtin<float> PBackend;  // the PSolver backend
    typedef amgcl::backend::builtin<
        amgcl::static_matrix<float,4,4>> UBackend;    // the USolver backend

    typedef amgcl::make_solver<
        amgcl::preconditioner::schur_pressure_correction<
            amgcl::make_block_solver<
                amgcl::amg<
                    UBackend,
                    amgcl::coarsening::aggregation,
                    amgcl::relaxation::ilu0
                    >,
                amgcl::solver::preonly<UBackend>
                >,
            amgcl::make_solver<
                amgcl::relaxation::as_preconditioner<
                    PBackend,
                    amgcl::relaxation::spai0
                    >,
                amgcl::solver::preonly<PBackend>
                >
            >,
        amgcl::solver::bicgstab<SBackend>
        > Solver;

    // Solver parameters
    Solver::params prm;
    prm.precond.pmask.resize(rows);
    for(ptrdiff_t i = 0; i < rows; ++i) prm.precond.pmask[i] = (i >= nu);

    // Initialize the solver with the system matrix.
    prof.tic("setup");
    Solver solve(A, prm);
    prof.toc("setup");

    // Show the mini-report on the constructed solver:
    std::cout << solve << std::endl;

    // Solve the system with the zero initial approximation:
    int iters;
    double error;
    std::vector<double> x(rows, 0.0);
    prof.tic("solve");
    std::tie(iters, error) = solve(A, f, x);
    prof.toc("solve");

    // Output the number of iterations, the relative error,
    // and the profiling data:
    std::cout << "Iters: " << iters << std::endl
              << "Error: " << error << std::endl
              << prof << std::endl;
}
