#include "hpipm-cpp/ocp_qp_solution.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

OcpQpSolution::OcpQpSolution(const OcpQpDim& dim) {
  resize(dim);
}


OcpQpSolution::~OcpQpSolution() {
  if (memory_) {
    free(memory_);
  }
}


std::vector<std::string> OcpQpSolution::checkSize(const OcpQpDim& dim) const {
  std::vector<std::string> err_mgs = dim.checkSize();
  if (!err_mgs.empty()) {
    err_mgs.push_back("Call ocp_qp_sol.checkSize() with correct ocp_qp_dim! Please check the above errors.");
    return err_mgs;
  }
  if (!x.empty()) {
    if (x.size() != dim.N+1) {
      err_mgs.push_back("ocp_qp_sol.x.size() must be the same as N+1 or 0!");
    }
    for (int i=0; i<=dim.N; ++i) {
      if (x[i].size() != dim.nx[i]) 
        err_mgs.push_back("ocp_qp_sol.x[" + std::to_string(i) + "].size() must be the same as ocp_qp_dim.nx[" + std::to_string(i) + "]!");
    }
  }
  if (!u.empty()) {
    if (u.size() != dim.N) {
      err_mgs.push_back("ocp_qp_sol.u.size() must be the same as N or 0!");
    }
    for (int i=0; i<dim.N; ++i) {
      if (u[i].size() != dim.nu[i]) 
        err_mgs.push_back("ocp_qp_sol.u[" + std::to_string(i) + "].size() must be the same as ocp_qp_dim.nu[" + std::to_string(i) + "]!");
    }
  }
  return err_mgs;
}


void OcpQpSolution::resize(const OcpQpDim& dim) {
  x.resize(dim.N+1);
  u.resize(dim.N);
  pi.resize(dim.N);
  for (int i=0; i<dim.N+1; ++i) {
    x[i].resize(dim.nx[i]);
  }
  for (int i=0; i<dim.N; ++i) {
    u[i].resize(dim.nu[i]);
  }
  for (int i=0; i<dim.N; ++i) {
    pi[i].resize(dim.nx[i]);
  }
}


void OcpQpSolution::createHpipmData(OcpQpDim& dim) {
  const hpipm_size_t new_memsize  = d_ocp_qp_sol_memsize(dim.to_hpipm());
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
	  d_ocp_qp_sol_create(dim.to_hpipm(), &ocp_qp_sol_hpipm_, memory_);
  }
  if (x.size() == dim.N+1) {
    for (int i=0; i<=dim.N; ++i) {
      d_ocp_qp_sol_set_x(i, x[i].data(), &ocp_qp_sol_hpipm_);
    }
  }
  if (u.size() == dim.N) {
    for (int i=0; i<dim.N; ++i) {
      d_ocp_qp_sol_set_u(i, u[i].data(), &ocp_qp_sol_hpipm_);
    }
  }
}


void OcpQpSolution::getSolutionFromHpipm(const OcpQpDim& dim) {
  x.resize(dim.N+1);
  u.resize(dim.N);
  pi.resize(dim.N);
  for (int i=0; i<dim.N; ++i) {
    x[i].setZero(dim.nx[i]);
    u[i].setZero(dim.nu[i]);
    pi[i].setZero(dim.nx[i]);
    d_ocp_qp_sol_get_x(i, &ocp_qp_sol_hpipm_, x[i].data());
    d_ocp_qp_sol_get_u(i, &ocp_qp_sol_hpipm_, u[i].data());
    d_ocp_qp_sol_get_pi(i, &ocp_qp_sol_hpipm_, pi[i].data());
  }
  x[dim.N].setZero(dim.nx[dim.N]);
  d_ocp_qp_sol_get_x(dim.N, &ocp_qp_sol_hpipm_, x[dim.N].data());
}

} // namespace hpipm