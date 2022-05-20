#ifndef HPIPM_CPP_OCP_QP_SOL_HPP_
#define HPIPM_CPP_OCP_QP_SOL_HPP_

#include <vector>
#include <string>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_sol.h"
}

#include "hpipm-cpp/ocp_qp_dim.hpp"


namespace hpipm {

struct ocp_qp_sol {
public:
  ocp_qp_sol() = default;

  ~ocp_qp_sol();

  void create_hpipm(ocp_qp_dim& dim);

  d_ocp_qp_sol* to_hpipm() { return &ocp_qp_sol_hpipm_; }

  const d_ocp_qp_sol* to_hpipm() const { return &ocp_qp_sol_hpipm_; }

  void from_hpipm(const ocp_qp_dim& dim);

  std::vector<Eigen::VectorXd> x;
  std::vector<Eigen::VectorXd> u;

private:
  d_ocp_qp_sol ocp_qp_sol_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_SOL_HPP_