#ifndef HPIPM_CPP_OCP_QP_IPM_SOLVER_HPP_
#define HPIPM_CPP_OCP_QP_IPM_SOLVER_HPP_

#include <vector>
#include <string>
#include <iostream>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/ocp_qp.hpp"
#include "hpipm-cpp/ocp_qp_solution.hpp"
#include "hpipm-cpp/ocp_qp_ipm_solver_settings.hpp"
#include "hpipm-cpp/ocp_qp_ipm_solver_statistics.hpp"
#include "hpipm-cpp/d_ocp_qp_ipm_ws_wrapper.hpp"


namespace hpipm {

///
/// @class HpipmStatus
/// @brief Solver status.
///
enum class HpipmStatus {
  Success = 0,
  MaxIterReached = 1,
  MinStepLengthReached = 2,
  NaNDetected = 3,
  UnknownFailure = 4,
};

std::string to_string(const HpipmStatus& hpipm_status);

std::ostream& operator<<(std::ostream& os, const HpipmStatus& hpipm_status);

///
/// @class OcpQpIpmSolver
/// @brief Ipm solver.
///
class OcpQpIpmSolver {
public:
  ///
  /// @brief Constructor.
  /// @param[in] dim Dimension of the OCP-QP problem.
  /// @param[in] ipm_solver_settings Settings of Ipm solver.
  ///
  OcpQpIpmSolver(const OcpQpDim& dim, 
                 const OcpQpIpmSolverSettings& ipm_solver_settings);

  ///
  /// @brief Default constructor. 
  ///
  OcpQpIpmSolver() = default;

  ///
  /// @brief Destructor.
  ///
  ~OcpQpIpmSolver() = default;

  ///
  /// @brief Custom copy constructor.
  ///
  OcpQpIpmSolver(const OcpQpIpmSolver&);

  ///
  /// @brief Custom copy assign operator.
  ///
  OcpQpIpmSolver& operator=(const OcpQpIpmSolver&);

  ///
  /// @brief Default move constructor.
  ///
  OcpQpIpmSolver(OcpQpIpmSolver&&) noexcept = default;

  ///
  /// @brief Default move assign operator.
  ///
  OcpQpIpmSolver& operator=(OcpQpIpmSolver&&) noexcept = default;

  ///
  /// @brief Resizes the solver.
  /// @param[in] dim Dimension of the OCP-QP problem.
  ///
  void resize(const OcpQpDim& dim);

  ///
  /// @brief Sets the Ipm solver settings.
  /// @param[in] ipm_solver_settings Settings of Ipm solver.
  ///
  void setSolverSettings(const OcpQpIpmSolverSettings& ipm_solver_settings);

  ///
  /// @brief Solves the OCP-QP.
  /// @param[in, out] qp OCP-QP problem.
  /// @param[in, out] qp_sol Solution of the OCP-QP problem.
  /// @return Solver status.
  ///
  HpipmStatus solve(OcpQp& qp, OcpQpSolution& qp_sol);

  ///
  /// @brief Get the dimension of the OCP-QP problem.
  /// @return const reference to the dimension of the OCP-QP problem.
  ///
  const OcpQpDim& dim() const;

  ///
  /// @brief Get the Ipm solver settings.
  /// @return const reference to the Ipm solver settings.
  ///
  const OcpQpIpmSolverSettings& ipmSolverSettings() const;

  ///
  /// @brief Get the solver statistics.
  /// @return const reference to the solver statistics.
  ///
  const OcpQpIpmSolverStatistics& getSolverStatistics() const;

private:
  OcpQpIpmSolverStatistics solver_statistics_;
  OcpQpDim dim_;
  OcpQpIpmSolverSettings ipm_solver_settings_;
  d_ocp_qp_ipm_ws_wrapper ocp_qp_ipm_ws_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_HPP_