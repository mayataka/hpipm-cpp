#include "hpipm-cpp/ocp_qp_ipm.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

ocp_qp_ipm::~ocp_qp_ipm() {
  if (memory_ ) {
	  free(memory_);
  }
}


void ocp_qp_ipm::create_hpipm(ocp_qp_dim& dim, ocp_qp_ipm_arg& ipm_arg) {
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_ws_memsize(dim.to_hpipm(), 
  														                             ipm_arg.to_hpipm());
  if (memory_ && new_memsize >= memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_ipm_ws_create(dim.to_hpipm(), ipm_arg.to_hpipm(), 
                           &ocp_qp_ipm_ws_hpipm_, memory_);
  }
}


HpipmStatus ocp_qp_ipm::solve(ocp_qp& qp, ocp_qp_sol& qp_sol, 
                              ocp_qp_ipm_arg& ipm_arg) {
  d_ocp_qp_ipm_solve(qp.to_hpipm(), qp_sol.to_hpipm(), ipm_arg.to_hpipm(), 
                     &ocp_qp_ipm_ws_hpipm_);
  int hpipm_status;
  d_ocp_qp_ipm_get_status(&ocp_qp_ipm_ws_hpipm_, &hpipm_status);
  if (0 <= hpipm_status && hpipm_status <= 3) {
    return static_cast<HpipmStatus>(hpipm_status);
  }
  else {
    return HpipmStatus::UnknownFailure;
  }
}

} // namespace hpipm