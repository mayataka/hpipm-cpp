#include "hpipm-cpp/hpipm-cpp.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include "Eigen/Core"


int main() {
  // setup QP
  hpipm::OcpQpDim dim;
  dim.N    = 20;
  dim.nx   = std::vector<int>(dim.N+1, 12);
  dim.nu   = std::vector<int>(dim.N, 4);
  dim.nbx  = std::vector<int>(dim.N+1, 3);
  dim.nbx[0] = 12;
  dim.nbu  = std::vector<int>(dim.N, 4);
  dim.ng   = std::vector<int>(dim.N+1, 0);
  dim.nsbx = std::vector<int>(dim.N+1, 0);
  dim.nsbu = std::vector<int>(dim.N, 0);
  dim.nsg  = std::vector<int>(dim.N+1, 0);
  const auto dim_err_msg = dim.checkSize();
  if (!dim_err_msg.empty()) {
    for (const auto& e : dim_err_msg) {
      std::cout << e << std::endl;
    }
    return 1;
  }
  dim.createHpipmData();

  hpipm::OcpQp qp;
  // initial state
  qp.x0.resize(12);
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
  for (int i=0; i<dim.N; ++i) {
    qp.A.push_back(A);
    qp.B.push_back(B);
    qp.b.push_back(b);
  }
  // cost
  Eigen::MatrixXd Q(12, 12), S(4, 12), R(4, 4);
  Q.setZero(); Q.diagonal() << 0, 0, 10., 10., 10., 10., 0, 0, 0, 5., 5., 5.;
  S.setZero();
  R.setZero(); R.diagonal() << 0.1, 0.1, 0.1, 0.1;
  Eigen::VectorXd x_ref(12);
  x_ref <<  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
  const Eigen::VectorXd q = - Q* x_ref;
  const Eigen::VectorXd r = Eigen::VectorXd::Zero(4);
  for (int i=0; i<dim.N; ++i) {
    qp.Q.push_back(Q);
    qp.R.push_back(R);
    qp.S.push_back(S);
    qp.q.push_back(q);
    qp.r.push_back(r);
  }
  qp.Q.push_back(Q);
  qp.q.push_back(q);
  // constraints
  qp.idxbx.push_back({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
  qp.lbx.push_back(qp.x0);
  qp.ubx.push_back(qp.x0);
  for (int i=1; i<=dim.N; ++i) {
    // constexpr double soft_inf = 1.0e10;
    constexpr double soft_inf = 1.0e03;
    qp.idxbx.push_back({0, 1, 5});
    qp.lbx.push_back((Eigen::VectorXd(3) << -M_PI/6.0, -M_PI/6.0, -1.0).finished());
    qp.ubx.push_back((Eigen::VectorXd(3) << M_PI/6.0, M_PI/6.0, soft_inf).finished());
  }
  for (int i=0; i<dim.N; ++i) {
    constexpr double u0 = 10.5916;
    qp.idxbu.push_back({0, 1, 2, 3});
    qp.lbu.push_back((Eigen::VectorXd(4) << 9.6-u0, 9.6-u0, 9.6-u0, 9.6-u0).finished());
    qp.ubu.push_back((Eigen::VectorXd(4) << 13.0-u0, 13.0-u0, 13.0-u0, 13.0-u0).finished());
  }
  const auto qp_err_msg = qp.checkSize(dim);
  if (!qp_err_msg.empty()) {
    for (const auto& e : qp_err_msg) {
      std::cout << e << std::endl;
    }
    return 1;
  }
  qp.createHpipmData(dim);

  hpipm::OcpQpIpmSolverSettings arg;
  arg.iter_max = 30;
  arg.alpha_min = 1e-8;
  arg.mu0 = 1e2;
  arg.tol_stat = 1e-04;
  arg.tol_eq = 1e-04;
  arg.tol_ineq = 1e-04;
  arg.tol_comp = 1e-04;
  arg.reg_prim = 1e-12;
  arg.warm_start = 1;
  arg.pred_corr = 1;
  arg.ric_alg = 0;
  arg.split_step = 1;
  arg.createHpipmData(dim);

  hpipm::OcpQpSolution sol;
  const auto sol_err_msg = sol.checkSize(dim);
  if (!sol_err_msg.empty()) {
    for (const auto& e : sol_err_msg) {
      std::cout << e << std::endl;
    }
    return 1;
  }
  sol.createHpipmData(dim);

  hpipm::OcpQpIpmSolver solver;
  solver.createHpipmData(dim, arg);

  Eigen::VectorXd u0(4);
  Eigen::VectorXd x(12);
  x << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

  // const int num_tests = 100;
  // const auto begin = std::chrono::high_resolution_clock::now();
  // for (int test=0; test<num_tests; ++test) {

  const int sim_steps = 50;
  for (int t=0; t<sim_steps; ++t) {
    std::cout << "t: " << t << ", x: " << x.transpose() << std::endl;
    qp.x0 = x;
    qp.createHpipmData(dim);
    if (solver.solve(qp, sol, arg) != hpipm::HpipmStatus::Success) return 1;
    sol.getSolutionFromHpipm(dim);
    u0 = sol.u[0];
    x = A * x + B * u0 + b;
  }

  }
  // const auto end = std::chrono::high_resolution_clock::now();
  // const auto timing = std::chrono::duration<double, std::milli>(end - begin);
  // std::cout << "CPU time: " << timing.count() << " [ms]" << std::endl;

  std::cout << "t: " << sim_steps << ", x: " << x.transpose() << std::endl;
  return 0;
}