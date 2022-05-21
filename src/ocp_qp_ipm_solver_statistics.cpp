#include "hpipm-cpp/ocp_qp_ipm_solver_statistics.hpp"

#include <iomanip>


namespace hpipm {

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