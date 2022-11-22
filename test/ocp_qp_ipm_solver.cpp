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

  for (int i=0; i<=N; ++i) {
    std::cout << "x:  " << solution[i].x.transpose() << std::endl;
    std::cout << "u:  " << solution[i].u.transpose() << std::endl;
    std::cout << "pi: " << solution[i].pi.transpose() << std::endl;
  }
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}