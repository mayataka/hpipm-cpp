#ifndef HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_
#define HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_

extern "C" {
#include "hpipm_d_ocp_qp_dim.h"
}


namespace hpipm {

///
/// @class d_ocp_qp_dim_wrapper
/// @brief A wrapper of d_ocp_qp_dim with a memory management.
///
class d_ocp_qp_dim_wrapper {
public:
  ///
  /// @brief Constructor. Allocates the hpipm resource.
  /// @param[in] N length of the horizon.
  ///
  d_ocp_qp_dim_wrapper(const unsigned int N);

  ///
  /// @brief Default constructor. Does not allocate the hpipm resource.
  ///
  d_ocp_qp_dim_wrapper();

  ///
  /// @brief Destructor.
  ///
  ~d_ocp_qp_dim_wrapper();

  ///
  /// @brief Custom copy constructor.
  ///
  d_ocp_qp_dim_wrapper(const d_ocp_qp_dim_wrapper&);

  ///
  /// @brief Custom copy assign operator.
  ///
  d_ocp_qp_dim_wrapper& operator=(const d_ocp_qp_dim_wrapper&);

  ///
  /// @brief Prohibit move constructor.
  ///
  d_ocp_qp_dim_wrapper(d_ocp_qp_dim_wrapper&&) noexcept = delete;

  ///
  /// @brief Prohibit move assign operator.
  ///
  d_ocp_qp_dim_wrapper& operator=(d_ocp_qp_dim_wrapper&&) noexcept = delete;

  ///
  /// @brief Gets the pointer to the hpipm resource. Throw an exception if the 
  /// memory for the instance is not allocated.
  /// @return Pointer to the hpipm resource.
  ///
  d_ocp_qp_dim* get();

  ///
  /// @brief Gets the const pointer to the hpipm instance.
  /// @return const pointer to the hpipm resource.
  ///
  const d_ocp_qp_dim* get() const;

  ///
  /// @brief Resizes the hpipm resource.
  /// @param[in] N length of the horizon.
  ///
  void resize(const unsigned int N);

private:
  d_ocp_qp_dim ocp_qp_dim_hpipm_;
  void *memory_ = nullptr;
  hpipm_size_t memsize_ = 0;

  void copy(const d_ocp_qp_dim_wrapper& other);
};

} // namespace hpipm

#endif // HPIPM_CPP_D_OCP_QP_DIM_WRAPPER_HPP_