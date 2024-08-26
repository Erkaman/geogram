#define BOOST_TEST_MODULE TestSkylineLU
#include <boost/test/unit_test.hpp>

#include <amgcl_adapter_zero_copy.hpp>
#include <amgcl_solver_skyline_lu.hpp>
#include <amgcl_backend_builtin.hpp>
#include <amgcl_profiler.hpp>
#include "sample_problem.hpp"

namespace amgcl {
    profiler<> prof;
}

BOOST_AUTO_TEST_SUITE( test_skyline_lu )

BOOST_AUTO_TEST_CASE(skyline_lu)
{
    std::vector<ptrdiff_t> ptr;
    std::vector<ptrdiff_t> col;
    std::vector<double>    val;
    std::vector<double>    rhs;

    size_t n = sample_problem(16, val, col, ptr, rhs);

    auto A = amgcl::adapter::zero_copy(n, ptr.data(), col.data(), val.data());

    amgcl::solver::skyline_lu<double> solve(*A);

    std::vector<double> x(n);
    std::vector<double> r(n);

    solve(rhs, x);

    amgcl::backend::residual(rhs, *A, x, r);

    BOOST_CHECK_SMALL(sqrt(amgcl::backend::inner_product(r, r)), 1e-8);
}

BOOST_AUTO_TEST_SUITE_END()

