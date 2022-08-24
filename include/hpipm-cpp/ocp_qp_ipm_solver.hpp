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

enum class HpipmStatus {
  Success = 0,
  MaxIterReached = 1,
  MinStepLengthReached = 2,
  NaNDetected = 3,
  UnknownFailure = 4,
};

std::string to_string(const HpipmStatus& hpipm_status);

std::ostream& operator<<(std::ostream& os, const HpipmStatus& hpipm_status);

class OcpQpIpmSolver {
public:
  OcpQpIpmSolver(const OcpQpDim& dim, 
                 const OcpQpIpmSolverSettings& ipm_solver_settings);

  OcpQpIpmSolver() = default;

  ~OcpQpIpmSolver() = default;

  OcpQpIpmSolver(const OcpQpIpmSolver&) = delete;

  OcpQpIpmSolver& operator=(const OcpQpIpmSolver&) = delete;

  void resize(const OcpQpDim& dim);

  void setSolverSettings(const OcpQpIpmSolverSettings& ipm_solver_settings);

  HpipmStatus solve(OcpQp& qp, OcpQpSolution& qp_sol);

  const OcpQpDim& dim() const;

  const OcpQpIpmSolverSettings& ipmSolverSettings() const;

  const OcpQpIpmSolverStatistics& getSolverStatistics() const;

private:
  OcpQpIpmSolverStatistics solver_statistics_;
  OcpQpDim dim_;
  OcpQpIpmSolverSettings ipm_solver_settings_;
  d_ocp_qp_ipm_ws_wrapper ocp_qp_ipm_ws_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_HPP_