#include "hpipm-cpp/hpipm-cpp.hpp"

#include <chrono>
#include <iostream>
#include <vector>

#include "Eigen/Core"


int main() {
  // setup QP
  const int N = 20;
  hpipm::OcpQpDim dim(N);
  dim.nx   = std::vector<int>(N+1, 12);
  dim.nu   = std::vector<int>(N, 4);
  dim.nbx  = std::vector<int>(N+1, 3);
  dim.nbx[0] = 12;
  dim.nbu  = std::vector<int>(N, 4);
  dim.ng   = std::vector<int>(N+1, 0);
  dim.nsbx = std::vector<int>(N+1, 0);
  dim.nsbu = std::vector<int>(N, 0);
  dim.nsg  = std::vector<int>(N+1, 0);

  hpipm::OcpQp qp(dim);
  // initial state
  qp.x0 << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
  // dynamics
  Eigen::MatrixXd A(12, 12), B(12, 4);
  A << 1.,      0.,     0., 0., 0., 0., 0.1,     0.,     0.,  0.,     0.,     0.    ,
       0.,      1.,     0., 0., 0., 0., 0.,      0.1,    0.,  0.,     0.,     0.    ,
       0.,      0.,     1., 0., 0., 0., 0.,      0.,     0.1, 0.,     0.,     0.    ,
       0.0488,  0.,     0., 1., 0., 0., 0.0016,  0.,     0.,  0.0992, 0.,     0.    ,
       0.,     -0.0488, 0., 0., 1., 0., 0.,     -0.0016, 0.,  0.,     0.0992, 0.    ,
       0.,      0.,     0., 0., 0., 1., 0.,      0.,     0.,  0.,     0.,     0.0992,
       0.,      0.,     0., 0., 0., 0., 1.,      0.,     0.,  0.,     0.,     0.    ,
       0.,      0.,     0., 0., 0., 0., 0.,      1.,     0.,  0.,     0.,     0.    ,
       0.,      0.,     0., 0., 0., 0., 0.,      0.,     1.,  0.,     0.,     0.    ,
       0.9734,  0.,     0., 0., 0., 0., 0.0488,  0.,     0.,  0.9846, 0.,     0.    ,
       0.,     -0.9734, 0., 0., 0., 0., 0.,     -0.0488, 0.,  0.,     0.9846, 0.    ,
       0.,      0.,     0., 0., 0., 0., 0.,      0.,     0.,  0.,     0.,     0.9846;
  B << 0.,      -0.0726,  0.,     0.0726,
      -0.0726,  0.,      0.0726, 0.    ,
      -0.0152,  0.0152, -0.0152, 0.0152,
      -0.,     -0.0006, -0.,     0.0006,
       0.0006,   0.,     -0.0006, 0.0000,
       0.0106,   0.0106,  0.0106, 0.0106,
       0,       -1.4512,  0.,     1.4512,
      -1.4512,  0.,      1.4512, 0.    ,
      -0.3049,  0.3049, -0.3049, 0.3049,
      -0.,     -0.0236,  0.,     0.0236,
       0.0236,   0.,     -0.0236, 0.    ,
       0.2107,   0.2107,  0.2107, 0.2107;
  const Eigen::VectorXd b = Eigen::VectorXd::Zero(12);
  for (int i=0; i<N; ++i) {
    qp.A[i] = A;
    qp.B[i] = B;
    qp.b[i] = b;
  }
  // cost
  Eigen::MatrixXd Q(12, 12), S(4, 12), R(4, 4);
  Q.setZero(); Q.diagonal() << 0, 0, 10., 10., 10., 10., 0, 0, 0, 5., 5., 5.;
  S.setZero();
  R.setZero(); R.diagonal() << 0.1, 0.1, 0.1, 0.1;
  Eigen::VectorXd x_ref(12);
  x_ref <<  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
  const Eigen::VectorXd q = - Q * x_ref;
  const Eigen::VectorXd r = Eigen::VectorXd::Zero(4);
  for (int i=0; i<N; ++i) {
    qp.Q[i] = Q;
    qp.R[i] = R;
    qp.S[i] = S;
    qp.q[i] = q;
    qp.r[i] = r;
  }
  qp.Q[N] = Q;
  qp.q[N] = q;
  // constraints
  const bool use_mask_for_one_sided_constraints = true;
  qp.idxbx[0] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  qp.lbx[0] = qp.x0;
  qp.ubx[0] = qp.x0;
  if (use_mask_for_one_sided_constraints) {
    qp.ubx_mask[0] = Eigen::VectorXd(); // there is no mask on initial stage
  }
  for (int i=1; i<=N; ++i) {
    constexpr double soft_inf = 1.0e10;
    qp.idxbx[i] = {0, 1, 5};
    qp.lbx[i] = (Eigen::VectorXd(3) << -M_PI/6.0, -M_PI/6.0, -1.0).finished();
    qp.ubx[i] = (Eigen::VectorXd(3) << M_PI/6.0, M_PI/6.0, soft_inf).finished();
    if (use_mask_for_one_sided_constraints) {
      qp.ubx_mask[i] = (Eigen::VectorXd(3) << 1.0, 1.0, 0.0).finished(); 
      // this mask disables upper bound by ubx[2]
    }
  }
  for (int i=0; i<N; ++i) {
    constexpr double u0 = 10.5916;
    qp.idxbu[i] = {0, 1, 2, 3};
    qp.lbu[i] = (Eigen::VectorXd(4) << 9.6-u0, 9.6-u0, 9.6-u0, 9.6-u0).finished();
    qp.ubu[i] = (Eigen::VectorXd(4) << 13.0-u0, 13.0-u0, 13.0-u0, 13.0-u0).finished();
  }

  hpipm::OcpQpIpmSolverSettings ipm_solver_settings;
  ipm_solver_settings.iter_max = 30;
  ipm_solver_settings.alpha_min = 1e-8;
  ipm_solver_settings.mu0 = 1e2;
  ipm_solver_settings.tol_stat = 1e-04;
  ipm_solver_settings.tol_eq = 1e-04;
  ipm_solver_settings.tol_ineq = 1e-04;
  ipm_solver_settings.tol_comp = 1e-04;
  ipm_solver_settings.reg_prim = 1e-12;
  ipm_solver_settings.warm_start = 1;
  ipm_solver_settings.pred_corr = 1;
  ipm_solver_settings.ric_alg = 0;
  ipm_solver_settings.split_step = 1;

  hpipm::OcpQpSolution solution(dim);
  hpipm::OcpQpIpmSolver solver(dim, ipm_solver_settings);

  Eigen::VectorXd u0(4);
  Eigen::VectorXd x(12);
  x << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

  const int sim_steps = 50;
  for (int t=0; t<sim_steps; ++t) {
    std::cout << "t: " << t << ", x: " << x.transpose() << std::endl;
    qp.x0 = x;
    if (solver.solve(qp, solution) != hpipm::HpipmStatus::Success) return 1;
    u0 = solution.u[0];
    x = A * x + B * u0 + b;
  }

  std::cout << "t: " << sim_steps << ", x: " << x.transpose() << std::endl;
  return 0;
}