#ifndef HPIPM_CPP_OCP_QP_HPP_
#define HPIPM_CPP_OCP_QP_HPP_

#include <vector>
#include <string>
#include <stdexcept>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"
#include "hpipm-cpp/d_ocp_qp_wrapper.hpp"


namespace hpipm {

///
/// @class OcpQpSolution
/// @brief The OCP-QP problem.
///
struct OcpQp {
public:
  ///
  /// @brief Constructor.
  /// @param[in] dim Dimension of the OCP-QP problem.
  ///
  OcpQp(const OcpQpDim& dim);

  ///
  /// @brief Default constructor. 
  ///
  OcpQp() = default;

  ///
  /// @brief Destructor.
  ///
  ~OcpQp() = default;

  ///
  /// @brief Default copy constructor.
  ///
  OcpQp(const OcpQp&) = default;

  ///
  /// @brief Default copy assign operator.
  ///
  OcpQp& operator=(const OcpQp&) = default;

  ///
  /// @brief Prohibit move constructor.
  ///
  OcpQp(OcpQp&&) noexcept = delete;

  ///
  /// @brief Prohibit move assign operator.
  ///
  OcpQp& operator=(OcpQp&&) noexcept = delete;

  ///
  /// @brief Resizes the OCP-QP problem.
  /// @param[in] dim Dimension of the OCP-QP problem.
  ///
  void resize(const OcpQpDim& dim);

  ///
  /// @brief Gets the wrapper of hpipm's resource. Throws exceptions 
  /// Throws exceptions when something wrongs in settings of x0, A, B, etc.
  ///
  d_ocp_qp_wrapper& getHpipmWrapper();

  ///
  /// @brief Initial state. Size must be OcpQpDim::nx[0].
  ///
  Eigen::VectorXd x0; 

  ///
  /// @brief Dynamics matrix in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nx[i] x OcpQpDim::nx[i].
  ///
  std::vector<Eigen::MatrixXd> A; 

  ///
  /// @brief Dynamics matrix in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nx[i] x OcpQpDim::nu[i].
  ///
  std::vector<Eigen::MatrixXd> B;

