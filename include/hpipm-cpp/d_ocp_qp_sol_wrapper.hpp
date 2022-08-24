#ifndef HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_sol.h"
}

#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_sol_wrapper {
public:
  d_ocp_qp_sol_wrapper(const d_ocp_qp_dim_wrapper& dim);

  d_ocp_qp_sol_wrapper();

  ~d_ocp_qp_sol_wrapper();

  d_ocp_qp_sol_wrapper(const d_ocp_qp_sol_wrapper&);

  d_ocp_qp_sol_wrapper& operator=(const d_ocp_qp_sol_wrapper&);

  d_ocp_qp_sol_wrapper(d_ocp_qp_sol_wrapper&&) noexcept = delete;

  d_ocp_qp_sol_wrapper& operator=(d_ocp_qp_sol_wrapper&&) noexcept = delete;

  d_ocp_qp_sol* get();

  const d_ocp_qp_sol* get() const;

  const d_ocp_qp_dim_wrapper& dim() const;

  void resize(const d_ocp_qp_dim_wrapper& dim);

private:
  d_ocp_qp_dim_wrapper dim_;
  d_ocp_qp_sol ocp_qp_sol_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_sol_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_