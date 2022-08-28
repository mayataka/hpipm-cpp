#include "hpipm-cpp/ocp_qp_ipm_solver_statistics.hpp"

#include <iomanip>


namespace hpipm {

void OcpQpIpmSolverStatistics::resize(const size_t size) {
  alpha_aff.resize(size);
  mu_aff.resize(size);
  sigma.resize(size);
  alpha_prim.resize(size);
  alpha_dual.resize(size);
  mu.resize(size);
  res_stat.resize(size);
  res_eq.resize(size);
  res_ineq.resize(size);
  res_comp.resize(size);
  obj.resize(size);
  lq_fact.resize(size);
  itref_pred.resize(size);
  itref_corr.resize(size);
  lin_res_stat.resize(size);
  lin_res_eq.resize(size);
  lin_res_ineq.resize(size);
  lin_res_comp.resize(size);
}


void OcpQpIpmSolverStatistics::reserve(const size_t size) {
  alpha_aff.reserve(size);
  mu_aff.reserve(size);
  sigma.reserve(size);
  alpha_prim.reserve(size);
  alpha_dual.reserve(size);
  mu.reserve(size);
  res_stat.reserve(size);
  res_eq.reserve(size);
  res_ineq.reserve(size);
  res_comp.reserve(size);
  obj.reserve(size);
  lq_fact.reserve(size);
  itref_pred.reserve(size);
  itref_corr.reserve(size);
  lin_res_stat.reserve(size);
  lin_res_eq.reserve(size);
  lin_res_ineq.reserve(size);
  lin_res_comp.reserve(size);
}


void OcpQpIpmSolverStatistics::clear() {
  alpha_aff.clear();
  mu_aff.clear();
  sigma.clear();
  alpha_prim.clear();
  alpha_dual.clear();
  mu.clear();
  res_stat.clear();
  res_eq.clear();
  res_ineq.clear();
  res_comp.clear();
  obj.clear();
  lq_fact.clear();
  itref_pred.clear();
  itref_corr.clear();
  lin_res_stat.clear();
  lin_res_eq.clear();
  lin_res_ineq.clear();
  lin_res_comp.clear();
}


void OcpQpIpmSolverStatistics::disp(std::ostream& os) const {
  os << "================== Hpipm Solver Statistics ==================" << std::endl;
  os << "ipm iter: " << iter << std::endl;
  os << std::setprecision(5) << std::scientific;
  os << "max_res_stat: " << max_res_stat << std::endl;
  os << "max_res_eq:   " << max_res_eq << std::endl;
  os << "max_res_ineq: " << max_res_ineq << std::endl;
  os << "max_res_comp: " << max_res_comp << std::endl;
  os << "alpha_aff    " 
     << "mu_aff       " 
     << "sigma        "
     << "alpha_prim   " 
     << "alpha_dual   "
     << "mu           "
     << "res_stat     " 
     << "res_eq       "
     << "res_ineq     "
     << "res_comp     "
     << "obj	        "
     << "lq fact	    "
     << "itref pred   "  
     << "itref corr   "
     << "lin res stat "  
     << "lin res eq   " 
     << "lin res ineq " 
     << "lin res comp " << std::endl;
  if (iter > 0) {
    for (int i=0; i<=iter; ++i) {
      os << alpha_aff[i]    << "  " 
         << mu_aff[i]       << "  " 
         << sigma[i]        << "  " 
         << alpha_prim[i]   << "  " 
         << alpha_dual[i]   << "  "
         << mu[i]           << "  " 
         << res_stat[i]     << "  " 
         << res_eq[i]       << "  " 
         << res_ineq[i]     << "  " 
         << res_comp[i]     << "  " 
         << obj[i]          << "  " 
         << lq_fact[i]      << "  " 
         << itref_pred[i]   << "  " 
         << itref_corr[i]   << "  " 
         << lin_res_stat[i] << "  " 
         << lin_res_eq[i]   << "  " 
         << lin_res_ineq[i] << "  " 
         << lin_res_comp[i] << std::endl;
    }
  }
}


std::ostream& operator<<(std::ostream& os, const OcpQpIpmSolverStatistics& stats) {
  stats.disp(os);
  return os;
}

} // namespace hpipm