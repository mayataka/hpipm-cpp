#include <gtest/gtest.h>
#include <random>

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

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}