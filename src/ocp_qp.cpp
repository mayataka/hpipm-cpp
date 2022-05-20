#include "hpipm-cpp/ocp_qp.hpp"

#include <algorithm>
#include <cstdlib>

namespace hpipm {

ocp_qp::~ocp_qp() {
  if (memory_) {
    free(memory_);
  }
}


void ocp_qp::create_hpipm(ocp_qp_dim& dim) {
  const hpipm_size_t new_memsize = d_ocp_qp_memsize(dim.to_hpipm());
  if (memory_ && new_memsize >= memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_create(dim.to_hpipm(), &ocp_qp_hpipm_, memory_);
  }
  A_ptr_.clear();
  B_ptr_.clear();
  b_ptr_.clear();
  Q_ptr_.clear();
  S_ptr_.clear();
  R_ptr_.clear();
  q_ptr_.clear();
  r_ptr_.clear();
  idxbx_ptr_.clear();
  lbx_ptr_.clear();
  ubx_ptr_.clear();
  idxbu_ptr_.clear();
  lbu_ptr_.clear();
  ubu_ptr_.clear();
  C_ptr_.clear();
  D_ptr_.clear();
  lg_ptr_.clear();
  ug_ptr_.clear();
  Zl_ptr_.clear();
  Zu_ptr_.clear();
  zl_ptr_.clear();
  zu_ptr_.clear();
  idxs_ptr_.clear();
  lls_ptr_.clear();
  lus_ptr_.clear();

  A_ptr_.reserve(dim.N);
  B_ptr_.reserve(dim.N);
  b_ptr_.reserve(dim.N);
  Q_ptr_.reserve(dim.N+1);
  S_ptr_.reserve(dim.N+1);
  R_ptr_.reserve(dim.N+1);
  q_ptr_.reserve(dim.N+1);
  r_ptr_.reserve(dim.N+1);
  idxbx_ptr_.reserve(dim.N+1);
  lbx_ptr_.reserve(dim.N+1);
  ubx_ptr_.reserve(dim.N+1);
  idxbu_ptr_.reserve(dim.N+1);
  lbu_ptr_.reserve(dim.N+1);
  ubu_ptr_.reserve(dim.N+1);
  C_ptr_.reserve(dim.N+1);
  D_ptr_.reserve(dim.N+1);
  lg_ptr_.reserve(dim.N+1);
  ug_ptr_.reserve(dim.N+1);
  Zl_ptr_.reserve(dim.N+1);
  Zu_ptr_.reserve(dim.N+1);
  zl_ptr_.reserve(dim.N+1);
  zu_ptr_.reserve(dim.N+1);
  idxs_ptr_.reserve(dim.N+1);
  lls_ptr_.reserve(dim.N+1);
  lus_ptr_.reserve(dim.N+1);

  // dynamics
  b_[0].noalias() += A_[0] * x0;
  A_[0].setZero();
  for (int i=0; i<N_; ++i) {
    A_ptr_[i] = A_[i].data();
    B_ptr_[i] = B_[i].data();
    b_ptr_[i] = b_[i].data();
  }
  // costs
  for (int i=0; i<=N_; ++i) {
    Q_ptr_[i] = Q_[i].data();
    S_ptr_[i] = S_[i].data();
    R_ptr_[i] = R_[i].data();
    q_ptr_[i] = q_[i].data();
    r_ptr_[i] = r_[i].data();
  }
  // box constraints
  for (int i=0; i<=N_; ++i) {
    idxbx_ptr_[i] = idxbx_[i].data();
    lbx_ptr_[i] = lbx_[i].data();
    ubx_ptr_[i] = ubx_[i].data();
    lbu_ptr_[i] = lbu_[i].data();
    ubu_ptr_[i] = ubu_[i].data();
  }
  // constraints
  for (int i=0; i<=N_; ++i) {
    C_ptr_[i] = C_[i].data();
    D_ptr_[i] = D_[i].data();
    lg_ptr_[i] = lg_[i].data();
    ug_ptr_[i] = ug_[i].data();
  }
  // soft constraints
  for (int i=0; i<=N_; ++i) {
    Zl_ptr_[i] = Zu_[i].data();
    Zu_ptr_[i] = Zu_[i].data();
    zl_ptr_[i] = zl_[i].data();
    zu_ptr_[i] = zu_[i].data();
  }
  // TODO: what is this??
  for (int i=0; i<=N_; ++i) {
    idxs_ptr_[i] = idxs_[i].data();
    lls_ptr_[i] = lls_[i].data();
    lus_ptr_[i] = lus_[i].data();
  }
  d_ocp_qp_set_all(A_ptr_.data(), B_ptr_.data(), b_ptr_.data(), 
                   Q_ptr_.data(), S_ptr_.data(), R_ptr_.data(), q_ptr_.data(), r_ptr_.data(), 
                   idxbx_ptr_.data(), lbx_ptr_.data(), ubx_ptr_.data(),
                   idxbu_ptr_.data(), lbu_ptr_.data(), ubu_ptr_.data(),
                   C_ptr_.data(), D_ptr_.data(), lg_ptr_.data(), ug_ptr_.data(), 
                   Zl_ptr_.data(), Zu_ptr_.data(), zl_ptr_.data(), zu_ptr_.data(), 
                   idxs_ptr_.data(), lls_ptr_.data(), lus_ptr_.data(), &ocp_qp_hpipm_);
}

} // namespace hpipm