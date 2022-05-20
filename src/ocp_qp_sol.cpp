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
  if (memory_ && new_memmemsize_size >= memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
	  d_ocp_qp_sol_create(dim.to_hpipm(), &ocp_qp_sol_hpipm_, memory_);
  }
}


void ocp_qp_sol::from_hpipm(const ocp_qp_dim& dim) {
  x.resize(dim.N+1);
  u.resize(dim.N+1);
  for (int i=0; i<dim.N; ++i) {
    x_[i].resize(dim.nx[i]);
    u_[i].resize(dim.nu[i]);
    d_ocp_qp_sol_get_x(i, &ocp_qp_sol_hpipm_, x[i].data());
    d_ocp_qp_sol_get_u(i, &ocp_qp_sol_hpipm_, u[i].data());
  }
  x[N].resize(dim.nx()[N]);
  d_ocp_qp_sol_get_x(N, &ocp_qp_sol_hpipm_, x[N].data());
  d_ocp_qp_sol_get_u(N, &ocp_qp_sol_hpipm_, u[N].data());
}

} // namespace hpipm