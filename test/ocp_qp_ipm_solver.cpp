#include <gtest/gtest.h>
#include <random>
#include <fstream>

#include "hpipm-cpp/hpipm-cpp.hpp"

#include "Eigen/LU"


namespace hpipm {

class OcpQpIpmSolver_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};


TEST_F(OcpQpIpmSolver_test, unconstrained) {
  const int nx = 5;
  const int nu = 3;
  const unsigned int N = 20;

  std::vector<hpipm::OcpQp> qp(N+1);
  for (int i=0; i<N; ++i) {
    qp[i].A = Eigen::MatrixXd::Random(nx, nx);
    qp[i].B = Eigen::MatrixXd::Random(nx, nu);
    qp[i].b = Eigen::VectorXd::Random(nx);
  }
  for (int i=0; i<N; ++i) {
    const Eigen::MatrixXd H = Eigen::MatrixXd::Random(nx+nu, nx+nu);
    const Eigen::MatrixXd HH = H * H.transpose();
    qp[i].Q = HH.bottomRightCorner(nx, nx);
    qp[i].S = HH.topRightCorner(nu, nx);
    qp[i].R = HH.topLeftCorner(nu, nu);
    qp[i].R.diagonal() += Eigen::VectorXd::Random(nu).cwiseAbs().matrix();
    qp[i].q = Eigen::VectorXd::Random(nx);
    qp[i].r = Eigen::VectorXd::Random(nu);
  }
  const Eigen::MatrixXd H = Eigen::MatrixXd::Random(nx, nx);
  qp[N].Q = H * H.transpose();
  qp[N].q = Eigen::VectorXd::Random(nx);

  const Eigen::VectorXd x0 = Eigen::VectorXd::Random(nx);

  hpipm::OcpQpIpmSolverSettings solver_settings;
  solver_settings.mode = hpipm::HpipmMode::Balance;

  std::vector<hpipm::OcpQpSolution> solution(N+1);
  hpipm::OcpQpIpmSolver solver(qp, solver_settings);
  const auto status = solver.solve(x0, qp, solution);
  EXPECT_EQ(status, hpipm::HpipmStatus::Success);
  EXPECT_EQ(solver.getSolverStatistics().iter, 0);
  EXPECT_TRUE(solution[0].x.isApprox(x0));
  std::cout << solver.getSolverStatistics() << std::endl;

  // reference unconstrained Riccati  
  std::vector<Eigen::MatrixXd> P, K;
  std::vector<Eigen::VectorXd> s, k;
  P.resize(N+1);
  s.resize(N+1);
  K.resize(N);
  k.resize(N);
  P[N] = qp[N].Q;
  s[N] = - qp[N].q;
  for (int i=N-1; i>=0; --i) {
    const Eigen::MatrixXd F = qp[i].Q + qp[i].A.transpose() * P[i+1] * qp[i].A;
    const Eigen::MatrixXd H = qp[i].S + qp[i].B.transpose() * P[i+1] * qp[i].A;
    const Eigen::MatrixXd G = qp[i].R + qp[i].B.transpose() * P[i+1] * qp[i].B;
    const Eigen::MatrixXd Ginv = G.inverse();
    K[i] = - Ginv * H;
    k[i] = - Ginv * (qp[i].B.transpose() * P[i+1] * qp[i].b - qp[i].B.transpose() * s[i+1] + qp[i].r);
    P[i] = F - K[i].transpose() * G * K[i];
    s[i] = qp[i].A.transpose() * (s[i+1] - P[i+1] * qp[i].b) - qp[i].q - H.transpose() * k[i];
  }
  std::vector<Eigen::VectorXd> x, u;
  x.resize(N+1);
  u.resize(N);
  x[0] = x0;
  for (int i=0; i<N; ++i) {
    u[i] = K[i] * x[i] + k[i];
    x[i+1] = qp[i].A * x[i] + qp[i].B * u[i] + qp[i].b;
  }
  std::vector<Eigen::VectorXd> lmd;
  lmd.resize(N+1);
  for (int i=0; i<=N; ++i) {
    lmd[i] = P[i] * x[i] - s[i];
  }
  const double prec = 1.0e-10;
  for (int i=0; i<=N; ++i) {
    EXPECT_TRUE(x[i].isApprox(solution[i].x, prec));
  }
  for (int i=0; i<N; ++i) {
    EXPECT_TRUE(u[i].isApprox(solution[i].u, prec));
  }
  for (int i=0; i<=N; ++i) {
    EXPECT_TRUE(lmd[i].isApprox(solution[i].pi, prec));
  }
  for (int i=0; i<=N; ++i) {
    EXPECT_TRUE(P[i].isApprox(solution[i].P, prec));
    EXPECT_TRUE(s[i].isApprox(-solution[i].p, prec));
  }
  for (int i=0; i<N; ++i) {
    EXPECT_TRUE(K[i].isApprox(solution[i].K, prec));
    EXPECT_TRUE(k[i].isApprox(solution[i].k, prec));
  }
}

