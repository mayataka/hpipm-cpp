#include "hpipm-cpp/ocp_qp_ipm_solver_settings.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

OcpQpIpmSolverSettings::~OcpQpIpmSolverSettings() {
  if (memory_) {
    free(memory_);
  }
}


void OcpQpIpmSolverSettings::createHpipmData(OcpQpDim& dim) {
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_arg_memsize(dim.to_hpipm());
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_ipm_arg_create(dim.to_hpipm(), &ocp_qp_ipm_arg_hpipm_, memory_);
  }
  d_ocp_qp_ipm_arg_set_default(static_cast<hpipm_mode>(mode), &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_mu0(&mu0, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_iter_max(&iter_max, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_alpha_min(&alpha_min, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_mu0(&mu0, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_stat(&tol_stat, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_eq(&tol_eq, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_ineq(&tol_ineq, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_comp(&tol_comp, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_reg_prim(&reg_prim, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_warm_start(&warm_start, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_pred_corr(&pred_corr, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_ric_alg(&ric_alg, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_split_step(&split_step, &ocp_qp_ipm_arg_hpipm_);
}

} // namespace hpipm