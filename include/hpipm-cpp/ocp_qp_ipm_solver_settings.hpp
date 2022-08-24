#ifndef HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_
#define HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/d_ocp_qp_ipm_arg_wrapper.hpp"


namespace hpipm {

enum class HpipmMode {
  SpeedAbs = hpipm_mode::SPEED_ABS,
  Speed    = hpipm_mode::SPEED,
  Balance  = hpipm_mode::BALANCE,
  Robust   = hpipm_mode::ROBUST,
};

struct OcpQpIpmSolverSettings {
public:
  OcpQpIpmSolverSettings() = default;

  ~OcpQpIpmSolverSettings() = default;

  OcpQpIpmSolverSettings(const OcpQpIpmSolverSettings&) = default;

  OcpQpIpmSolverSettings& operator=(const OcpQpIpmSolverSettings&) = default;

  OcpQpIpmSolverSettings(OcpQpIpmSolverSettings&&) noexcept = delete;

  OcpQpIpmSolverSettings& operator=(OcpQpIpmSolverSettings&&) noexcept = delete;

  d_ocp_qp_ipm_arg_wrapper& getHpipmWrapper();

  HpipmMode mode = HpipmMode::Speed; 

  int iter_max = 15; 

  double alpha_min = 1.0e-08; // min step length

  double mu0 = 1.0e+02; // intial barrier parameter

  double tol_stat = 1.0e-08; // convergence criteria

  double tol_eq = 1.0e-08; // convergence criteria

  double tol_ineq = 1.0e-08; // convergence criteria

  double tol_comp = 1.0e-08; // convergence criteria

  double reg_prim = 1.0e-12; // reg

  int warm_start = 0; // use warm start or not

  int pred_corr = 1; // use correction step

  int ric_alg = 1; // use square-root Riccati or not 

  int split_step = 0; //  use different step for primal and dual variables or not

private:
  d_ocp_qp_ipm_arg_wrapper ocp_qp_ipm_arg_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_