#include "hpipm-cpp/ocp_qp_sol.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

ocp_qp_sol::~ocp_qp_sol() {
  if (memory_) {
    free(memory_);
  }
}


void ocp_qp_sol::create_hpipm(ocp_qp_dim& dim) {
  const hpipm_size_t new_memsize  = d_ocp_qp_sol_memsize(dim.to_hpipm());
  if (memory_ && new_memsize >= memsize_) {
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
  if (u.size() == dim.N+1) {
    for (int i=0; i<=dim.N; ++i) {
      d_ocp_qp_sol_set_u(i, u[i].data(), &ocp_qp_sol_hpipm_);
    }
  }
}


void ocp_qp_sol::from_hpipm(const ocp_qp_dim& dim) {
  x.resize(dim.N+1);
  u.resize(dim.N+1);
  pi.resize(dim.N+1);
  for (int i=0; i<=dim.N; ++i) {
    x[i].resize(dim.nx[i]);
    u[i].resize(dim.nu[i]);
    pi[i].resize(dim.nx[i]);
    d_ocp_qp_sol_get_x(i, &ocp_qp_sol_hpipm_, x[i].data());
    d_ocp_qp_sol_get_u(i, &ocp_qp_sol_hpipm_, u[i].data());
    d_ocp_qp_sol_get_pi(i, &ocp_qp_sol_hpipm_, pi[i].data());
  }
}

} // namespace hpipm