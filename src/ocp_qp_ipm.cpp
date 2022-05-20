#include "hpipm-cpp/ocp_qp_ipm.hpp"

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


ocp_qp_ipm::~ocp_qp_ipm() {
  if (memory_ ) {
	  free(memory_);
  }
}


void ocp_qp_ipm::createHpipmData(ocp_qp_dim& dim, ocp_qp_ipm_arg& ipm_arg) {
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_ws_memsize(dim.to_hpipm(), 
  														                             ipm_arg.to_hpipm());
  if (memory_ && new_memsize >= memsize_) {
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


HpipmStatus ocp_qp_ipm::solve(ocp_qp& qp, ocp_qp_sol& qp_sol, 
                              ocp_qp_ipm_arg& ipm_arg) {
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


ocp_qp_ipm_stat ocp_qp_ipm::getStat() {
  ocp_qp_ipm_stat stat; 
  d_ocp_qp_ipm_get_iter(&ocp_qp_ipm_ws_hpipm_, &stat.iter);
  d_ocp_qp_ipm_get_max_res_stat(&ocp_qp_ipm_ws_hpipm_, &stat.max_res_stat);
  d_ocp_qp_ipm_get_max_res_eq(&ocp_qp_ipm_ws_hpipm_, &stat.max_res_eq);
  d_ocp_qp_ipm_get_max_res_ineq(&ocp_qp_ipm_ws_hpipm_, &stat.max_res_ineq);
  d_ocp_qp_ipm_get_max_res_comp(&ocp_qp_ipm_ws_hpipm_, &stat.max_res_comp);
  const int stat_m = 18;
  for (int i=0; i<=stat.iter+1; ++i) {
    stat.alpha_aff.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+0]);
    stat.mu_aff.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+1]);
    stat.sigma.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+2]);
    stat.alpha_prim.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+3]);
    stat.alpha_dual.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+4]);
    stat.mu.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+5]);
    stat.res_stat.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+6]);
    stat.res_eq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+7]);
    stat.res_ineq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+8]);
    stat.res_comp.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+9]);
    stat.obj.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+10]);
    stat.lq_fact.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+11]);
    stat.itref_pred.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+12]);
    stat.itref_corr.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+13]);
    stat.lin_res_stat.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+14]);
    stat.lin_res_eq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+15]);
    stat.lin_res_ineq.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+16]);
    stat.lin_res_comp.push_back(ocp_qp_ipm_ws_hpipm_.stat[stat_m*i+17]);
  }
  return stat;
}

} // namespace hpipm