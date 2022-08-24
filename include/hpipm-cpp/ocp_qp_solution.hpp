#ifndef HPIPM_CPP_OCP_QP_SOLUTION_HPP_
#define HPIPM_CPP_OCP_QP_SOLUTION_HPP_

#include <vector>
#include <string>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_sol.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/d_ocp_qp_sol_wrapper.hpp"


namespace hpipm {

struct OcpQpSolution {
public:
  OcpQpSolution(const OcpQpDim& dim);

  OcpQpSolution() = default;

  ~OcpQpSolution() = default;

  OcpQpSolution(const OcpQpSolution&) = default;

  OcpQpSolution& operator=(const OcpQpSolution&) = default;

  OcpQpSolution(OcpQpSolution&&) noexcept = delete;

  OcpQpSolution& operator=(OcpQpSolution&&) noexcept = delete;

  std::vector<std::string> checkSize(const OcpQpDim& dim) const;

  void resize(const OcpQpDim& dim);

  d_ocp_qp_sol_wrapper& getHpipmWrapper();

  void retriveSolution();

  std::vector<Eigen::VectorXd> x;
  std::vector<Eigen::VectorXd> u;
  std::vector<Eigen::VectorXd> pi; // the Lagrange multiplier w.r.t. the state equation

  // TODO: get the following variables from hpipm
  // std::vector<Eigen::VectorXd> sl; // slack lower 
  // std::vector<Eigen::VectorXd> su; // slack upper 
  // std::vector<Eigen::VectorXd> lam_lb; // the Lagrange multiplier w.r.t. the lower box constraint 
  // std::vector<Eigen::VectorXd> lam_ub; // the Lagrange multiplier w.r.t. the upper box constraint
  // std::vector<Eigen::VectorXd> lam_lg; // the Lagrange multiplier w.r.t. the lower constraint
  // std::vector<Eigen::VectorXd> lam_ug; // the Lagrange multiplier w.r.t. the upper constraint
  // std::vector<Eigen::VectorXd> lam_ls; // the Lagrange multiplier w.r.t. the lower soft constraint
  // std::vector<Eigen::VectorXd> lam_us; // the Lagrange multiplier w.r.t. the upper soft constraint

private:
  OcpQpDim dim_;
  d_ocp_qp_sol_wrapper ocp_qp_sol_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_SOLUTION_HPP_