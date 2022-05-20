#ifndef HPIPM_CPP_OCP_QP_IPM_STAT_HPP_
#define HPIPM_CPP_OCP_QP_IPM_STAT_HPP_

#include <vector>
#include <string>
#include <iostream>

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}


namespace hpipm {

struct ocp_qp_ipm_stat {
  int iter = 0;
  double max_res_stat = 0.0;
  double max_res_eq = 0.0;
  double max_res_ineq = 0.0;
  double max_res_comp = 0.0;
  // stat
  std::vector<double> alpha_aff;
  std::vector<double> mu_aff;
  std::vector<double> sigma;
  std::vector<double> alpha_prim;
  std::vector<double> alpha_dual;
  std::vector<double> mu;
  std::vector<double> res_stat;
  std::vector<double> res_eq;
  std::vector<double> res_ineq;
  std::vector<double> res_comp;
  std::vector<double> obj;
  std::vector<double> lq_fact;
  std::vector<double> itref_pred;
  std::vector<double> itref_corr;
  std::vector<double> lin_res_stat;
  std::vector<double> lin_res_eq;
  std::vector<double> lin_res_ineq;
  std::vector<double> lin_res_comp;

  void disp(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const ocp_qp_ipm_stat& stat);

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_STAT_HPP_