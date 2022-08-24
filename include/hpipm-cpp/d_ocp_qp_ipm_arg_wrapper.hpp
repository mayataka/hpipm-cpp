#ifndef HPIPM_CPP_D_OCP_QP_IPM_ARG_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_IPM_ARG_WRAPPER_HPP_

#include <vector>
#include <string>
#include <stdexcept>

#include "Eigen/Core"

extern "C" {
#include "hpipm_d_ocp_qp_ipm.h"
}

#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_ipm_arg_wrapper {
public:
  d_ocp_qp_ipm_arg_wrapper();

  ~d_ocp_qp_ipm_arg_wrapper();

  d_ocp_qp_ipm_arg_wrapper(const d_ocp_qp_ipm_arg_wrapper&);

  d_ocp_qp_ipm_arg_wrapper& operator=(const d_ocp_qp_ipm_arg_wrapper&);

  d_ocp_qp_ipm_arg_wrapper(d_ocp_qp_ipm_arg_wrapper&&) noexcept = delete;

  d_ocp_qp_ipm_arg_wrapper& operator=(d_ocp_qp_ipm_arg_wrapper&&) noexcept = delete;

  d_ocp_qp_ipm_arg* get();

  const d_ocp_qp_ipm_arg* get() const;

private:
  d_ocp_qp_ipm_arg ocp_qp_ipm_arg_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void resize();

  void copy(const d_ocp_qp_ipm_arg_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_IPM_ARG_WRAPPER_HPP_