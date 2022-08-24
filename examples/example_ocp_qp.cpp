#include "hpipm-cpp/hpipm-cpp.hpp"

#include "getting_started_data.hpp"

#include <iostream>
#include <vector>
#include "Eigen/Core"


int main() {
  QPSize qp_size;
  hpipm::OcpQpDim dim(qp_size.N);
  dim.nx   = qp_size.nx;
  dim.nu   = qp_size.nu;
  dim.nbx  = qp_size.nbx;
  dim.nbu  = qp_size.nbu;
  dim.ng   = qp_size.ng;
  dim.nsbx = qp_size.nsbx;
  dim.nsbu = qp_size.nsbu;
  dim.nsg  = qp_size.nsg;

  QPData qp_data;
  hpipm::OcpQp qp(dim);
  // initial state
  qp.x0 = qp_data.x0;
  // dynamics
  for (int i=0; i<dim.N; ++i) {
    qp.A[i] = qp_data.A;
    qp.B[i] = qp_data.B;
    qp.b[i] = qp_data.b;
  }
  // cost
  for (int i=0; i<dim.N; ++i) {
    qp.Q[i] = qp_data.Q;
    qp.R[i] = qp_data.R;
    qp.S[i] = qp_data.S;
    qp.q[i] = qp_data.q;
    qp.r[i] = qp_data.r;
  }
  qp.Q[dim.N] = qp_data.Q;
  qp.q[dim.N] = qp_data.q;
  // constraints on the state
  for (int i=1; i<=dim.N; ++i) {
    qp.idxbx[i] = qp_data.idxbx;
    qp.lbx[i]   = qp_data.lbx;
    qp.ubx[i]   = qp_data.ubx;
  }

  IPMArg ipm_arg;
  hpipm::OcpQpIpmSolverSettings ipm_solver_settings;
  ipm_solver_settings.mode       = static_cast<hpipm::HpipmMode>(ipm_arg.mode);
  ipm_solver_settings.iter_max   = ipm_arg.iter_max;
  ipm_solver_settings.alpha_min  = ipm_arg.alpha_min;
  ipm_solver_settings.mu0        = ipm_arg.mu0;
  ipm_solver_settings.tol_stat   = ipm_arg.tol_stat;
  ipm_solver_settings.tol_eq     = ipm_arg.tol_eq;
  ipm_solver_settings.tol_ineq   = ipm_arg.tol_ineq;
  ipm_solver_settings.tol_comp   = ipm_arg.tol_comp;
  ipm_solver_settings.reg_prim   = ipm_arg.reg_prim;
  ipm_solver_settings.warm_start = ipm_arg.warm_start;
  ipm_solver_settings.pred_corr  = ipm_arg.pred_corr;
  ipm_solver_settings.ric_alg    = ipm_arg.ric_alg;
  ipm_solver_settings.split_step = ipm_arg.split_step;

  hpipm::OcpQpSolution solution(dim);
  hpipm::OcpQpIpmSolver solver(dim, ipm_solver_settings);
  const auto res = solver.solve(qp, solution);
  std::cout << "QP result: " << res << std::endl;

  std::cout << "OCP QP primal solution: " << std::endl;
  for (int i=0; i<=dim.N; ++i) {
    std::cout << "x[" << i << "]: " << solution.x[i].transpose() << std::endl;
  }
  for (int i=0; i<dim.N; ++i) {
    std::cout << "u[" << i << "]: " << solution.u[i].transpose() << std::endl;
  }

  std::cout << "OCP QP dual solution (Lagrange multipliers): " << std::endl;
  for (int i=0; i<dim.N; ++i) {
    std::cout << "pi[" << i << "]: " << solution.pi[i].transpose() << std::endl;
  }

  const auto& stat = solver.getSolverStatistics();
  std::cout << stat << std::endl; 

  return 0;
}