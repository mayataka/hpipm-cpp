#include <vector>
#include "Eigen/Core"


struct QPSize {
  int N = 5; // horizon lenght
  std::vector<int> nu = {1, 1, 1, 1, 1};  // number of input
  std::vector<int> nx = {2, 2, 2, 2, 2, 2};  // number of states 
  std::vector<int> nbu = {0, 0, 0, 0, 0}; // number of box constraints on input
  std::vector<int> nbx = {2, 0, 0, 0, 0, 0}; // number of box constraints on states
  std::vector<int> ng = {0, 0, 0, 0, 0, 0};  // number of general constraints
  std::vector<int> nsbx = {0, 0, 0, 0, 0, 0}; // number of softed constraints on state box constraints
  std::vector<int> nsbu = {0, 0, 0, 0, 0}; // number of softed constraints on input box constraints
  std::vector<int> nsg = {0, 0, 0, 0, 0, 0};  // number of softed constraints on general constraints
  std::vector<int> nbue = {0, 0, 0, 0, 0}; // number of input box constraints considered as equality
  std::vector<int> nbxe = {0, 0, 0, 0, 0, 0}; // number of states box constraints considered as equality
  // std::vector<int> nge = {0, 0, 0, 0, 0, 0};  // number of general constraints considered as equality
};


struct QPData {
  Eigen::MatrixXd A = (Eigen::MatrixXd(2, 2) << 1.0, 1.0, 
                                                0.0, 1.0).finished();
  Eigen::MatrixXd B = (Eigen::MatrixXd(2, 1) << 0.0, 1.0).finished();
  Eigen::VectorXd b = (Eigen::VectorXd(2) << 0.0, 0.0).finished();

  Eigen::MatrixXd Q = (Eigen::MatrixXd(2, 2) << 1.0, 0.0, 
                                                0.0, 1.0).finished();
  Eigen::MatrixXd R = (Eigen::MatrixXd(1, 1) << 1.0).finished();
  Eigen::MatrixXd S = (Eigen::MatrixXd(1, 2) << 0.0, 0.0).finished();
  Eigen::VectorXd q = (Eigen::VectorXd(2) << 1.0, 1.0).finished();
  Eigen::VectorXd r = (Eigen::VectorXd(1) << 0.0).finished();

  Eigen::VectorXd x0 = (Eigen::VectorXd(2) << 1.0, 1.0).finished();

  Eigen::VectorXd lbx0 = x0;
  Eigen::VectorXd ubx0 = x0;
  std::vector<int> idxbx0 = {0, 1};

  Eigen::VectorXd lbx;
  Eigen::VectorXd ubx;
  std::vector<int> idxbx = {};

  Eigen::VectorXd u_guess = (Eigen::VectorXd(1) << 1.0).finished();
  Eigen::VectorXd x_guess = (Eigen::VectorXd(2) << 0.0, 0.0).finished();
};


struct IPMArg {
  int mode = 1;
  int iter_max = 30;
  double alpha_min = 1e-8;
  double mu0 = 1e4;
  double tol_stat = 1e-4;
  double tol_eq = 1e-5;
  double tol_ineq = 1e-5;
  double tol_comp = 1e-5;
  double reg_prim = 1e-12;
  int warm_start = 0;
  int pred_corr = 1;
  int ric_alg = 0;
  int split_step = 1;
};