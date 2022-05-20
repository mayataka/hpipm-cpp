#ifndef HPIPM_CPP_OCP_QP_IPM_HPP_
#define HPIPM_CPP_OCP_QP_IPM_HPP_

#include <vector>
#include <string>
#include <iostream>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/ocp_qp_sol.hpp"
#include "hpipm-cpp/ocp_qp.hpp"
#include "hpipm-cpp/ocp_qp_ipm_arg.hpp"
#include "hpipm-cpp/ocp_qp_ipm_stat.hpp"


namespace hpipm {

enum class HpipmStatus {
  Success = 0,
  MaxIterReached = 1,
  MinStepLengthReached = 2,
  NaNDetected = 3,
  UnknownFailure = 4,
};

std::string to_string(const HpipmStatus& hpipm_status);

std::ostream& operator<<(std::ostream& os, const HpipmStatus& hpipm_status);

class ocp_qp_ipm {
public:
  ocp_qp_ipm() = default;

  ~ocp_qp_ipm();

  void createHpipmData(ocp_qp_dim& dim, ocp_qp_ipm_arg& ipm_arg);

  HpipmStatus solve(ocp_qp& qp, ocp_qp_sol& qp_sol, ocp_qp_ipm_arg& ipm_arg);

  ocp_qp_ipm_stat getStat();

private:
  struct d_ocp_qp_ipm_ws ocp_qp_ipm_ws_hpipm_;
  void *memory_ = nullptr;
  double *stat_;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_IPM_HPP_