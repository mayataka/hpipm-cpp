#include "hpipm-cpp/ocp_qp_solution.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

OcpQpSolution::OcpQpSolution(const OcpQpDim& dim) {
  resize(dim);
}


// std::vector<std::string> OcpQpSolution::checkSize(const OcpQpDim& dim) const {
//   std::vector<std::string> err_mgs = dim.checkSize();
//   if (!err_mgs.empty()) {
//     err_mgs.push_back("Call ocp_qp_sol.checkSize() with correct ocp_qp_dim! Please check the above errors.");
//     return err_mgs;
//   }
//   if (!x.empty()) {
//     if (x.size() != dim.N+1) {
//       err_mgs.push_back("ocp_qp_sol.x.size() must be the same as N+1 or 0!");
//     }
//     for (int i=0; i<=dim.N; ++i) {
//       if (x[i].size() != dim.nx[i]) 
//         err_mgs.push_back("ocp_qp_sol.x[" + std::to_string(i) + "].size() must be the same as ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     }
//   }
//   if (!u.empty()) {
//     if (u.size() != dim.N) {
//       err_mgs.push_back("ocp_qp_sol.u.size() must be the same as N or 0!");
//     }
//     for (int i=0; i<dim.N; ++i) {
//       if (u[i].size() != dim.nu[i]) 
//         err_mgs.push_back("ocp_qp_sol.u[" + std::to_string(i) + "].size() must be the same as ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     }
//   }
//   return err_mgs;
// }


void OcpQpSolution::resize(const OcpQpDim& dim) {
  dim_ = dim;
  x.resize(dim_.N+1);
  u.resize(dim_.N);
  pi.resize(dim_.N);
  for (int i=0; i<dim_.N+1; ++i) {
    x[i].setZero(dim_.nx[i]);
  }
  for (int i=0; i<dim_.N; ++i) {
    u[i].setZero(dim_.nu[i]);
  }
  for (int i=0; i<dim_.N; ++i) {
    pi[i].setZero(dim_.nx[i]);
  }
  ocp_qp_sol_wrapper_.resize(dim_.getHpipmWrapper());
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
  x.resize(dim_.N+1);
  u.resize(dim_.N);
  pi.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    x[i].setZero(dim_.nx[i]);
    u[i].setZero(dim_.nu[i]);
    pi[i].setZero(dim_.nx[i]);
    d_ocp_qp_sol_get_x(i, ocp_qp_sol_wrapper_.get(), x[i].data());
    d_ocp_qp_sol_get_u(i, ocp_qp_sol_wrapper_.get(), u[i].data());
    d_ocp_qp_sol_get_pi(i, ocp_qp_sol_wrapper_.get(), pi[i].data());
  }
  x[dim_.N].setZero(dim_.nx[dim_.N]);
  d_ocp_qp_sol_get_x(dim_.N, ocp_qp_sol_wrapper_.get(), x[dim_.N].data());
}

} // namespace hpipm