#ifndef HPIPM_CPP_OCP_QP_HPP_
#define HPIPM_CPP_OCP_QP_HPP_

#include <vector>
#include <string>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"


namespace hpipm {

struct OcpQp {
public:
  OcpQp(const OcpQpDim& dim);

  OcpQp() = default;

  ~OcpQp();

  std::vector<std::string> checkSize(const OcpQpDim& dim) const;

  void resize(const OcpQpDim& dim);

  void createHpipmData(OcpQpDim& dim);

  d_ocp_qp* to_hpipm() { return &ocp_qp_hpipm_; }

  const d_ocp_qp* to_hpipm() const { return &ocp_qp_hpipm_; }

  Eigen::VectorXd x0; // initial state. 
  std::vector<Eigen::MatrixXd> A;  // x_next = Ax+Bu+b
  std::vector<Eigen::MatrixXd> B;
  std::vector<Eigen::VectorXd> b;
  std::vector<Eigen::MatrixXd> Q; // Qxx
  std::vector<Eigen::MatrixXd> S; // Qux
  std::vector<Eigen::MatrixXd> R; // Quu
  std::vector<Eigen::VectorXd> q; // lx
  std::vector<Eigen::VectorXd> r; // lu
  std::vector<std::vector<int>> idxbx; // indices of box constrained x
  std::vector<Eigen::VectorXd> lbx; 
  std::vector<Eigen::VectorXd> ubx; 
  std::vector<Eigen::VectorXd> lbx_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<Eigen::VectorXd> ubx_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<std::vector<int>> idxbu; // indices of box constrained u
  std::vector<Eigen::VectorXd> lbu; 
  std::vector<Eigen::VectorXd> ubu; 
  std::vector<Eigen::VectorXd> lbu_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<Eigen::VectorXd> ubu_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<Eigen::MatrixXd> C; // lg < Cx+Du < ug
  std::vector<Eigen::MatrixXd> D;
  std::vector<Eigen::VectorXd> lg; 
  std::vector<Eigen::VectorXd> ug; 
  std::vector<Eigen::VectorXd> lg_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<Eigen::VectorXd> ug_mask; // if this is set, each elemtn has to be 0.0 or 1.0
  std::vector<Eigen::MatrixXd> Zl; // penalty on the slacks of upper soft constraints
  std::vector<Eigen::MatrixXd> Zu; // penalty on the slacks of lower soft constraints
  std::vector<Eigen::VectorXd> zl; // lower bounds of the slacks of upper soft constraints
  std::vector<Eigen::VectorXd> zu; // lower bounds of the slacks of lower soft constraints
  std::vector<std::vector<int>> idxs; // TODO: what is this? 
  std::vector<Eigen::VectorXd> lls; // TODO: what is this?
  std::vector<Eigen::VectorXd> lus; // TODO: what is this?

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

  d_ocp_qp ocp_qp_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_HPP_