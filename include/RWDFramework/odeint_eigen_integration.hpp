#ifndef ODEINT_EIGEN_INTEGRATION_HPP
#define ODEINT_EIGEN_INTEGRATION_HPP

#include <iostream>
#include <vector>

#include <eigen3/Eigen/Core>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template<typename B,int S1,int S2,int O, int M1, int M2>
struct algebra_dispatcher< Eigen::Matrix<B,S1,S2,O,M1,M2> > {
    typedef vector_space_algebra algebra_type;
};

}}}

namespace Eigen {

template<typename D, int Rows, int Cols>
Matrix<D, Rows, Cols>
abs(Matrix<D, Rows, Cols> const& m) {
    return m.cwiseAbs();
}

}

#endif // ODEINT_EIGEN_INTEGRATION_HPP
