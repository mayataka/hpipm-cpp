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
  OcpQpIpmSolver() = default;

  ~OcpQpIpmSolver();

  void createHpipmData(OcpQpDim& dim, OcpQpIpmSolverSettings& ipm_arg);

  // TODO: add const to qp and ipm_arg?
  HpipmStatus solve(OcpQp& qp, OcpQpSolution& qp_sol, 
                    OcpQpIpmSolverSettings& ipm_arg);

  OcpQpIpmSolverStatistics getSolverStatistics();

private:
  struct d_ocp_qp_ipm_ws ocp_qp_ipm_ws_hpipm_;
  void *memory_ = nullptr;
  double *stat_;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_HPP_