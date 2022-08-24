#include "hpipm-cpp/ocp_qp_ipm_solver_settings.hpp"


namespace hpipm {

d_ocp_qp_ipm_arg_wrapper& OcpQpIpmSolverSettings::getHpipmWrapper() {
  d_ocp_qp_ipm_arg* ptr = ocp_qp_ipm_arg_wrapper_.get();
  d_ocp_qp_ipm_arg_set_default(static_cast<hpipm_mode>(mode), ptr);
  d_ocp_qp_ipm_arg_set_mu0(&mu0, ptr);
  d_ocp_qp_ipm_arg_set_iter_max(&iter_max, ptr);
  d_ocp_qp_ipm_arg_set_alpha_min(&alpha_min, ptr);
  d_ocp_qp_ipm_arg_set_mu0(&mu0, ptr);
  d_ocp_qp_ipm_arg_set_tol_stat(&tol_stat, ptr);
  d_ocp_qp_ipm_arg_set_tol_eq(&tol_eq, ptr);
  d_ocp_qp_ipm_arg_set_tol_ineq(&tol_ineq, ptr);
  d_ocp_qp_ipm_arg_set_tol_comp(&tol_comp, ptr);
  d_ocp_qp_ipm_arg_set_reg_prim(&reg_prim, ptr);
  d_ocp_qp_ipm_arg_set_warm_start(&warm_start, ptr);
  d_ocp_qp_ipm_arg_set_pred_corr(&pred_corr, ptr);
  d_ocp_qp_ipm_arg_set_ric_alg(&ric_alg, ptr);
  d_ocp_qp_ipm_arg_set_split_step(&split_step, ptr);
  return ocp_qp_ipm_arg_wrapper_;
}

} // namespace hpipm