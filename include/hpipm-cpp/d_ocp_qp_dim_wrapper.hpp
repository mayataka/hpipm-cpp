#ifndef HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_dim.h"
}


namespace hpipm {

class d_ocp_qp_dim_wrapper {
public:
  d_ocp_qp_dim_wrapper(const unsigned int N);

  d_ocp_qp_dim_wrapper();

  ~d_ocp_qp_dim_wrapper();

  d_ocp_qp_dim_wrapper(const d_ocp_qp_dim_wrapper&);

  d_ocp_qp_dim_wrapper& operator=(const d_ocp_qp_dim_wrapper&);

  d_ocp_qp_dim_wrapper(d_ocp_qp_dim_wrapper&&) noexcept = delete;

  d_ocp_qp_dim_wrapper& operator=(d_ocp_qp_dim_wrapper&&) noexcept = delete;

  d_ocp_qp_dim* get();

  const d_ocp_qp_dim* get() const;

  void resize(const unsigned int N);

private:
  d_ocp_qp_dim ocp_qp_dim_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_dim_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_