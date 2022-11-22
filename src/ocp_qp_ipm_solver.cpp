#include "hpipm-cpp/ocp_qp_ipm_solver.hpp"

#include <algorithm>
#include <cstdlib>

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}


namespace hpipm {

std::string to_string(const HpipmStatus& hpipm_status) {
  switch (hpipm_status)
  {
  case HpipmStatus::Success:
    return "HpipmStatus::Success"; 
  case HpipmStatus::MaxIterReached:
    return "HpipmStatus::MaxIterReached"; 
  case HpipmStatus::MinStepLengthReached:
    return "HpipmStatus::MinStepLengthReached"; 
  case HpipmStatus::NaNDetected:
    return "HpipmStatus::NaNDetected"; 
  default:
    return "HpipmStatus::UnknownFailure"; 
  }
}


std::ostream& operator<<(std::ostream& os, const HpipmStatus& hpipm_status) {
  os << to_string(hpipm_status);
  return os;
}


OcpQpIpmSolver::OcpQpIpmSolver(const std::vector<OcpQp>& ocp_qp, 
                               const OcpQpIpmSolverSettings& solver_settings) 
  : solver_settings_(),
    solver_statistics_(),
    dim_(),
    ocp_qp_dim_wrapper_(std::make_shared<d_ocp_qp_dim_wrapper>()),
    ocp_qp_ipm_arg_wrapper_(std::make_shared<d_ocp_qp_ipm_arg_wrapper>()),
    ocp_qp_wrapper_(),
    ocp_qp_sol_wrapper_(),
    ocp_qp_ipm_ws_wrapper_() {
  setSolverSettings(solver_settings);
  resize(ocp_qp);
}


OcpQpIpmSolver::OcpQpIpmSolver() 
  : solver_settings_(),
    solver_statistics_(),
    dim_(),
    ocp_qp_dim_wrapper_(std::make_shared<d_ocp_qp_dim_wrapper>()),
    ocp_qp_ipm_arg_wrapper_(std::make_shared<d_ocp_qp_ipm_arg_wrapper>()),
    ocp_qp_wrapper_(),
    ocp_qp_sol_wrapper_(),
    ocp_qp_ipm_ws_wrapper_() {
  setSolverSettings(OcpQpIpmSolverSettings());
}


void OcpQpIpmSolver::setSolverSettings(const OcpQpIpmSolverSettings& solver_settings) {
  d_ocp_qp_ipm_arg* ocp_qp_ipm_arg_ptr = ocp_qp_ipm_arg_wrapper_->get();
  solver_settings_ = solver_settings;
  d_ocp_qp_ipm_arg_set_default(static_cast<hpipm_mode>(solver_settings_.mode), ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_mu0(&solver_settings_.mu0, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_iter_max(&solver_settings_.iter_max, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_alpha_min(&solver_settings_.alpha_min, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_mu0(&solver_settings_.mu0, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_tol_stat(&solver_settings_.tol_stat, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_tol_eq(&solver_settings_.tol_eq, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_tol_ineq(&solver_settings_.tol_ineq, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_tol_comp(&solver_settings_.tol_comp, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_reg_prim(&solver_settings_.reg_prim, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_warm_start(&solver_settings_.warm_start, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_pred_corr(&solver_settings_.pred_corr, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_ric_alg(&solver_settings_.ric_alg, ocp_qp_ipm_arg_ptr);
  d_ocp_qp_ipm_arg_set_split_step(&solver_settings_.split_step, ocp_qp_ipm_arg_ptr);
}


void OcpQpIpmSolver::resize(const std::vector<OcpQp>& ocp_qp) {
  dim_.resize(ocp_qp);
  ocp_qp_dim_wrapper_->resize(dim_.N);
  d_ocp_qp_dim_set_all(dim_.nx.data(), dim_.nu.data(), 
                       dim_.nbx.data(), dim_.nbu.data(), dim_.ng.data(), 
                       dim_.nsbx.data(), dim_.nsbu.data(), dim_.nsg.data(), 
                       ocp_qp_dim_wrapper_->get());

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

  idxbx0_.resize(dim_.nx[0]);
  for (int i=0; i<dim_.nx[0]; ++i) {
    idxbx0_[i] = i;
  }
  x0_.resize(dim_.nx[0]);

  ocp_qp_wrapper_.resize(ocp_qp_dim_wrapper_);
  ocp_qp_sol_wrapper_.resize(ocp_qp_dim_wrapper_);
  ocp_qp_ipm_ws_wrapper_.resize(ocp_qp_dim_wrapper_, ocp_qp_ipm_arg_wrapper_);
}


HpipmStatus OcpQpIpmSolver::solve(const Eigen::VectorXd& x0,
                                  std::vector<OcpQp>& ocp_qp,
                                  std::vector<OcpQpSolution>& qp_sol) {
  // resize data
  resize(ocp_qp);
  if (qp_sol.size() != dim_.N+1) {
    qp_sol.resize(dim_.N+1);
  }
  for (int i=0; i<=dim_.N; ++i) {
    qp_sol[i].x.resize(dim_.nx[i]);
  }
  for (int i=0; i<dim_.N; ++i) {
    qp_sol[i].u.resize(dim_.nu[i]);
  }
  for (int i=0; i<=dim_.N; ++i) {
    qp_sol[i].pi.resize(dim_.nx[i]);
  }
  // set QP data
  for (int i=0; i<dim_.N; ++i) {
    A_ptr_[i] = ocp_qp[i].A.data();
    B_ptr_[i] = ocp_qp[i].B.data();
    b_ptr_[i] = ocp_qp[i].b.data();
  }
  for (int i=0; i<dim_.N; ++i) {
    Q_ptr_[i] = ocp_qp[i].Q.data();
    S_ptr_[i] = ocp_qp[i].S.data();
    R_ptr_[i] = ocp_qp[i].R.data();
    q_ptr_[i] = ocp_qp[i].q.data();
    r_ptr_[i] = ocp_qp[i].r.data();
  }
  Q_ptr_[dim_.N] = ocp_qp[dim_.N].Q.data();
  q_ptr_[dim_.N] = ocp_qp[dim_.N].q.data();
  x0_ = x0;
  idxbx_ptr_[0] = idxbx0_.data();
  lbx_ptr_[0] = x0_.data();
  ubx_ptr_[0] = x0_.data();
  for (int i=1; i<=dim_.N; ++i) {
    idxbx_ptr_[i] = ocp_qp[i].idxbx.data();
    lbx_ptr_[i]   = ocp_qp[i].lbx.data();
    ubx_ptr_[i]   = ocp_qp[i].ubx.data();
  }
  for (int i=0; i<dim_.N; ++i) {
    idxbu_ptr_[i] = ocp_qp[i].idxbu.data();
    lbu_ptr_[i]   = ocp_qp[i].lbu.data();
    ubu_ptr_[i]   = ocp_qp[i].ubu.data();
  }
  for (int i=0; i<dim_.N; ++i) {
    C_ptr_[i]  = ocp_qp[i].C.data();
    D_ptr_[i]  = ocp_qp[i].D.data();
    lg_ptr_[i] = ocp_qp[i].lg.data();
    ug_ptr_[i] = ocp_qp[i].ug.data();
  }
  C_ptr_[dim_.N]  = ocp_qp[dim_.N].C.data();
  lg_ptr_[dim_.N] = ocp_qp[dim_.N].lg.data();
  ug_ptr_[dim_.N] = ocp_qp[dim_.N].ug.data();
  for (int i=0; i<=dim_.N; ++i) {
    Zl_ptr_[i] = ocp_qp[i].Zl.data();
    Zu_ptr_[i] = ocp_qp[i].Zu.data();
    zl_ptr_[i] = ocp_qp[i].zl.data();
    zu_ptr_[i] = ocp_qp[i].zu.data();
  }
  for (int i=0; i<=dim_.N; ++i) {
    idxs_ptr_[i] = ocp_qp[i].idxs.data();
    lls_ptr_[i]  = ocp_qp[i].lls.data();
    lus_ptr_[i]  = ocp_qp[i].lus.data();
  }
  d_ocp_qp* ocp_qp_ptr = ocp_qp_wrapper_.get();
  d_ocp_qp_set_all(A_ptr_.data(), B_ptr_.data(), b_ptr_.data(), 
                   Q_ptr_.data(), S_ptr_.data(), R_ptr_.data(), q_ptr_.data(), r_ptr_.data(), 
                   idxbx_ptr_.data(), lbx_ptr_.data(), ubx_ptr_.data(),
                   idxbu_ptr_.data(), lbu_ptr_.data(), ubu_ptr_.data(),
                   C_ptr_.data(), D_ptr_.data(), lg_ptr_.data(), ug_ptr_.data(), 
                   Zl_ptr_.data(), Zu_ptr_.data(), zl_ptr_.data(), zu_ptr_.data(), 
                   idxs_ptr_.data(), lls_ptr_.data(), lus_ptr_.data(), ocp_qp_ptr);

  // initial state embedding
  d_ocp_qp_set_lbx(0, x0_.data(), ocp_qp_ptr);
  d_ocp_qp_set_ubx(0, x0_.data(), ocp_qp_ptr);
  d_ocp_qp_set_idxe(0, idxbx0_.data(), ocp_qp_ptr);
  // masks
  for (int i=1; i<=dim_.N; ++i) {
    if (ocp_qp[i].lbx_mask.size() == dim_.nbx[i]) {
      lbx_mask_ptr_[i] = ocp_qp[i].lbx_mask.data();
      d_ocp_qp_set_lbx_mask(i, lbx_mask_ptr_[i], ocp_qp_ptr);
    }
  }
  for (int i=1; i<=dim_.N; ++i) {
    if (ocp_qp[i].ubx_mask.size() == dim_.nbx[i]) {
      ubx_mask_ptr_[i] = ocp_qp[i].ubx_mask.data();
      d_ocp_qp_set_ubx_mask(i, ubx_mask_ptr_[i], ocp_qp_ptr);
    }
  }
  for (int i=0; i<dim_.N; ++i) {
    if (ocp_qp[i].lbu_mask.size() == dim_.nbu[i]) {
      lbu_mask_ptr_[i] = ocp_qp[i].lbu_mask.data();
      d_ocp_qp_set_lbu_mask(i, lbu_mask_ptr_[i], ocp_qp_ptr);
    }
  }
  for (int i=0; i<dim_.N; ++i) {
    if (ocp_qp[i].ubu_mask.size() == dim_.nbu[i]) {
      ubu_mask_ptr_[i] = ocp_qp[i].ubu_mask.data();
      d_ocp_qp_set_ubu_mask(i, ubu_mask_ptr_[i], ocp_qp_ptr);
    }
  }
  for (int i=0; i<=dim_.N; ++i) {
    if (ocp_qp[i].lg_mask.size() == dim_.ng[i]) {
      lg_mask_ptr_[i] = ocp_qp[i].lg_mask.data();
      d_ocp_qp_set_lg_mask(i, lg_mask_ptr_[i], ocp_qp_ptr);
    }
  }
  for (int i=0; i<=dim_.N; ++i) {
    if (ocp_qp[i].ug_mask.size() == dim_.ng[i]) {
      ug_mask_ptr_[i] = ocp_qp[i].ug_mask.data();
      d_ocp_qp_set_ug_mask(i, ug_mask_ptr_[i], ocp_qp_ptr);
    }
  }

  // solve QP
  d_ocp_qp_dim* ocp_qp_dim_ptr = ocp_qp_dim_wrapper_->get();
  d_ocp_qp_sol* ocp_qp_sol_ptr = ocp_qp_sol_wrapper_.get();
  d_ocp_qp_ipm_arg* ocp_qp_ipm_arg_ptr = ocp_qp_ipm_arg_wrapper_->get();
  d_ocp_qp_ipm_ws* ocp_qp_ipm_ws_ptr = ocp_qp_ipm_ws_wrapper_.get();
  d_ocp_qp_ipm_solve(ocp_qp_ptr, ocp_qp_sol_ptr, ocp_qp_ipm_arg_ptr, ocp_qp_ipm_ws_ptr);

  // get solution
  for (int i=0; i<dim_.N; ++i) {
    d_ocp_qp_sol_get_x(i, ocp_qp_sol_ptr, qp_sol[i].x.data());
    d_ocp_qp_sol_get_u(i, ocp_qp_sol_ptr, qp_sol[i].u.data());
    d_ocp_qp_sol_get_pi(i, ocp_qp_sol_ptr, qp_sol[i].pi.data());
  }
  d_ocp_qp_sol_get_x(dim_.N, ocp_qp_sol_ptr, qp_sol[dim_.N].x.data());

  // get solver statistics
  d_ocp_qp_ipm_get_iter(ocp_qp_ipm_ws_ptr, &solver_statistics_.iter);
  d_ocp_qp_ipm_get_max_res_stat(ocp_qp_ipm_ws_ptr, &solver_statistics_.max_res_stat);
  d_ocp_qp_ipm_get_max_res_eq(ocp_qp_ipm_ws_ptr, &solver_statistics_.max_res_eq);
  d_ocp_qp_ipm_get_max_res_ineq(ocp_qp_ipm_ws_ptr, &solver_statistics_.max_res_ineq);
  d_ocp_qp_ipm_get_max_res_comp(ocp_qp_ipm_ws_ptr, &solver_statistics_.max_res_comp);
  const int stat_m = 18;
  solver_statistics_.clear();
  solver_statistics_.reserve(solver_statistics_.iter+2);
  for (int i=0; i<=solver_statistics_.iter+1; ++i) {
    solver_statistics_.alpha_aff.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+0]);
    solver_statistics_.mu_aff.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+1]);
    solver_statistics_.sigma.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+2]);
    solver_statistics_.alpha_prim.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+3]);
    solver_statistics_.alpha_dual.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+4]);
    solver_statistics_.mu.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+5]);
    solver_statistics_.res_stat.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+6]);
    solver_statistics_.res_eq.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+7]);
    solver_statistics_.res_ineq.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+8]);
    solver_statistics_.res_comp.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+9]);
    solver_statistics_.obj.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+10]);
    solver_statistics_.lq_fact.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+11]);
    solver_statistics_.itref_pred.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+12]);
    solver_statistics_.itref_corr.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+13]);
    solver_statistics_.lin_res_stat.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+14]);
    solver_statistics_.lin_res_eq.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+15]);
    solver_statistics_.lin_res_ineq.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+16]);
    solver_statistics_.lin_res_comp.push_back(ocp_qp_ipm_ws_ptr->stat[stat_m*i+17]);
  }

  // get hpipm status
  int hpipm_status;
  d_ocp_qp_ipm_get_status(ocp_qp_ipm_ws_wrapper_.get(), &hpipm_status);
  if (0 <= hpipm_status && hpipm_status <= 3) {
    return static_cast<HpipmStatus>(hpipm_status);
  }
  else {
    return HpipmStatus::UnknownFailure;
  }
}


const OcpQpIpmSolverSettings& OcpQpIpmSolver::getIpmSolverSettings() const {
  return solver_settings_;
}


const OcpQpIpmSolverStatistics& OcpQpIpmSolver::getSolverStatistics() const {
  return solver_statistics_;
}

} // namespace hpipm