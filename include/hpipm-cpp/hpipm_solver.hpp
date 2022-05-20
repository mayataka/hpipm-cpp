#ifndef HPIPM_CPP_HPIPM_SOLVER_HPP_
#define HPIPM_CPP_HPIPM_SOLVER_HPP_

#include <vector>
#include <string>
#include <optional>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_imp.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/ocp_qp_sol.hpp"
#include "hpipm-cpp/ocp_qp.hpp"
#include "hpipm-cpp/ocp_qp_ipm_arg.hpp"
#include "hpipm-cpp/ocp_qp_ipm.hpp"


namespace hpipm {

class HpipmSolver {
public:
  HpipmSolver(ocp_qp_dim& dim);

  HpipmSolver() = default;

  ~HpipmSolver();

  void create_hpipm(ocp_qp_dim& dim, ocp_qp_ipm_arg& ipm_arg);

  HpipmStatus solve(ocp_qp& qp, ocp_qp_sol& qp_sol, ocp_qp_ipm_arg& ipm_arg);

private:
	struct d_ocp_qp_ipm_ws ocp_qp_ipm_ws_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_HPIPM_SOLVER_HPP_