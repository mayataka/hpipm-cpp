#include "hpipm-cpp/ocp_qp_dim.hpp"

#include <stdexcept>
#include <string>


namespace hpipm {

OcpQpDim::OcpQpDim(const unsigned int N) {
  resize(N);
}


void OcpQpDim::resize(const unsigned int _N) {
  N = _N; 
  nx.resize(N+1);
  nu.resize(N);
  nbx.resize(N+1);
  nbu.resize(N);
  ng.resize(N+1);
  nsbx.resize(N+1);
  nsbu.resize(N);
  nsg.resize(N+1);
  ocp_qp_dim_wrapper_.resize(N);
}


d_ocp_qp_dim_wrapper& OcpQpDim::getHpipmWrapper() { 
  if (N <= 0) {
    throw std::runtime_error("OcpQpDim.N must be positive: input value is " + std::to_string(N));
  }
  if (nx.size() != N+1) {
    throw std::runtime_error("OcpQpDim.nx.size() must be the same as N+1: input value is " + std::to_string(nx.size()));
  }
  if (nu.size() != N) {
    throw std::runtime_error("OcpQpDim.nu.size() must be the same as N: input value is " + std::to_string(nu.size()));
  }
  if (nbx.size() != N+1) {
    throw std::runtime_error("OcpQpDim.nbx.size() must be the same as N+1: input value is " + std::to_string(nbx.size()));
  }
  if (nbu.size() != N) {
    throw std::runtime_error("OcpQpDim.nbu.size() must be the same as N: input value is " + std::to_string(nbu.size()));
  }
  if (ng.size() != N+1) {
    throw std::runtime_error("OcpQpDim.ng.size() must be the same as N+1: input value is " + std::to_string(ng.size()));
  }
  if (nsbx.size() != N+1) {
    throw std::runtime_error("OcpQpDim.nsbx.size() must be the same as N+1: input value is " + std::to_string(nsbx.size()));
  }
  if (nsbu.size() != N) {
    throw std::runtime_error("OcpQpDim.nsbu.size() must be the same as N: input value is " + std::to_string(nsbu.size()));
  }
  if (nsg.size() != N+1) {
    throw std::runtime_error("OcpQpDim.nsg.size() must be the same as N+1: input value is " + std::to_string(nsg.size()));
  }
  for (unsigned int i=0; i<=N; ++i) {
    if (nx[i] <= 0) throw std::runtime_error("OcpQpDim.nx[" + std::to_string(i) + "] must be positive");
  }
  for (unsigned int i=0; i<N; ++i) {
    if (nu[i] < 0) throw std::runtime_error("OcpQpDim.nu[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<=N; ++i) {
    if (nbx[i] < 0) throw std::runtime_error("OcpQpDim.nbx[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<N; ++i) {
    if (nbu[i] < 0) throw std::runtime_error("OcpQpDim.nbu[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<=N; ++i) {
    if (ng[i] < 0) throw std::runtime_error("OcpQpDim.ng[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<=N; ++i) {
    if (nsbx[i] < 0) throw std::runtime_error("OcpQpDim.nsbx[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<N; ++i) {
    if (nsbu[i] < 0) throw std::runtime_error("OcpQpDim.nsbu[" + std::to_string(i) + "] must be non-negative");
  }
  for (unsigned int i=0; i<=N; ++i) {
    if (nsg[i] < 0) throw std::runtime_error("OcpQpDim.nsg[" + std::to_string(i) + "] must be non-negative");
  }
  ocp_qp_dim_wrapper_.resize(N);
  d_ocp_qp_dim_set_all(nx.data(), nu.data(), nbx.data(), nbu.data(), ng.data(), 
                       nsbx.data(), nsbu.data(), nsg.data(), 
                       ocp_qp_dim_wrapper_.get());
  return ocp_qp_dim_wrapper_;
}

} // namespace hpipm