  ///
  /// @brief Dynamics vector in x[i+1] = A[i] x[i] + B[i] u[i] + b[i]. 
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nx[i].
  ///
  std::vector<Eigen::VectorXd> b;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] u[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nx[i] x OcpQpDim::nx[i].
  ///
  std::vector<Eigen::MatrixXd> Q;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] u[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nu[i] x OcpQpDim::nx[i].
  ///
  std::vector<Eigen::MatrixXd> S;

  ///
  /// @brief Cost matrix in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] u[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nu[i] x OcpQpDim::nu[i].
  ///
  std::vector<Eigen::MatrixXd> R;

  ///
  /// @brief Cost vector in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] u[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nx[i].
  ///
  std::vector<Eigen::VectorXd> q;

  ///
  /// @brief Cost vector in (1/2) * x[i]^T Q[i] x[i] + u[i]^T S[i] u[i] + (1/2) * u[i]^T R[i] u[i] + q[i]^T x[i] + r[i]^T u[i].   
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nu[i].
  ///
  std::vector<Eigen::VectorXd> r;

  ///
  /// @brief Indices of box constrainted elements of x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nbx[i].
  ///
  std::vector<std::vector<int>> idxbx;

  ///
  /// @brief Lower bounds of box constraints on x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nbx[i].
  ///
  std::vector<Eigen::VectorXd> lbx; 

  ///
  /// @brief Upper bounds of box constraints on x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nbx[i].
  ///
  std::vector<Eigen::VectorXd> ubx; 

  ///
  /// @brief Masks on the lower bounds of box constraints on x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be 0 or OcpQpDim::nbx[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> lbx_mask;

  ///
  /// @brief Masks on the upper bounds of box constraints on x.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be 0 or OcpQpDim::nbx[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> ubx_mask;

  ///
  /// @brief Indices of box constrainted elements of u.
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nbu[i].
  ///
  std::vector<std::vector<int>> idxbu;

  ///
  /// @brief Lower bounds of box constraints on u.
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nbu[i].
  ///
  std::vector<Eigen::VectorXd> lbu; 

  ///
  /// @brief Upper bounds of box constraints on u.
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::nbu[i].
  ///
  std::vector<Eigen::VectorXd> ubu; 

  ///
  /// @brief Masks on the lower bounds of box constraints on u.
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be 0 or OcpQpDim::nbu[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> lbu_mask;

  ///
  /// @brief Masks on the upper bounds of box constraints on u.
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be 0 or OcpQpDim::nbu[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> ubu_mask;

  ///
  /// @brief Constraint matrix in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::ng[i] x OcpQpDim::nx[i].
  ///
  std::vector<Eigen::MatrixXd> C;

  ///
  /// @brief Constraint matrix in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N. 
  /// Size of each element must be OcpQpDim::ng[i] x OcpQpDim::nu[i].
  ///
  std::vector<Eigen::MatrixXd> D;

  ///
  /// @brief Constraint vector in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::ng[i].
  ///
  std::vector<Eigen::VectorXd> lg; 

  ///
  /// @brief Constraint vector in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::ng[i].
  ///
  std::vector<Eigen::VectorXd> ug; 

  ///
  /// @brief Masks on lower bounds in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be 0 or OcpQpDim::ng[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> lg_mask;

  ///
  /// @brief Masks on upper bounds in lg[i] < C[i] x[i] + D[i] u[i] < ug[i].   
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be 0 or OcpQpDim::ng[i].
  /// Each element must be composed only by 0 or 1.0.
  ///
  std::vector<Eigen::VectorXd> ug_mask;

  ///
  /// @brief Matrix in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nsg[i].
  ///
  std::vector<Eigen::MatrixXd> Zl;

  ///
  /// @brief Matrix in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nsg[i].
  ///
  std::vector<Eigen::MatrixXd> Zu;

  ///
  /// @brief Vector in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nsg[i].
  ///
  std::vector<Eigen::VectorXd> zl;

  ///
  /// @brief Vector in the slack penalty (1/2) sl^T Zl sl + zl^T sl + (1/2) su^T Zu su + zu^T su.
  /// Size must be OcpQpDim::N+1. 
  /// Size of each element must be OcpQpDim::nsg[i].
  ///
  std::vector<Eigen::VectorXd> zu;

  ///
  /// @brief Indices of box constrainted elements of slack variables.
  /// Size must be OcpQpDim::N+1. 
  ///
  std::vector<std::vector<int>> idxs;

  ///
  /// @brief Lower bounds of box constraints of slack variables.
  /// Size must be OcpQpDim::N+1. 
  ///
  std::vector<Eigen::VectorXd> lls;

  ///
  /// @brief Upper bounds of box constraints of slack variables.
  /// Size must be OcpQpDim::N+1. 
  ///
  std::vector<Eigen::VectorXd> lus;

  ///
  /// @brief Get the dimension of the OCP-QP problem.
  /// @return const reference to the dimension of the OCP-QP problem.
  ///
  const OcpQpDim& dim() const;

private:
  std::vector<int> hidxe_;
  std::vector<double*> A_ptr_; 
  std::vector<double*> B_ptr_;
  std::vector<double*> b_ptr_;
  std::vector<double*> Q_ptr_; 
  std::vector<double*> S_ptr_; 
  std::vector<double*> R_ptr_; 
  std::vector<double*> q_ptr_; 
  std::vector<double*> r_ptr_; 
  std::vector<int*> idxbx_ptr_; 
  std::vector<double*> lbx_ptr_; 
  std::vector<double*> ubx_ptr_; 
  std::vector<double*> lbx_mask_ptr_; 
  std::vector<double*> ubx_mask_ptr_; 
  std::vector<int*> idxbu_ptr_; 
  std::vector<double*> lbu_ptr_; 
  std::vector<double*> ubu_ptr_; 
  std::vector<double*> lbu_mask_ptr_; 
  std::vector<double*> ubu_mask_ptr_; 
  std::vector<double*> C_ptr_; 
  std::vector<double*> D_ptr_;
  std::vector<double*> lg_ptr_; 
  std::vector<double*> ug_ptr_; 
  std::vector<double*> lg_mask_ptr_; 
  std::vector<double*> ug_mask_ptr_; 
  std::vector<double*> Zl_ptr_; 
  std::vector<double*> Zu_ptr_; 
  std::vector<double*> zl_ptr_; 
  std::vector<double*> zu_ptr_; 
  std::vector<int*> idxs_ptr_; 
  std::vector<double*> lls_ptr_; 
  std::vector<double*> lus_ptr_; 

  OcpQpDim dim_;
  d_ocp_qp_wrapper ocp_qp_wrapper_;

  void resize();

  void checkSize() const;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_HPP_