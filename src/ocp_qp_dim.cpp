#include "hpipm-cpp/ocp_qp_dim.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

OcpQpDim::OcpQpDim(const int N) {
  resize(N);
}


OcpQpDim::~OcpQpDim() {
  if (memory_) {
    free(memory_);
  }
}


std::vector<std::string> OcpQpDim::checkSize() const {
  std::vector<std::string> err_mgs;
  if (N <= 0) {
    err_mgs.push_back("OcpQpDim.N must be positive!: input value is " + std::to_string(N));
  }
  if (nx.size() != N+1) {
    err_mgs.push_back("OcpQpDim.nx.size() must be the same as N+1!: input value is " + std::to_string(nx.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nx[i] < 0) err_mgs.push_back("OcpQpDim.nx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nu.size() != N) {
    err_mgs.push_back("OcpQpDim.nu.size() must be the same as N!: input value is " + std::to_string(nu.size()));
  }
  else {
    for (int i=0; i<N; ++i) {
      if (nu[i] < 0) err_mgs.push_back("OcpQpDim.nu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nbx.size() != N+1) {
    err_mgs.push_back("OcpQpDim.nbx.size() must be the same as N+1!: input value is " + std::to_string(nbx.size()));
  }
  else {
    if (nbx[0] != nx[0]) err_mgs.push_back("OcpQpDim.nbx[0] must be the same as nx[0]!");
    for (int i=1; i<=N; ++i) {
      if (nbx[i] < 0) err_mgs.push_back("OcpQpDim.nbx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nbu.size() != N) {
    err_mgs.push_back("OcpQpDim.nbu.size() must be the same as N!: input value is " + std::to_string(nbu.size()));
  }
  else {
    for (int i=0; i<N; ++i) {
      if (nbu[i] < 0) err_mgs.push_back("OcpQpDim.nbu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (ng.size() != N+1) {
    err_mgs.push_back("OcpQpDim.ng.size() must be the same as N+1!: input value is " + std::to_string(ng.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (ng[i] < 0) err_mgs.push_back("OcpQpDim.ng[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsbx.size() != N+1) {
    err_mgs.push_back("OcpQpDim.nsbx.size() must be the same as N+1!: input value is " + std::to_string(nsbx.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nsbx[i] < 0) err_mgs.push_back("OcpQpDim.nsbx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsbu.size() != N) {
    err_mgs.push_back("OcpQpDim.nsbu.size() must be the same as N!: input value is " + std::to_string(nsbu.size()));
  }
  else {
    for (int i=0; i<N; ++i) {
      if (nsbu[i] < 0) err_mgs.push_back("OcpQpDim.nsbu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsg.size() != N+1) {
    err_mgs.push_back("OcpQpDim.nsg.size() must be the same as N+1!: input value is " + std::to_string(nsg.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nsg[i] < 0) err_mgs.push_back("OcpQpDim.nsg[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  return err_mgs;
}


void OcpQpDim::resize(const int _N) {
  N = _N; 
  nx.resize(N+1);
  nu.resize(N);
  nbx.resize(N+1);
  nbu.resize(N);
  ng.resize(N+1);
  nsbx.resize(N+1);
  nsbu.resize(N);
  nsg.resize(N+1);
  std::fill(nx.begin(), nx.end(), 0);
  std::fill(nu.begin(), nu.end(), 0);
  std::fill(nbx.begin(), nbx.end(), 0);
  std::fill(nbu.begin(), nbu.end(), 0);
  std::fill(ng.begin(), ng.end(), 0);
  std::fill(nsbx.begin(), nsbx.end(), 0);
  std::fill(nsbu.begin(), nsbu.end(), 0);
  std::fill(nsg.begin(), nsg.end(), 0);
}


void OcpQpDim::createHpipmData() {
  const hpipm_size_t new_memsize = d_ocp_qp_dim_memsize(N);
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
	  d_ocp_qp_dim_create(N, &ocp_qp_dim_hpipm_, memory_);
  }
	d_ocp_qp_dim_set_all(nx.data(), nu.data(), nbx.data(), nbu.data(), ng.data(), 
                       nsbx.data(), nsbu.data(), nsg.data(), &ocp_qp_dim_hpipm_);
}


OcpQpDim OcpQpDim::from_hpipm(const d_ocp_qp_dim* ocp_qp_dim_hpipm) {
  OcpQpDim ret;
  ret.N = ocp_qp_dim_hpipm->N;
  for (int i=0; i<=ret.N; ++i) {
    ret.nx.push_back(ocp_qp_dim_hpipm->nx[i]);
    ret.nu.push_back(ocp_qp_dim_hpipm->nu[i]);
    ret.nbx.push_back(ocp_qp_dim_hpipm->nbx[i]);
    ret.nbu.push_back(ocp_qp_dim_hpipm->nbu[i]);
    ret.ng.push_back(ocp_qp_dim_hpipm->ng[i]);
    ret.nsbx.push_back(ocp_qp_dim_hpipm->nsbx[i]);
    ret.nsbu.push_back(ocp_qp_dim_hpipm->nsbu[i]);
    ret.nsg.push_back(ocp_qp_dim_hpipm->nsg[i]);
  }
  return ret;
}

} // namespace hpipm
