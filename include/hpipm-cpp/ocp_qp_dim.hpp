#ifndef HPIPM_CPP_OCP_QP_DIM_HPP_
#define HPIPM_CPP_OCP_QP_DIM_HPP_

#include <vector>
#include <string>
#include <optional>

extern "C" {
#include "hpipm_d_ocp_qp_dim.h"
}


namespace hpipm {

struct ocp_qp_dim {
public:
  ocp_qp_dim() = default;

  ~ocp_qp_dim();

  std::optional<std::string> checkSize() const;

  void create_hpipm();

  d_ocp_qp_dim* to_hpipm() { return &ocp_qp_dim_hpipm_; }

  const d_ocp_qp_dim* to_hpipm() const { return &ocp_qp_dim_hpipm_; }

  static ocp_qp_dim_wrapper from_hpipm(const d_ocp_qp_dim* ocp_qp_dim_hpipm);

  int N; // horizon length
  std::vector<int> nx;   // dimension of x
  std::vector<int> nu;   // dimension of u
  std::vector<int> nbx;  // number of box inequality constraints on x
  std::vector<int> nbu;  // number of box inequality constraints on u
  std::vector<int> ng;   // number of inequality constraints
  std::vector<int> nsbx; // number of soft box inequality constraints on x in nbx_
  std::vector<int> nsbu; // number of soft box inequality constraints on u in nbu_
  std::vector<int> nsg;  // number of soft inequality constraints in ng_ 

private:
  d_ocp_qp_dim ocp_qp_dim_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_DIM_HPP_