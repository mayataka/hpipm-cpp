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

  ///
  /// @brief Riccati matrix P. 
  ///
  Eigen::MatrixXd P;

  ///
  /// @brief Riccati vector s. 
  ///
  Eigen::VectorXd p;

  ///
  /// @brief Feedback gain. 
  ///
  Eigen::MatrixXd K;

  ///
  /// @brief Feedforward term. 
  ///
  Eigen::VectorXd k;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_SOLUTION_HPP_