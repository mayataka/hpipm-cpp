#include "hpipm-cpp/ocp_qp.hpp"

#include <stdexcept>
#include <string>


namespace hpipm {

OcpQp::OcpQp(const OcpQpDim& dim) {
  resize(dim);
}


void OcpQp::resize(const OcpQpDim& dim) {
  dim_ = dim;
  ocp_qp_wrapper_.resize(dim_.getHpipmWrapper());
  resize();
}


d_ocp_qp_wrapper& OcpQp::getHpipmWrapper() {
  checkSize();

  A_ptr_.resize(dim_.N);
  B_ptr_.resize(dim_.N);
  b_ptr_.resize(dim_.N);
  Q_ptr_.resize(dim_.N+1);
  S_ptr_.resize(dim_.N+1);
  R_ptr_.resize(dim_.N+1);
  q_ptr_.resize(dim_.N+1);
  r_ptr_.resize(dim_.N+1);
  idxbx_ptr_.resize(dim_.N+1);
  lbx_ptr_.resize(dim_.N+1);
  ubx_ptr_.resize(dim_.N+1);
  lbx_mask_ptr_.resize(dim_.N+1);
  ubx_mask_ptr_.resize(dim_.N+1);
  idxbu_ptr_.resize(dim_.N+1);
  lbu_ptr_.resize(dim_.N+1);
  ubu_ptr_.resize(dim_.N+1);
  lbu_mask_ptr_.resize(dim_.N+1);
  ubu_mask_ptr_.resize(dim_.N+1);
  C_ptr_.resize(dim_.N+1);
  D_ptr_.resize(dim_.N+1);
  lg_ptr_.resize(dim_.N+1);
  ug_ptr_.resize(dim_.N+1);
  lg_mask_ptr_.resize(dim_.N+1);
  ug_mask_ptr_.resize(dim_.N+1);
  Zl_ptr_.resize(dim_.N+1);
  Zu_ptr_.resize(dim_.N+1);
  zl_ptr_.resize(dim_.N+1);
  zu_ptr_.resize(dim_.N+1);
  idxs_ptr_.resize(dim_.N+1);
  lls_ptr_.resize(dim_.N+1);
  lus_ptr_.resize(dim_.N+1);

  // dynamics
  for (int i=0; i<dim_.N; ++i) {
    A_ptr_[i] = A[i].data();
    B_ptr_[i] = B[i].data();
    b_ptr_[i] = b[i].data();
  }
  // costs
  for (int i=0; i<dim_.N; ++i) {
    Q_ptr_[i] = Q[i].data();
    S_ptr_[i] = S[i].data();
    R_ptr_[i] = R[i].data();
    q_ptr_[i] = q[i].data();
    r_ptr_[i] = r[i].data();
  }
  Q_ptr_[dim_.N] = Q[dim_.N].data();
  q_ptr_[dim_.N] = q[dim_.N].data();
  // box constraints on state
  if (idxbx.empty() || lbx.empty() || ubx.empty()) {
    idxbx.resize(dim_.N+1);
    lbx.resize(dim_.N+1);
    ubx.resize(dim_.N+1);
  }
  idxbx[0].resize(dim_.nx[0]);
  for (int i=0; i<dim_.nx[0]; ++i) {
    idxbx[0][i] = i;
  }
  lbx[0] = x0;
  ubx[0] = x0;
  for (int i=0; i<=dim_.N; ++i) {
    idxbx_ptr_[i] = idxbx[i].data();
    lbx_ptr_[i]   = lbx[i].data();
    ubx_ptr_[i]   = ubx[i].data();
  }
  // box constraints on control input
  if (idxbu.empty() || lbu.empty() || ubu.empty()) {
    idxbu.resize(dim_.N+1);
    lbu.resize(dim_.N+1);
    ubu.resize(dim_.N+1);
  }
  for (int i=0; i<dim_.N; ++i) {
    idxbu_ptr_[i] = idxbu[i].data();
    lbu_ptr_[i] = lbu[i].data();
    ubu_ptr_[i] = ubu[i].data();
  }
  // constraints
  if (C.empty() || D.empty() || lg.empty() || ug.empty()) {
    C.resize(dim_.N+1);
    D.resize(dim_.N+1);
    lg.resize(dim_.N+1);
    ug.resize(dim_.N+1);
  }
  for (int i=0; i<dim_.N; ++i) {
    C_ptr_[i]  = C[i].data();
    D_ptr_[i]  = D[i].data();
    lg_ptr_[i] = lg[i].data();
    ug_ptr_[i] = ug[i].data();
  }
  C_ptr_[dim_.N]  = C[dim_.N].data();
  lg_ptr_[dim_.N] = lg[dim_.N].data();
  ug_ptr_[dim_.N] = ug[dim_.N].data();
  // soft constraints
  if (Zl.empty() || Zu.empty() || zl.empty() || zu.empty()) {
    Zl.resize(dim_.N+1);
    Zu.resize(dim_.N+1);
    zl.resize(dim_.N+1);
    zu.resize(dim_.N+1);
  }
  for (int i=0; i<=dim_.N; ++i) {
    Zl_ptr_[i] = Zu[i].data();
    Zu_ptr_[i] = Zu[i].data();
    zl_ptr_[i] = zl[i].data();
    zu_ptr_[i] = zu[i].data();
  }
  // TODO: what is this??
  if (idxs.empty() || lls.empty() || lus.empty()) {
    idxs.resize(dim_.N+1);
    lls.resize(dim_.N+1);
    lus.resize(dim_.N+1);
  }
  for (int i=0; i<=dim_.N; ++i) {
    idxs_ptr_[i] = idxs[i].data();
    lls_ptr_[i]  = lls[i].data();
    lus_ptr_[i]  = lus[i].data();
  }

  d_ocp_qp* hpipm_ptr = ocp_qp_wrapper_.get();
  d_ocp_qp_set_all(A_ptr_.data(), B_ptr_.data(), b_ptr_.data(), 
                   Q_ptr_.data(), S_ptr_.data(), R_ptr_.data(), q_ptr_.data(), r_ptr_.data(), 
                   idxbx_ptr_.data(), lbx_ptr_.data(), ubx_ptr_.data(),
                   idxbu_ptr_.data(), lbu_ptr_.data(), ubu_ptr_.data(),
                   C_ptr_.data(), D_ptr_.data(), lg_ptr_.data(), ug_ptr_.data(), 
                   Zl_ptr_.data(), Zu_ptr_.data(), zl_ptr_.data(), zu_ptr_.data(), 
                   idxs_ptr_.data(), lls_ptr_.data(), lus_ptr_.data(), hpipm_ptr);

  // initial state embedding
  hidxe_.resize(x0.size());
  for (int i=0; i<x0.size(); ++i) {
    hidxe_[i] = i;
  }
  d_ocp_qp_set_lbx(0, x0.data(), hpipm_ptr);
  d_ocp_qp_set_ubx(0, x0.data(), hpipm_ptr);
  d_ocp_qp_set_idxe(0, hidxe_.data(), hpipm_ptr);
  // masks
  if (lbx_mask.size() == dim_.N+1) {
    for (int i=1; i<=dim_.N; ++i) {
      if (lbx_mask[i].size() == dim_.nbx[i]) {
        lbx_mask_ptr_[i] = lbx[i].data();
        d_ocp_qp_set_lbx_mask(i, lbx_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ubx_mask.size() == dim_.N+1) {
    for (int i=1; i<=dim_.N; ++i) {
      if (ubx_mask[i].size() == dim_.nbx[i]) {
        ubx_mask_ptr_[i] = ubx[i].data();
        d_ocp_qp_set_ubx_mask(i, ubx_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (lbu_mask.size() == dim_.N) {
    for (int i=0; i<dim_.N; ++i) {
      if (lbu_mask[i].size() == dim_.nbu[i]) {
        lbu_mask_ptr_[i] = lbu[i].data();
        d_ocp_qp_set_lbu_mask(i, lbu_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ubu_mask.size() == dim_.N) {
    for (int i=0; i<dim_.N; ++i) {
      if (ubu_mask[i].size() == dim_.nbu[i]) {
        ubu_mask_ptr_[i] = ubu[i].data();
        d_ocp_qp_set_ubu_mask(i, ubu_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (lg_mask.size() == dim_.N+1) {
    for (int i=0; i<=dim_.N; ++i) {
      if (lg_mask[i].size() == dim_.ng[i]) {
        lg_mask_ptr_[i] = lg[i].data();
        d_ocp_qp_set_lg_mask(i, lg_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ug_mask.size() == dim_.N+1) {
    for (int i=0; i<=dim_.N; ++i) {
      if (ug_mask[i].size() == dim_.ng[i]) {
        ug_mask_ptr_[i] = ug[i].data();
        d_ocp_qp_set_ug_mask(i, ug_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  return ocp_qp_wrapper_;
}


const OcpQpDim& OcpQp::dim() const {
  return dim_;
}


void OcpQp::resize() {
  x0.resize(dim_.nx[0]); 
  // dynamics
  A.resize(dim_.N);
  B.resize(dim_.N);
  b.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    A[i].resize(dim_.nx[i], dim_.nx[i]);
    B[i].resize(dim_.nx[i], dim_.nu[i]);
    b[i].resize(dim_.nx[i]);
  }
  // cost
  Q.resize(dim_.N+1);
  S.resize(dim_.N);
  R.resize(dim_.N);
  q.resize(dim_.N+1);
  r.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    Q[i].resize(dim_.nx[i], dim_.nx[i]);
    S[i].resize(dim_.nu[i], dim_.nx[i]);
    R[i].resize(dim_.nu[i], dim_.nu[i]);
    q[i].resize(dim_.nx[i]);
    r[i].resize(dim_.nu[i]);
  }
  Q[dim_.N].resize(dim_.nx[dim_.N], dim_.nx[dim_.N]);
  q[dim_.N].resize(dim_.nx[dim_.N]);
  // constraints
  idxbx.resize(dim_.N+1);
  lbx.resize(dim_.N+1);
  ubx.resize(dim_.N+1);
  lbx_mask.resize(dim_.N+1);
  ubx_mask.resize(dim_.N+1);
  for (int i=0; i<dim_.N+1; ++i) {
    idxbx[i].resize(dim_.nbx[i]);
    lbx[i].resize(dim_.nbx[i]);
    ubx[i].resize(dim_.nbx[i]);
    lbx_mask[i].resize(0);
    ubx_mask[i].resize(0);
  }
  idxbu.resize(dim_.N);
  lbu.resize(dim_.N);
  ubu.resize(dim_.N);
  lbu_mask.resize(dim_.N);
  ubu_mask.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    idxbu[i].resize(dim_.nbu[i]);
    lbu[i].resize(dim_.nbu[i]);
    ubu[i].resize(dim_.nbu[i]);
    lbu_mask[i].resize(0);
    ubu_mask[i].resize(0);
  }
  C.resize(dim_.N+1);
  D.resize(dim_.N);
  lg.resize(dim_.N+1);
  ug.resize(dim_.N+1);
  lg_mask.resize(dim_.N+1);
  ug_mask.resize(dim_.N+1);
  for (int i=0; i<dim_.N; ++i) {
    C[i].resize(dim_.ng[i], dim_.nx[i]);
    D[i].resize(dim_.ng[i], dim_.nu[i]);
    lg[i].resize(dim_.ng[i]);
    ug[i].resize(dim_.ng[i]);
    lg_mask[i].resize(0);
    ug_mask[i].resize(0);
  }
  C[dim_.N].resize(dim_.ng[dim_.N], dim_.nx[dim_.N]);
  lg[dim_.N].resize(dim_.ng[dim_.N]);
  ug[dim_.N].resize(dim_.ng[dim_.N]);
  lg_mask[dim_.N].resize(0);
  ug_mask[dim_.N].resize(0);
  // soft constraints
  Zl.resize(dim_.N+1);
  Zu.resize(dim_.N+1);
  zl.resize(dim_.N+1);
  zu.resize(dim_.N+1);
  for (int i=0; i<=dim_.N; ++i) {
    Zl[i].resize(dim_.nsg[i], dim_.nsg[i]);
    Zu[i].resize(dim_.nsg[i], dim_.nsg[i]);
    zl[i].resize(dim_.nsg[i]);
    zu[i].resize(dim_.nsg[i]);
  }
  idxs.resize(dim_.N+1);
  lls.resize(dim_.N+1);
  lus.resize(dim_.N+1);
  for (int i=0; i<=dim_.N; ++i) {
    idxs[i].resize(dim_.nsg[i]);
    lls[i].resize(dim_.nsg[i]);
    lus[i].resize(dim_.nsg[i]);
  }
}


void OcpQp::checkSize() const {
  if (x0.size() != dim_.nx[0]) {
    throw std::runtime_error("x0.size() must be OcpQpDim::nx[0]");
  }
  // dynamics
  if (A.size() != dim_.N) {
    throw std::runtime_error("A.size() must be OcpQpDim::N");
  }
  if (B.size() != dim_.N) {
    throw std::runtime_error("B.size() must be OcpQpDim::N");
  }
  if (b.size() != dim_.N) {
    throw std::runtime_error("b.size() must be OcpQpDim::N");
  }
  for (unsigned int i=0; i<dim_.N; ++i) {
    if (A[i].rows() != dim_.nx[i]) {
      throw std::runtime_error("A[" + std::to_string(i) + "].rows() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (A[i].cols() != dim_.nx[i]) {
      throw std::runtime_error("A[" + std::to_string(i) + "].cols() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (B[i].rows() != dim_.nx[i]) {
      throw std::runtime_error("A[" + std::to_string(i) + "].rows() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (B[i].cols() != dim_.nu[i]) {
      throw std::runtime_error("B[" + std::to_string(i) + "].cols() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
    if (b[i].size() != dim_.nx[i]) {
      throw std::runtime_error("b[" + std::to_string(i) + "].size() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
  }
  // costs
  if (Q.size() != dim_.N+1) {
    throw std::runtime_error("Q.size() must be OcpQpDim::N+1");
  }
  if (R.size() != dim_.N) {
    throw std::runtime_error("R.size() must be OcpQpDim::N");
  }
  if (S.size() != dim_.N) {
    throw std::runtime_error("S.size() must be OcpQpDim::N");
  }
  if (q.size() != dim_.N+1) {
    throw std::runtime_error("q.size() must be OcpQpDim::N+1");
  }
  if (r.size() != dim_.N) {
    throw std::runtime_error("r.size() must be OcpQpDim::N");
  }
  for (unsigned int i=0; i<dim_.N; ++i) {
    if (Q[i].rows() != dim_.nx[i]) {
      throw std::runtime_error("Q[" + std::to_string(i) + "].rows() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (Q[i].cols() != dim_.nx[i]) {
      throw std::runtime_error("Q[" + std::to_string(i) + "].cols() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (S[i].rows() != dim_.nu[i]) {
      throw std::runtime_error("S[" + std::to_string(i) + "].rows() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
    if (S[i].cols() != dim_.nx[i]) {
      throw std::runtime_error("S[" + std::to_string(i) + "].cols() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (R[i].rows() != dim_.nu[i]) {
      throw std::runtime_error("R[" + std::to_string(i) + "].rows() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
    if (R[i].cols() != dim_.nu[i]) {
      throw std::runtime_error("R[" + std::to_string(i) + "].cols() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
    if (q[i].size() != dim_.nx[i]) {
      throw std::runtime_error("q[" + std::to_string(i) + "].size() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (r[i].size() != dim_.nu[i]) {
      throw std::runtime_error("r[" + std::to_string(i) + "].size() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
  }
  if (Q[dim_.N].rows() != dim_.nx[dim_.N]) {
    throw std::runtime_error("Q[" + std::to_string(dim_.N) + "].rows() must be OcpQpDim::nx[" + std::to_string(dim_.N) + "]");
  }
  if (Q[dim_.N].cols() != dim_.nx[dim_.N]) {
    throw std::runtime_error("Q[" + std::to_string(dim_.N) + "].cols() must be OcpQpDim::nx[" + std::to_string(dim_.N) + "]");
  }
  if (q[dim_.N].size() != dim_.nx[dim_.N]) {
    throw std::runtime_error("q[" + std::to_string(dim_.N) + "].size() must be OcpQpDim::nx[" + std::to_string(dim_.N) + "]");
  }
  // box constraints on x
  if (idxbx.size() != dim_.N+1) {
    throw std::runtime_error("idxbx.size() must be OcpQpDim::N+1");
  }
  if (lbx.size() != dim_.N+1) {
    throw std::runtime_error("lbx.size() must be OcpQpDim::N+1");
  }
  if (ubx.size() != dim_.N+1) {
    throw std::runtime_error("ubx.size() must be OcpQpDim::N+1");
  }
  if (lbx_mask.size() != dim_.N+1) {
    throw std::runtime_error("lbx_mask.size() must be OcpQpDim::N+1");
  }
  if (ubx_mask.size() != dim_.N+1) {
    throw std::runtime_error("ubx_mask.size() must be OcpQpDim::N+1");
  }
  for (unsigned int i=0; i<=dim_.N; ++i) {
    if (idxbx[i].size() != dim_.nbx[i]) {
      throw std::runtime_error("idxbx[" + std::to_string(i) + "].size() must be OcpQpDim::nbx[" + std::to_string(i) + "]");
    }
    if (lbx[i].size() != dim_.nbx[i]) {
      throw std::runtime_error("lbx[" + std::to_string(i) + "].size() must be OcpQpDim::nbx[" + std::to_string(i) + "]");
    }
    if (ubx[i].size() != dim_.nbx[i]) {
      throw std::runtime_error("ubx[" + std::to_string(i) + "].size() must be OcpQpDim::nbx[" + std::to_string(i) + "]");
    }
    if (lbx_mask[i].size() != 0 && lbx_mask[i].size() != dim_.nbx[i]) {
      throw std::runtime_error("lbx_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::nbx[" + std::to_string(i) + "]");
    }
    if (ubx_mask[i].size() != 0 && ubx_mask[i].size() != dim_.nbx[i]) {
      throw std::runtime_error("ubx_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::nbx[" + std::to_string(i) + "]");
    }
  }
  // box constraints on u
  if (idxbu.size() != dim_.N) {
    throw std::runtime_error("idxbu.size() must be OcpQpDim::N");
  }
  if (lbu.size() != dim_.N) {
    throw std::runtime_error("lbu.size() must be OcpQpDim::N");
  }
  if (ubu.size() != dim_.N) {
    throw std::runtime_error("ubu.size() must be OcpQpDim::N");
  }
  if (lbu_mask.size() != dim_.N) {
    throw std::runtime_error("lbu_mask.size() must be OcpQpDim::N");
  }
  if (ubu_mask.size() != dim_.N) {
    throw std::runtime_error("ubu_mask.size() must be OcpQpDim::N");
  }
  for (unsigned int i=0; i<dim_.N; ++i) {
    if (idxbu[i].size() != dim_.nbu[i]) {
      throw std::runtime_error("idxbu[" + std::to_string(i) + "].size() must be OcpQpDim::nbu[" + std::to_string(i) + "]");
    }
    if (lbu[i].size() != dim_.nbu[i]) {
      throw std::runtime_error("lbu[" + std::to_string(i) + "].size() must be OcpQpDim::nbu[" + std::to_string(i) + "]");
    }
    if (ubu[i].size() != dim_.nbu[i]) {
      throw std::runtime_error("ubu[" + std::to_string(i) + "].size() must be OcpQpDim::nbu[" + std::to_string(i) + "]");
    }
    if (lbu_mask[i].size() != 0 && lbu_mask[i].size() != dim_.nbu[i]) {
      throw std::runtime_error("lbu_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::nbu[" + std::to_string(i) + "]");
    }
    if (ubu_mask[i].size() != 0 && ubu_mask[i].size() != dim_.nbu[i]) {
      throw std::runtime_error("ubu_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::nbu[" + std::to_string(i) + "]");
    }
  }
  // constraints 
  if (C.size() != dim_.N+1) {
    throw std::runtime_error("C.size() must be OcpQpDim::N+1");
  }
  if (D.size() != dim_.N) {
    throw std::runtime_error("D.size() must be OcpQpDim::N");
  }
  if (lg.size() != dim_.N+1) {
    throw std::runtime_error("lg.size() must be OcpQpDim::N+1");
  }
  if (ug.size() != dim_.N+1) {
    throw std::runtime_error("ug.size() must be OcpQpDim::N+1");
  }
  if (lg_mask.size() != dim_.N+1) {
    throw std::runtime_error("lg_mask.size() must be OcpQpDim::N+1");
  }
  if (ug_mask.size() != dim_.N+1) {
    throw std::runtime_error("ug_mask.size() must be OcpQpDim::N+1");
  }
  for (unsigned int i=0; i<dim_.N; ++i) {
    if (C[i].rows() != dim_.ng[i]) {
      throw std::runtime_error("C[" + std::to_string(i) + "].rows() must be OcpQpDim::ng[" + std::to_string(i) + "]");
    }
    if (C[i].cols() != dim_.nx[i]) {
      throw std::runtime_error("C[" + std::to_string(i) + "].cols() must be OcpQpDim::nx[" + std::to_string(i) + "]");
    }
    if (D[i].rows() != dim_.ng[i]) {
      throw std::runtime_error("D[" + std::to_string(i) + "].rows() must be OcpQpDim::ng[" + std::to_string(i) + "]");
    }
    if (D[i].cols() != dim_.nu[i]) {
      throw std::runtime_error("D[" + std::to_string(i) + "].cols() must be OcpQpDim::nu[" + std::to_string(i) + "]");
    }
    if (lg[i].size() != dim_.ng[i]) {
      throw std::runtime_error("lg[" + std::to_string(i) + "].size() must be OcpQpDim::ng[" + std::to_string(i) + "]");
    }
    if (ug[i].size() != dim_.ng[i]) {
      throw std::runtime_error("ug[" + std::to_string(i) + "].size() must be OcpQpDim::ng[" + std::to_string(i) + "]");
    }
    if (lg_mask[i].size() != 0 && lg_mask[i].size() != dim_.ng[i]) {
      throw std::runtime_error("lg_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::ng[" + std::to_string(i) + "]");
    }
    if (ug_mask[i].size() != 0 && ug_mask[i].size() != dim_.ng[i]) {
      throw std::runtime_error("ub_mask[" + std::to_string(i) + "].size() must be 0 or OcpQpDim::ng[" + std::to_string(i) + "]");
    }
  }
  if (C[dim_.N].rows() != dim_.ng[dim_.N]) {
    throw std::runtime_error("C[" + std::to_string(dim_.N) + "].rows() must be OcpQpDim::ng[" + std::to_string(dim_.N) + "]");
  }
  if (C[dim_.N].cols() != dim_.nx[dim_.N]) {
    throw std::runtime_error("C[" + std::to_string(dim_.N) + "].cols() must be OcpQpDim::nx[" + std::to_string(dim_.N) + "]");
  }
  if (lg[dim_.N].size() != dim_.ng[dim_.N]) {
    throw std::runtime_error("lg[" + std::to_string(dim_.N) + "].size() must be OcpQpDim::ng[" + std::to_string(dim_.N) + "]");
  }
  if (ug[dim_.N].size() != dim_.ng[dim_.N]) {
    throw std::runtime_error("ug[" + std::to_string(dim_.N) + "].size() must be OcpQpDim::ng[" + std::to_string(dim_.N) + "]");
  }
  if (lg_mask[dim_.N].size() != 0 && lg_mask[dim_.N].size() != dim_.ng[dim_.N]) {
    throw std::runtime_error("lb_mask[" + std::to_string(dim_.N) + "].size() must be 0 or OcpQpDim::ng[" + std::to_string(dim_.N) + "]");
  }
  if (ug_mask[dim_.N].size() != 0 && ug_mask[dim_.N].size() != dim_.ng[dim_.N]) {
    throw std::runtime_error("ub_mask[" + std::to_string(dim_.N) + "].size() must be 0 or OcpQpDim::ng[" + std::to_string(dim_.N) + "]");
  }
  // soft constraints 
  if (Zl.size() != dim_.N+1) {
    throw std::runtime_error("Zl.size() must be OcpQpDim::N+1");
  }
  if (Zu.size() != dim_.N+1) {
    throw std::runtime_error("Zu.size() must be OcpQpDim::N+1");
  }
  if (zl.size() != dim_.N+1) {
    throw std::runtime_error("zl.size() must be OcpQpDim::N+1");
  }
  if (zu.size() != dim_.N+1) {
    throw std::runtime_error("zu.size() must be OcpQpDim::N+1");
  }
  for (unsigned int i=0; i<=dim_.N; ++i) {
    if (Zl[i].rows() != dim_.nsg[i]) {
      throw std::runtime_error("Zl[" + std::to_string(i) + "].rows() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (Zl[i].cols() != dim_.nsg[i]) {
      throw std::runtime_error("Zl[" + std::to_string(i) + "].cols() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (Zu[i].rows() != dim_.nsg[i]) {
      throw std::runtime_error("Zu[" + std::to_string(i) + "].rows() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (Zu[i].cols() != dim_.nsg[i]) {
      throw std::runtime_error("Zu[" + std::to_string(i) + "].cols() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (zl[i].size() != dim_.nsg[i]) {
      throw std::runtime_error("zl[" + std::to_string(i) + "].size() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (zu[i].size() != dim_.nsg[i]) {
      throw std::runtime_error("zu[" + std::to_string(i) + "].size() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
  }
  if (idxs.size() != dim_.N+1) {
    throw std::runtime_error("idxs.size() must be OcpQpDim::N+1");
  }
  if (lls.size() != dim_.N+1) {
    throw std::runtime_error("lls.size() must be OcpQpDim::N+1");
  }
  if (lus.size() != dim_.N+1) {
    throw std::runtime_error("lus.size() must be OcpQpDim::N+1");
  }
  for (unsigned int i=0; i<=dim_.N; ++i) {
    if (idxs[i].size() != dim_.nsg[i]) {
      throw std::runtime_error("idxs[" + std::to_string(i) + "].size() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (lls[i].size() != dim_.nsg[i]) {
      throw std::runtime_error("lls[" + std::to_string(i) + "].size() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
    if (lus[i].size() != dim_.nsg[i]) {
      throw std::runtime_error("lus[" + std::to_string(i) + "].size() must be OcpQpDim::nsg[" + std::to_string(i) + "]");
    }
  }
}

} // namespace hpipm
