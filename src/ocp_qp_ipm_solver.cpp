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


OcpQpIpmSolver::~OcpQpIpmSolver() {
  if (memory_ ) {
	  free(memory_);
  }
}


void OcpQpIpmSolver::createHpipmData(OcpQpDim& dim, 
                                     OcpQpIpmSolverSettings& ipm_arg) {
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_ws_memsize(dim.to_hpipm(), 
  														                             ipm_arg.to_hpipm());
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_ipm_ws_create(dim.to_hpipm(), ipm_arg.to_hpipm(), 
                           &ocp_qp_ipm_ws_hpipm_, memory_);
  }
}


HpipmStatus OcpQpIpmSolver::solve(OcpQp& qp, OcpQpSolution& qp_sol, 
                                  OcpQpIpmSolverSettings& ipm_arg) {
  d_ocp_qp_ipm_solve(qp.to_hpipm(), qp_sol.to_hpipm(), ipm_arg.to_hpipm(), 
                     &ocp_qp_ipm_ws_hpipm_);
  int hpipm_status;
  d_ocp_qp_ipm_get_status(&ocp_qp_ipm_ws_hpipm_, &hpipm_status);
  if (0 <= hpipm_status && hpipm_status <= 3) {
    return static_cast<HpipmStatus>(hpipm_status);
  }
  else {
    return HpipmStatus::UnknownFailure;
  }
}


OcpQpIpmSolverStatistics OcpQpIpmSolver::getSolverStatistics() {
  OcpQpIpmSolverStatistics stats; 
  d_ocp_qp_ipm_get_iter(&ocp_qp_ipm_ws_hpipm_, &stats.iter);
  d_ocp_qp_ipm_get_max_res_stat(&ocp_qp_ipm_ws_hpipm_, &stats.max_res_stat);
  d_ocp_qp_ipm_get_max_res_eq(&ocp_qp_ipm_ws_hpipm_, &stats.max_res_eq);
  d_ocp_qp_ipm_get_max_res_ineq(&ocp_qp_ipm_ws_hpipm_, &stats.max_res_ineq);
  d_ocp_qp_ipm_get_max_res_comp(&ocp_qp_ipm_ws_hpipm_, &stats.max_res_comp);
  const int stat_m = 18;
  for (int i=0; i<=stats.iter+1; ++i) {
    stats.alpha_aff.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+0]);
    stats.mu_aff.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+1]);
    stats.sigma.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+2]);
    stats.alpha_prim.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+3]);
    stats.alpha_dual.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+4]);
    stats.mu.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+5]);
    stats.res_stat.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+6]);
    stats.res_eq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+7]);
    stats.res_ineq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+8]);
    stats.res_comp.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+9]);
    stats.obj.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+10]);
    stats.lq_fact.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+11]);
    stats.itref_pred.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+12]);
    stats.itref_corr.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+13]);
    stats.lin_res_stat.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+14]);
    stats.lin_res_eq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+15]);
    stats.lin_res_ineq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+16]);
    stats.lin_res_comp.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+17]);
  }
  return stats;
}

} // namespace hpipm