#ifndef HPIPM_CPP_OCP_QP_SOLUTION_HPP_
#define HPIPM_CPP_OCP_QP_SOLUTION_HPP_

#include "Eigen/Core"

namespace hpipm {

///
/// @class OcpQpSolution
/// @brief Solution of the OCP-QP problem.
///
struct OcpQpSolution {
public:
  ///
  /// @brief State. 
  ///
  Eigen::VectorXd x;

  ///
  /// @brief Control input. 
  ///
  Eigen::VectorXd u;

  ///
  /// @brief Costate (the Lagrange multiplier w.r.t the state equation). 
  ///
  Eigen::VectorXd pi;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_SOLUTION_HPP_