TEST_F(OcpQpIpmSolver_test, constrained) {
  const int nx = 5;
  const int nu = 3;
  const int ng = 2;
  const unsigned int N = 20;

  std::vector<hpipm::OcpQp> qp(N+1);
  for (int i=0; i<N; ++i) {
    qp[i].A = Eigen::MatrixXd::Random(nx, nx);
    qp[i].B = Eigen::MatrixXd::Random(nx, nu);
    qp[i].b = Eigen::VectorXd::Random(nx);
  }
  for (int i=0; i<N; ++i) {
    const Eigen::MatrixXd H = Eigen::MatrixXd::Random(nx+nu, nx+nu);
    const Eigen::MatrixXd HH = H * H.transpose();
    qp[i].Q = HH.bottomRightCorner(nx, nx);
    qp[i].S = HH.topRightCorner(nu, nx);
    qp[i].R = HH.topLeftCorner(nu, nu);
    qp[i].q = Eigen::VectorXd::Random(nx);
    qp[i].r = Eigen::VectorXd::Random(nu);
  }
  const Eigen::MatrixXd H = Eigen::MatrixXd::Random(nx, nx);
  qp[N].Q = H * H.transpose();
  qp[N].q = Eigen::VectorXd::Random(nx);

  const Eigen::VectorXd x0 = Eigen::VectorXd::Random(nx);

  for (int i=0; i<N; ++i) {
    qp[i].idxbu = {0, 1, 2};
    qp[i].lbu = - Eigen::VectorXd::Random(qp[i].idxbu.size()).cwiseAbs().matrix();
    qp[i].ubu = Eigen::VectorXd::Random(qp[i].idxbu.size()).cwiseAbs().matrix();
  }
  for (int i=1; i<=N; ++i) {
    qp[i].idxbx = {1, 3};
    qp[i].lbx = (Eigen::VectorXd(2) << x0(1), x0(3)).finished() - 10 * Eigen::VectorXd::Random(qp[i].idxbx.size()).cwiseAbs().matrix();
    qp[i].ubx = (Eigen::VectorXd(2) << x0(1), x0(3)).finished() + 10 * Eigen::VectorXd::Random(qp[i].idxbx.size()).cwiseAbs().matrix();
  }
  for (int i=0; i<N; ++i) {
    qp[i].C = Eigen::MatrixXd::Random(ng, nx);
    qp[i].D = Eigen::MatrixXd::Random(ng, nu);
    qp[i].lg = - 10 * Eigen::VectorXd::Random(ng).cwiseAbs().matrix();
    qp[i].ug = 10 * Eigen::VectorXd::Random(ng).cwiseAbs().matrix();
  }
  qp[N].C = Eigen::MatrixXd::Random(ng, nx);
  qp[N].lg = - 10 * Eigen::VectorXd::Random(ng).cwiseAbs().matrix();
  qp[N].ug = 10 * Eigen::VectorXd::Random(ng).cwiseAbs().matrix();

  hpipm::OcpQpIpmSolverSettings solver_settings;
  solver_settings.mode = hpipm::HpipmMode::Balance;

  std::vector<hpipm::OcpQpSolution> solution(N+1);
  hpipm::OcpQpIpmSolver solver(qp, solver_settings);
  const auto status = solver.solve(x0, qp, solution);
  EXPECT_EQ(status, hpipm::HpipmStatus::Success);
  std::cout << solver.getSolverStatistics() << std::endl;
  EXPECT_TRUE(solution[0].x.isApprox(x0));
}

