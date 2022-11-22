#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/hpipm-cpp.hpp"


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
    qp[i].q = Eigen::VectorXd::Random(nx);
    qp[i].r = Eigen::VectorXd::Random(nu);
  }
  const Eigen::MatrixXd H = Eigen::MatrixXd::Random(nx, nx);
  qp[N].Q = H * H.transpose();
  qp[N].q = Eigen::VectorXd::Random(nx);

  const Eigen::VectorXd x0 = Eigen::VectorXd::Random(nx);

  hpipm::OcpQpIpmSolverSettings solver_settings;

  std::vector<hpipm::OcpQpSolution> solution(N+1);
  hpipm::OcpQpIpmSolver solver(qp, solver_settings);
  const auto status = solver.solve(x0, qp, solution);
  EXPECT_EQ(status, hpipm::HpipmStatus::Success);
  EXPECT_EQ(solver.getSolverStatistics().iter, 0);
  std::cout << solver.getSolverStatistics() << std::endl;
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
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}