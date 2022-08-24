#include "hpipm-cpp/ocp_qp_ipm_solver.hpp"

#include <algorithm>
#include <cstdlib>


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


OcpQpIpmSolver::OcpQpIpmSolver(const OcpQpDim& dim, 
                               const OcpQpIpmSolverSettings& ipm_solver_settings) 
  : solver_statistics_(),
    dim_(dim),
    ipm_solver_settings_(ipm_solver_settings),
    ocp_qp_ipm_ws_wrapper_() {
  ocp_qp_ipm_ws_wrapper_.resize(dim_.getHpipmWrapper(), 
                                ipm_solver_settings_.getHpipmWrapper());
}


void OcpQpIpmSolver::resize(const OcpQpDim& dim) {
  dim_ = dim;
  ocp_qp_ipm_ws_wrapper_.resize(dim_.getHpipmWrapper(), 
                                ipm_solver_settings_.getHpipmWrapper());
}


void OcpQpIpmSolver::setSolverSettings(const OcpQpIpmSolverSettings& ipm_solver_settings) {
  ipm_solver_settings_ = ipm_solver_settings;
  ocp_qp_ipm_ws_wrapper_.resize(dim_.getHpipmWrapper(), 
                                ipm_solver_settings_.getHpipmWrapper());
}


HpipmStatus OcpQpIpmSolver::solve(OcpQp& qp, OcpQpSolution& qp_sol) {
  // solve QP
  d_ocp_qp_ipm_solve(qp.getHpipmWrapper().get(), qp_sol.getHpipmWrapper().get(), 
                     ipm_solver_settings_.getHpipmWrapper().get(), 
                     ocp_qp_ipm_ws_wrapper_.get());
  qp_sol.retriveSolution();

  // get solver statistics
  d_ocp_qp_ipm_ws* ws_ptr = ocp_qp_ipm_ws_wrapper_.get();
  d_ocp_qp_ipm_get_iter(ws_ptr, &solver_statistics_.iter);
  d_ocp_qp_ipm_get_max_res_stat(ws_ptr, &solver_statistics_.max_res_stat);
  d_ocp_qp_ipm_get_max_res_eq(ws_ptr, &solver_statistics_.max_res_eq);
  d_ocp_qp_ipm_get_max_res_ineq(ws_ptr, &solver_statistics_.max_res_ineq);
  d_ocp_qp_ipm_get_max_res_comp(ws_ptr, &solver_statistics_.max_res_comp);
  const int stat_m = 18;
  solver_statistics_.clear();
  solver_statistics_.reserve(solver_statistics_.iter+2);
  for (int i=0; i<=solver_statistics_.iter+1; ++i) {
    solver_statistics_.alpha_aff.push_back(ws_ptr->stat[stat_m*i+0]);
    solver_statistics_.mu_aff.push_back(ws_ptr->stat[stat_m*i+1]);
    solver_statistics_.sigma.push_back(ws_ptr->stat[stat_m*i+2]);
    solver_statistics_.alpha_prim.push_back(ws_ptr->stat[stat_m*i+3]);
    solver_statistics_.alpha_dual.push_back(ws_ptr->stat[stat_m*i+4]);
    solver_statistics_.mu.push_back(ws_ptr->stat[stat_m*i+5]);
    solver_statistics_.res_stat.push_back(ws_ptr->stat[stat_m*i+6]);
    solver_statistics_.res_eq.push_back(ws_ptr->stat[stat_m*i+7]);
    solver_statistics_.res_ineq.push_back(ws_ptr->stat[stat_m*i+8]);
    solver_statistics_.res_comp.push_back(ws_ptr->stat[stat_m*i+9]);
    solver_statistics_.obj.push_back(ws_ptr->stat[stat_m*i+10]);
    solver_statistics_.lq_fact.push_back(ws_ptr->stat[stat_m*i+11]);
    solver_statistics_.itref_pred.push_back(ws_ptr->stat[stat_m*i+12]);
    solver_statistics_.itref_corr.push_back(ws_ptr->stat[stat_m*i+13]);
    solver_statistics_.lin_res_stat.push_back(ws_ptr->stat[stat_m*i+14]);
    solver_statistics_.lin_res_eq.push_back(ws_ptr->stat[stat_m*i+15]);
    solver_statistics_.lin_res_ineq.push_back(ws_ptr->stat[stat_m*i+16]);
    solver_statistics_.lin_res_comp.push_back(ws_ptr->stat[stat_m*i+17]);
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


const OcpQpDim& OcpQpIpmSolver::dim() const {
  return dim_;
}


const OcpQpIpmSolverSettings& OcpQpIpmSolver::ipmSolverSettings() const {
  return ipm_solver_settings_;
}


const OcpQpIpmSolverStatistics& OcpQpIpmSolver::getSolverStatistics() const {
  return solver_statistics_;
}

} // namespace hpipm