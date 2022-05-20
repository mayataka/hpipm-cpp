#ifndef HPIPM_CPP_OCP_QP_IPM_ARG_HPP_
#define HPIPM_CPP_OCP_QP_IPM_ARG_HPP_

#include <vector>
#include <string>
#include <optional>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"


namespace hpipm {

enum class HpipmMode {
  SpeedAbs = hpipm_mode::SPEED_ABS,
  Speed    = hpipm_mode::SPEED,
  Balance  = hpipm_mode::BALANCE,
  Robust   = hpipm_mode::ROBUST,
};

struct ocp_qp_ipm_arg {
public:
  ocp_qp_ipm_arg() = default;

  ~ocp_qp_ipm_arg();

  void create_hpipm(ocp_qp_dim& dim);

  d_ocp_qp_ipm_arg* to_hpipm() { return &ocp_qp_ipm_arg_hpipm_; }

  const d_ocp_qp_ipm_arg* to_hpipm() const { return &ocp_qp_ipm_arg_hpipm_; }

  void from_hpipm(const ocp_qp_dim_wrapper& dim);

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
  d_ocp_qp_ipm_arg ocp_qp_ipm_arg_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_ARG_HPP_