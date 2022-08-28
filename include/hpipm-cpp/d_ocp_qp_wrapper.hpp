#ifndef HPIPM_CPP_D_OCP_QP_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_WRAPPER_HPP_

extern "C" {
#include "hpipm_d_ocp_qp.h"
}

#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

///
/// @class d_ocp_qp_wrapper
/// @brief A wrapper of d_ocp_qp with a memory management.
///
class d_ocp_qp_wrapper {
public:
  ///
  /// @brief Constructor. Allocates the hpipm resource.
  /// @param[in] dim Dimension.
  ///
  d_ocp_qp_wrapper(const d_ocp_qp_dim_wrapper& dim);

  ///
  /// @brief Default constructor. Does not allocate the hpipm resource.
  ///
  d_ocp_qp_wrapper();

  ///
  /// @brief Destructor.
  ///
  ~d_ocp_qp_wrapper();

  ///
  /// @brief Custom copy constructor.
  ///
  d_ocp_qp_wrapper(const d_ocp_qp_wrapper&);

  ///
  /// @brief Custom copy assign operator.
  ///
  d_ocp_qp_wrapper& operator=(const d_ocp_qp_wrapper&);

  ///
  /// @brief Custom move constructor.
  ///
  d_ocp_qp_wrapper(d_ocp_qp_wrapper&&) noexcept;

  ///
  /// @brief Custom move assign operator.
  ///
  d_ocp_qp_wrapper& operator=(d_ocp_qp_wrapper&&) noexcept;

  ///
  /// @brief Gets the pointer to the hpipm resource. Throw an exception if the 
  /// memory for the instance is not allocated.
  /// @return Pointer to the hpipm resource.
  ///
  d_ocp_qp* get();

  ///
  /// @brief Gets the const pointer to the hpipm instance.
  /// @return const pointer to the hpipm resource.
  ///
  const d_ocp_qp* get() const;

  ///
  /// @brief Gets the dimension.
  /// @return const reference to the dimension.
  ///
  const d_ocp_qp_dim_wrapper& dim() const;

  ///
  /// @brief Resizes the hpipm resource.
  /// @param[in] dim Dimension.
  ///
  void resize(const d_ocp_qp_dim_wrapper& dim);

private:
  d_ocp_qp_dim_wrapper dim_;
  d_ocp_qp ocp_qp_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_WRAPPER_HPP_