#ifndef HPIPM_CPP_OCP_QP_IPM_SOLVER_STATISTICS_HPP_
#define HPIPM_CPP_OCP_QP_IPM_SOLVER_STATISTICS_HPP_

#include <vector>
#include <string>
#include <iostream>


namespace hpipm {

///
/// @class OcpQpIpmSolverStatistics
/// @brief Ipm solver statistics.
///
struct OcpQpIpmSolverStatistics {
  ///
  /// @brief Number of iterations.
  ///
  int iter = 0;

  ///
  /// @brief Maximum residual in statistics.
  ///
  double max_res_stat = 0.0;

  ///
  /// @brief Maximum residual in equality constraints.
  ///
  double max_res_eq = 0.0;

  ///
  /// @brief Maximum residual in inequality constraints.
  ///
  double max_res_ineq = 0.0;

  ///
  /// @brief Maximum residual in complementary slackness.
  ///
  double max_res_comp = 0.0;

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

  ///
  /// @brief Resizes std::vector member variables.
  /// @param[in] size Size of std::vector member variables.
  ///
  void resize(const size_t size);

  ///
  /// @brief Reserve std::vector member variables.
  /// @param[in] size Size of std::vector member variables.
  ///
  void reserve(const size_t size);

  ///
  /// @brief Clears std::vector member variables.
  ///
  void clear();

  void disp(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const OcpQpIpmSolverStatistics& stats);

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_SOLVER_STATISTICS_HPP_