#ifndef HPIPM_CPP_OCP_QP_HPP_
#define HPIPM_CPP_OCP_QP_HPP_

#include <vector>

#include "Eigen/Core"


namespace hpipm {

///
/// @class OcpQp
/// @brief The OCP-QP data class.
///
struct OcpQp {
  ///
  /// @brief Dynamics matrix in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  ///
  Eigen::MatrixXd A; 

  ///
  /// @brief Dynamics matrix in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  ///
  Eigen::MatrixXd B;

  ///
  /// @brief Dynamics vector in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  ///
  Eigen::VectorXd b;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] x[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  ///
  Eigen::MatrixXd Q;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] x[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  ///
  Eigen::MatrixXd S;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] x[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  ///
  Eigen::MatrixXd R;

  ///
  /// @brief Cost vector in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] x[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  ///
  Eigen::VectorXd q;

  ///
  /// @brief Cost vector in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] x[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  ///
  Eigen::VectorXd r;

  ///
  /// @brief Indices of box constrainted elements of x.
  ///
  std::vector<int> idxbx;

  ///
  /// @brief Lower bounds of box constraints on x.
  ///
  Eigen::VectorXd lbx; 

  ///
  /// @brief Upper bounds of box constraints on x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nbx[i].
  ///
  Eigen::VectorXd ubx; 

  ///
  /// @brief Masks on the lower bounds of box constraints on x.
  /// Each element must be composed only by 0 or 1.0.
  ///
  Eigen::VectorXd lbx_mask;

  ///
  /// @brief Masks on the upper bounds of box constraints on x.
  /// Each element must be composed only by 0 or 1.0.
  ///
  Eigen::VectorXd ubx_mask;

  ///
  /// @brief Indices of box constrainted elements of u.
  ///
  std::vector<int> idxbu;

  ///
  /// @brief Lower bounds of box constraints on u.
  ///
  Eigen::VectorXd lbu; 

  ///
  /// @brief Upper bounds of box constraints on u.
  ///
  Eigen::VectorXd ubu; 

  ///
  /// @brief Masks on the lower bounds of box constraints on u.
  ///
  Eigen::VectorXd lbu_mask;

  ///
  /// @brief Masks on the upper bounds of box constraints on u.
  /// Each element must be composed only by 0 or 1.0.
  ///
  Eigen::VectorXd ubu_mask;

  ///
  /// @brief Constraint matrix in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  ///
  Eigen::MatrixXd C;

  ///
  /// @brief Constraint matrix in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  ///
  Eigen::MatrixXd D;

  ///
  /// @brief Constraint vector in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  ///
  Eigen::VectorXd lg; 

  ///
  /// @brief Constraint vector in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  ///
  Eigen::VectorXd ug; 

  ///
  /// @brief Masks on lower bounds in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Each element must be composed only by 0 or 1.0.
  ///
  Eigen::VectorXd lg_mask;

  ///
  /// @brief Masks on upper bounds in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Each element must be composed only by 0 or 1.0.
  ///
  Eigen::VectorXd ug_mask;

  ///
  /// @brief Matrix in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  ///
  Eigen::MatrixXd Zl;

  ///
  /// @brief Matrix in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  ///
  Eigen::MatrixXd Zu;

  ///
  /// @brief Vector in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  ///
  Eigen::VectorXd zl;

  ///
  /// @brief Vector in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  ///
  Eigen::VectorXd zu;

  ///
  /// @brief Indices of box constrainted elements of slack variables.
  ///
  std::vector<int> idxs;

  ///
  /// @brief Lower bounds of box constraints of slack variables.
  ///
  Eigen::VectorXd lls;

  ///
  /// @brief Upper bounds of box constraints of slack variables.
  ///
  Eigen::VectorXd lus;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_HPP_