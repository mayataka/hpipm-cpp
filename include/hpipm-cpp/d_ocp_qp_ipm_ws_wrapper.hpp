#ifndef HPIPM_CPP_D_OCP_QP_IPM_WS_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_IPM_WS_WRAPPER_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"
#include "hpipm-cpp/d_ocp_qp_ipm_arg_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_ipm_ws_wrapper {
public:
  d_ocp_qp_ipm_ws_wrapper(const d_ocp_qp_dim_wrapper& dim, 
                          const d_ocp_qp_ipm_arg_wrapper& ipm_arg);

  d_ocp_qp_ipm_ws_wrapper();

  ~d_ocp_qp_ipm_ws_wrapper();

  d_ocp_qp_ipm_ws_wrapper(const d_ocp_qp_ipm_ws_wrapper&) = delete;

  d_ocp_qp_ipm_ws_wrapper& operator=(const d_ocp_qp_ipm_ws_wrapper&) = delete;

  d_ocp_qp_ipm_ws_wrapper(d_ocp_qp_ipm_ws_wrapper&&) noexcept = delete;

  d_ocp_qp_ipm_ws_wrapper& operator=(d_ocp_qp_ipm_ws_wrapper&&) noexcept = delete;

  d_ocp_qp_ipm_ws* get();

  const d_ocp_qp_ipm_ws* get() const;

  const d_ocp_qp_dim_wrapper& dim() const;

  void resize(const d_ocp_qp_dim_wrapper& dim,
              const d_ocp_qp_ipm_arg_wrapper& ipm_arg);

private:
  d_ocp_qp_dim_wrapper dim_;
  d_ocp_qp_ipm_arg_wrapper ipm_arg_;
  d_ocp_qp_ipm_ws ocp_qp_ipm_ws_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_ipm_ws_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_IPM_WS_WRAPPER_HPP_