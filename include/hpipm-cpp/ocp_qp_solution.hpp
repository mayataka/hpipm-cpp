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

///
/// @class OcpQpSolution
/// @brief Solution of the OCP-QP problem.
///
struct OcpQpSolution {
public:
  ///
  /// @brief Constructor.
  /// @param[in] dim Dimension of the OCP-QP problem.
  ///
  OcpQpSolution(const OcpQpDim& dim);

  ///
  /// @brief Default constructor. 
  ///
  OcpQpSolution() = default;

  ///
  /// @brief Destructor.
  ///
  ~OcpQpSolution() = default;

  ///
  /// @brief Default copy constructor.
  ///
  OcpQpSolution(const OcpQpSolution&) = default;

  ///
  /// @brief Default copy assign operator.
  ///
  OcpQpSolution& operator=(const OcpQpSolution&) = default;

  ///
  /// @brief Prohibit move constructor.
  ///
  OcpQpSolution(OcpQpSolution&&) noexcept = delete;

  ///
  /// @brief Prohibit move assign operator.
  ///
  OcpQpSolution& operator=(OcpQpSolution&&) noexcept = delete;

  ///
  /// @brief Resizes the solution.
  /// @param[in] dim Dimension of the OCP-QP problem.
  ///
  void resize(const OcpQpDim& dim);

  ///
  /// @brief Gets the wrapper of hpipm's resource. 
  ///
  d_ocp_qp_sol_wrapper& getHpipmWrapper();

  ///
  /// @brief Retrive x, u, and pi from the hpipm's resource. 
  ///
  void retriveSolution();

  ///
  /// @brief State. 
  ///
  std::vector<Eigen::VectorXd> x;

  ///
  /// @brief Control input. 
  ///
  std::vector<Eigen::VectorXd> u;

  ///
  /// @brief Costate (the Lagrange multiplier w.r.t the state equation). 
  ///
  std::vector<Eigen::VectorXd> pi;

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

  void resize();
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_SOLUTION_HPP_