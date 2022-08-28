#include "hpipm-cpp/ocp_qp_solution.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

OcpQpSolution::OcpQpSolution(const OcpQpDim& dim) {
  resize(dim);
}


void OcpQpSolution::resize(const OcpQpDim& dim) {
  dim_ = dim;
  resize();
}


d_ocp_qp_sol_wrapper& OcpQpSolution::getHpipmWrapper() {
  if (x.size() == dim_.N+1) {
    for (int i=0; i<=dim_.N; ++i) {
      if (x[i].size() == dim_.nx[i]) 
        d_ocp_qp_sol_set_x(i, x[i].data(), ocp_qp_sol_wrapper_.get());
    }
  }
  if (u.size() == dim_.N) {
    for (int i=0; i<dim_.N; ++i) {
      if (x[i].size() == dim_.nu[i]) 
        d_ocp_qp_sol_set_u(i, u[i].data(), ocp_qp_sol_wrapper_.get());
    }
  }
  return ocp_qp_sol_wrapper_;
}


void OcpQpSolution::retriveSolution() {
  resize();
  for (int i=0; i<dim_.N; ++i) {
    x[i].setZero();
    u[i].setZero();
    pi[i].setZero();
    d_ocp_qp_sol_get_x(i, ocp_qp_sol_wrapper_.get(), x[i].data());
    d_ocp_qp_sol_get_u(i, ocp_qp_sol_wrapper_.get(), u[i].data());
    d_ocp_qp_sol_get_pi(i, ocp_qp_sol_wrapper_.get(), pi[i].data());
  }
  x[dim_.N].setZero();
  d_ocp_qp_sol_get_x(dim_.N, ocp_qp_sol_wrapper_.get(), x[dim_.N].data());
}


const OcpQpDim& OcpQpSolution::dim() const {
  return dim_;
}


void OcpQpSolution::resize() {
  if (x.size() != dim_.N+1) {
    x.resize(dim_.N+1);
  }
  if (u.size() != dim_.N) {
    u.resize(dim_.N);
  }
  if (pi.size() != dim_.N) {
    pi.resize(dim_.N);
  }
  for (int i=0; i<dim_.N+1; ++i) {
    x[i].resize(dim_.nx[i]);
  }
  for (int i=0; i<dim_.N; ++i) {
    u[i].resize(dim_.nu[i]);
  }
  for (int i=0; i<dim_.N; ++i) {
    pi[i].resize(dim_.nx[i]);
  }
  ocp_qp_sol_wrapper_.resize(dim_.getHpipmWrapper());
}

} // namespace hpipm