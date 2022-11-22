#include "hpipm-cpp/ocp_qp_ipm_solver_settings.hpp"

#include <stdexcept>

namespace hpipm {

void OcpQpIpmSolverSettings::checkSettings() const {
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
}

} // namespace hpipm