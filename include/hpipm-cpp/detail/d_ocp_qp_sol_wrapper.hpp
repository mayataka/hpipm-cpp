#ifndef HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_

#include <memory>

extern "C" {
#include "hpipm_d_ocp_qp_sol.h"
}

#include "hpipm-cpp/detail/d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

///
/// @class d_ocp_qp_sol_wrapper
/// @brief A wrapper of d_ocp_qp_sol with a memory management.
///
class d_ocp_qp_sol_wrapper {
public:
  ///
  /// @brief Constructor. Allocates the hpipm resource.
  /// @param[in] dim Dimension.
  ///
  d_ocp_qp_sol_wrapper(const std::shared_ptr<d_ocp_qp_dim_wrapper>& dim);

  ///
  /// @brief Default constructor. Does not allocate the hpipm resource.
  ///
  d_ocp_qp_sol_wrapper();

  ///
  /// @brief Destructor.
  ///
  ~d_ocp_qp_sol_wrapper();

  ///
  /// @brief Custom copy constructor.
  ///
  d_ocp_qp_sol_wrapper(const d_ocp_qp_sol_wrapper&);

  ///
  /// @brief Custom copy assign operator.
  ///
  d_ocp_qp_sol_wrapper& operator=(const d_ocp_qp_sol_wrapper&);

  ///
  /// @brief Custom move constructor.
  ///
  d_ocp_qp_sol_wrapper(d_ocp_qp_sol_wrapper&&) noexcept;

  ///
  /// @brief Custom move assign operator.
  ///
  d_ocp_qp_sol_wrapper& operator=(d_ocp_qp_sol_wrapper&&) noexcept;

  ///
  /// @brief Gets the pointer to the hpipm resource. Throw an exception if the 
  /// memory for the instance is not allocated.
  /// @return Pointer to the hpipm resource.
  ///
  d_ocp_qp_sol* get();

  ///
  /// @brief Gets the const pointer to the hpipm instance.
  /// @return const pointer to the hpipm resource.
  ///
  const d_ocp_qp_sol* get() const;

  ///
  /// @brief Resizes the hpipm resource.
  /// @param[in] dim Dimension.
  ///
  void resize(const std::shared_ptr<d_ocp_qp_dim_wrapper>& dim);

private:
  std::shared_ptr<d_ocp_qp_dim_wrapper> dim_;
  d_ocp_qp_sol ocp_qp_sol_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_sol_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_SOL_WRAPPER_HPP_