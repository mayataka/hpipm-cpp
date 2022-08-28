#include "hpipm-cpp/ocp_qp_ipm_solver_settings.hpp"


namespace hpipm {

d_ocp_qp_ipm_arg_wrapper& OcpQpIpmSolverSettings::getHpipmWrapper() {
  if (iter_max < 0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.iter_max must be non-negative");
  }
  if (alpha_min <= 0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.alpha_min must be positive");
  }
  if (alpha_min > 1.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.alpha_min must be less than 1.0");
  }
  if (mu0 <= 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.mu0 must be positive");
  }
  if (tol_stat <= 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.tol_stat must be positive");
  }
  if (tol_eq <= 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.tol_eq must be positive");
  }
  if (tol_ineq <= 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.tol_ineq must be positive");
  }
  if (tol_comp <= 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.tol_comp must be positive");
  }
  if (reg_prim < 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.reg_prim must be non-negative");
  }
  if (reg_prim < 0.0) {
    throw std::runtime_error("OcpQpIpmSolverSettings.reg_prim must be non-negative");
  }
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