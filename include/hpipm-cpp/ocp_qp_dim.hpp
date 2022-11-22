#ifndef HPIPM_CPP_OCP_QP_DIM_HPP_
#define HPIPM_CPP_OCP_QP_DIM_HPP_

#include <vector>

#include "ocp_qp.hpp"


namespace hpipm {

///
/// @class OcpQpDim
/// @brief Dimension of an OCP-QP problem.
///
struct OcpQpDim {
public:
  ///
  /// @brief Constructor. 
  /// @param[in] N Horizon length.
  ///
  OcpQpDim(const unsigned int N);

  ///
  /// @brief Constructor. 
  /// @param[in] ocp_qp OCP-QP data.
  ///
  OcpQpDim(const std::vector<OcpQp>& ocp_qp);

  ///
  /// @brief Default constructor. 
  ///
  OcpQpDim() = default;

  ///
  /// @brief Destructor.
  ///
  ~OcpQpDim() = default;

  ///
  /// @brief Default copy constructor.
  ///
  OcpQpDim(const OcpQpDim&) = default;

  ///
  /// @brief Default copy assign operator.
  ///
  OcpQpDim& operator=(const OcpQpDim&) = default;

  ///
  /// @brief Default move constructor.
  ///
  OcpQpDim(OcpQpDim&&) noexcept = default;

  ///
  /// @brief Default move assign operator.
  ///
  OcpQpDim& operator=(OcpQpDim&&) noexcept = default;

  ///
  /// @brief Horizon length.
  ///
  unsigned int N; 

  ///
  /// @brief Dimensions of x over the horizon. Size must be N+1. Each element must be positive.
  ///
  std::vector<int> nx;

  ///
  /// @brief Dimensions of u over the horizon. Size must be N. Each element must be non-negative.
  ///
  std::vector<int> nu;

  ///
  /// @brief Numbers of box inequality constraints on x over the horizon. Size must be N+1. Each element must be non-negative.
  ///
  std::vector<int> nbx;

  ///
  /// @brief Numbers of box inequality constraints on u over the horizon. Size must be N. Each element must be non-negative.
  ///
  std::vector<int> nbu;

  ///
  /// @brief Dimensions of inequality constraints over the horizon. Size must be N+1. Each element must be non-negative.
  ///
  std::vector<int> ng;

  ///
  /// @brief Numbers of soft box inequality constraints on x over the horizon. Size must be N+1. Each element must be non-negative.
  ///
  std::vector<int> nsbx;

  ///
  /// @brief Numbers of soft box inequality constraints on u over the horizon. Size must be N. Each element must be non-negative.
  ///
  std::vector<int> nsbu;

  ///
  /// @brief Dimensions of soft inequality constraints over the horizon. Size must be N+1. Each element must be non-negative.
  ///
  std::vector<int> nsg;

  ///
  /// @brief Resizes the dimension.
  /// @param[in] N horizon length.
  ///
  void resize(const unsigned int N);

  ///
  /// @brief Resizes the dimension.
  /// @param[in] ocp_qp OCP-QP data.
  ///
  void resize(const std::vector<OcpQp>& ocp_qp);

  ///
  /// @brief Check the sizes of OCP-QP data. If something is wrong, throws an exception.
  /// @param[in] ocp_qp OCP-QP data.
  ///
  void checkSize(const std::vector<OcpQp>& ocp_qp) const;
};

} // namespace hpipm

#endif // HPIPM_CPP_OCP_QP_DIM_HPP_