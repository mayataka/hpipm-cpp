#ifndef HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_
#define HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/d_ocp_qp_ipm_arg_wrapper.hpp"


namespace hpipm {

///
/// @class HpipmMode
/// @brief Solver mode.
///
enum class HpipmMode {
  SpeedAbs = hpipm_mode::SPEED_ABS,
  Speed    = hpipm_mode::SPEED,
  Balance  = hpipm_mode::BALANCE,
  Robust   = hpipm_mode::ROBUST,
};

///
/// @class OcpQpIpmSolverSettings
/// @brief Ipm solver settings.
///
struct OcpQpIpmSolverSettings {
public:
  ///
  /// @brief Default constructor. 
  ///
  OcpQpIpmSolverSettings() = default;

  ///
  /// @brief Default destructor.
  ///
  ~OcpQpIpmSolverSettings() = default;

  ///
  /// @brief Default copy constructor.
  ///
  OcpQpIpmSolverSettings(const OcpQpIpmSolverSettings&) = default;

  ///
  /// @brief Default copy assign operator.
  ///
  OcpQpIpmSolverSettings& operator=(const OcpQpIpmSolverSettings&) = default;

  ///
  /// @brief Default move constructor.
  ///
  OcpQpIpmSolverSettings(OcpQpIpmSolverSettings&&) noexcept = default;

  ///
  /// @brief Default move assign operator.
  ///
  OcpQpIpmSolverSettings& operator=(OcpQpIpmSolverSettings&&) noexcept = default;

  ///
  /// @brief Gets the wrapper of hpipm's resource. 
  /// Throws exceptions when something wrongs in settings of iter_max, alpha_min, etc.
  ///
  d_ocp_qp_ipm_arg_wrapper& getHpipmWrapper();

  ///
  /// @brief Solver mode. Default is HpipmMode::Speed.
  ///
  HpipmMode mode = HpipmMode::Speed; 

  ///
  /// @brief Maximum number of iterations. Must be nen-negative. Default is 15.
  ///
  int iter_max = 15; 

  ///
  /// @brief Minimum step size. Must be positive and less than 1.0. Default is 1.0e-08.
  ///
  double alpha_min = 1.0e-08;

  ///
  /// @brief Initial barrier parameter. Must be positive. Default is 1.0e+02.
  ///
  double mu0 = 1.0e+02;

  ///
  /// @brief Convergence criteria. Must be positive. Default is 1.0e-08.
  ///
  double tol_stat = 1.0e-08;

  ///
  /// @brief Convergence criteria. Must be positive. Default is 1.0e-08.
  ///
  double tol_eq = 1.0e-08;

  ///
  /// @brief Convergence criteria. Must be positive. Default is 1.0e-08.
  ///
  double tol_ineq = 1.0e-08;

  ///
  /// @brief Convergence criteria. Must be positive. Default is 1.0e-08.
  ///
  double tol_comp = 1.0e-08; // convergence criteria

  ///
  /// @brief Regularization term. Must be non-negative. Default is 1.0e-12.
  ///
  double reg_prim = 1.0e-12;

  ///
  /// @brief Warm start flag (0: disable, 1: enable). Default is 0.
  ///
  int warm_start = 0;

  ///
  /// @brief Prediction-correction flag (0: disable, 1: enable). Default is 1.
  ///
  int pred_corr = 1;

  ///
  /// @brief Square-root Riccati flag (0: disable, 1: enable). Default is 1.
  ///
  int ric_alg = 1; 

  ///
  /// @brief Use different step for primal and dual variables (0: disable, 1: enable). Default is 0.
  ///
  int split_step = 0;

private:
  d_ocp_qp_ipm_arg_wrapper ocp_qp_ipm_arg_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_SETTINGS_HPP_