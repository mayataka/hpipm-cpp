#ifndef HPIPM_CPP_OCP_QP_DIM_HPP_
#define HPIPM_CPP_OCP_QP_DIM_HPP_

#include <vector>

extern "C" {
#include "hpipm_d_ocp_qp_dim.h"
}

#include "d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

// Dimensions of OCP-QP.
class OcpQpDim {
public:
  OcpQpDim(const unsigned int N);

  OcpQpDim() = default;

  ~OcpQpDim() = default;

  OcpQpDim(const OcpQpDim&) = default;

  OcpQpDim& operator=(const OcpQpDim&) = default;

  OcpQpDim(OcpQpDim&&) noexcept = delete;

  OcpQpDim& operator=(OcpQpDim&&) noexcept = delete;

  void resize(const unsigned int N);

  d_ocp_qp_dim_wrapper& getHpipmWrapper();

  unsigned int N; // horizon length
  std::vector<int> nx;   // dimension of x
  std::vector<int> nu;   // dimension of u
  std::vector<int> nbx;  // number of box inequality constraints on x
  std::vector<int> nbu;  // number of box inequality constraints on u
  std::vector<int> ng;   // number of inequality constraints
  std::vector<int> nsbx; // number of soft box inequality constraints on x in nbx
  std::vector<int> nsbu; // number of soft box inequality constraints on u in nbu
  std::vector<int> nsg;  // number of soft inequality constraints in ng

private:
  d_ocp_qp_dim_wrapper ocp_qp_dim_wrapper_;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_DIM_HPP_