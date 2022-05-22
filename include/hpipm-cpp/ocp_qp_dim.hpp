#ifndef HPIPM_CPP_OCP_QP_DIM_HPP_
#define HPIPM_CPP_OCP_QP_DIM_HPP_

#include <vector>
#include <string>

extern "C" {
#include "hpipm_d_ocp_qp_dim.h"
}


namespace hpipm {

// Dimensions of OCP-QP.
struct OcpQpDim {
public:
  OcpQpDim(const int N);

  OcpQpDim() = default;

  ~OcpQpDim();

  std::vector<std::string> checkSize() const;

  void resize(const int N);

  void createHpipmData();

  d_ocp_qp_dim* to_hpipm() { return &ocp_qp_dim_hpipm_; }

  const d_ocp_qp_dim* to_hpipm() const { return &ocp_qp_dim_hpipm_; }

  static OcpQpDim from_hpipm(const d_ocp_qp_dim* ocp_qp_dim_hpipm);

  int N; // horizon length
  std::vector<int> nx;   // dimension of x
  std::vector<int> nu;   // dimension of u
  std::vector<int> nbx;  // number of box inequality constraints on x
  std::vector<int> nbu;  // number of box inequality constraints on u
  std::vector<int> ng;   // number of inequality constraints
  std::vector<int> nsbx; // number of soft box inequality constraints on x in nbx
  std::vector<int> nsbu; // number of soft box inequality constraints on u in nbu
  std::vector<int> nsg;  // number of soft inequality constraints in ng

private:
  d_ocp_qp_dim ocp_qp_dim_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_DIM_HPP_