TEST_F(OcpQpIpmSolver_test, compareResults) {
  const unsigned int N = 10;

  std::vector<hpipm::OcpQp> qp(N+1);
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
    qp[i].A = A;
    qp[i].B = B;
    qp[i].b = b;
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
    qp[i].Q = Q;
    qp[i].R = R;
    qp[i].S = S;
    qp[i].q = q;
    qp[i].r = r;
  }
  qp[N].Q = Q;
  qp[N].q = q;
  // constraints
  const bool use_mask_for_one_sided_constraints = true;
  for (int i=1; i<=N; ++i) {
    constexpr double soft_inf = 1.0e10;
    qp[i].idxbx = {0, 1, 5};
    qp[i].lbx = (Eigen::VectorXd(3) << -M_PI/6.0, -M_PI/6.0, -1.0).finished();
    qp[i].ubx = (Eigen::VectorXd(3) << M_PI/6.0, M_PI/6.0, soft_inf).finished();
    if (use_mask_for_one_sided_constraints) {
      qp[i].ubx_mask = (Eigen::VectorXd(3) << 1.0, 1.0, 0.0).finished(); // this mask disables upper bound by ubx[2]
    }
  }
  for (int i=0; i<N; ++i) {
    constexpr double u0 = 10.5916;
    qp[i].idxbu = {0, 1, 2, 3};
    qp[i].lbu = (Eigen::VectorXd(4) << 9.6-u0, 9.6-u0, 9.6-u0, 9.6-u0).finished();
    qp[i].ubu = (Eigen::VectorXd(4) << 13.0-u0, 13.0-u0, 13.0-u0, 13.0-u0).finished();
  }

  hpipm::OcpQpIpmSolverSettings solver_settings;
  solver_settings.mode = hpipm::HpipmMode::Balance;
  solver_settings.iter_max = 30;
  solver_settings.alpha_min = 1e-8;
  solver_settings.mu0 = 1e2;
  solver_settings.tol_stat = 1e-10;
  solver_settings.tol_eq = 1e-10;
  solver_settings.tol_ineq = 1e-10;
  solver_settings.tol_comp = 1e-10;
  solver_settings.reg_prim = 1e-12;
  solver_settings.warm_start = 1;
  solver_settings.pred_corr = 1;
  solver_settings.ric_alg = 0;
  solver_settings.split_step = 1;

  std::vector<hpipm::OcpQpSolution> solution(N+1);
  hpipm::OcpQpIpmSolver solver(qp, solver_settings);

  Eigen::VectorXd u0(4);
  Eigen::VectorXd x(12);
  x << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

  Eigen::VectorXd x0 = x;

  auto loadDataFromFile = [](const std::string& file_path) {
    std::ifstream indata;
    indata.open(file_path);
    std::string line;
    std::vector<double> values;
    uint rows = 0;
    while (std::getline(indata, line)) {
      std::stringstream lineStream(line);
      std::string cell;
      while (std::getline(lineStream, cell, ',')) {
        values.push_back(std::stod(cell));
      }
      ++rows;
    }
    return values;
  };

  auto concatenateSolution = [](const std::vector<hpipm::OcpQpSolution>& sol) {
    const int N = sol.size() - 1;
    Eigen::VectorXd ret((N+1)*12 + N*4);
    for (int i=0; i<N+1; ++i) {
      ret.segment(i*12, 12) = sol[i].x;
    }
    for (int i=0; i<N; ++i) {
      ret.segment((N+1)*12+i*4, 4) = sol[i].u;
    }
    return ret;
  };

  const int sim_steps = 15;
  for (int t=0; t<sim_steps; ++t) {
    x0 = x;
    ASSERT_EQ(solver.solve(x0, qp, solution), hpipm::HpipmStatus::Success);

    // Compare solution x and u trajectories againt OSQP 
    auto concatenated = concatenateSolution(solution);

    const std::string datafile = "../../test/sol" + std::to_string(t) + ".txt";
    auto loaded = loadDataFromFile(datafile);
    EXPECT_TRUE(concatenated.isApprox(Eigen::Map<Eigen::VectorXd>(loaded.data(), loaded.size()), 1.0e-09));

    u0 = solution[0].u;
    x = A * x + B * u0 + b;
  }
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}