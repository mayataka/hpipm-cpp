#include "hpipm-cpp/ocp_qp_dim.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

ocp_qp_dim::~ocp_qp_dim() {
  if (memory_) {
    free(memory_);
  }
}


std::vector<std::string> ocp_qp_dim::checkSize() const {
  std::vector<std::string> err_mgs;
  if (N <= 0) {
    err_mgs.push_back("ocp_qp_dim.N must be positive!: input value is " + std::to_string(N));
  }
  if (nx.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nx.size() must be the same as N+1!: input value is " + std::to_string(nx.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nx[i] < 0) err_mgs.push_back("ocp_qp_dim.nx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nu.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nu.size() must be the same as N+1!: input value is " + std::to_string(nu.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nu[i] < 0) err_mgs.push_back("ocp_qp_dim.nu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nbx.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nbx.size() must be the same as N+1!: input value is " + std::to_string(nbx.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nbx[i] < 0) err_mgs.push_back("ocp_qp_dim.nbx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nbu.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nbu.size() must be the same as N+1!: input value is " + std::to_string(nbu.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nbu[i] < 0) err_mgs.push_back("ocp_qp_dim.nbu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (ng.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.ng.size() must be the same as N+1!: input value is " + std::to_string(ng.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (ng[i] < 0) err_mgs.push_back("ocp_qp_dim.ng[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsbx.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nsbx.size() must be the same as N+1!: input value is " + std::to_string(nsbx.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nsbx[i] < 0) err_mgs.push_back("ocp_qp_dim.nsbx[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsbu.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nsbu.size() must be the same as N+1!: input value is " + std::to_string(nsbu.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nsbu[i] < 0) err_mgs.push_back("ocp_qp_dim.nsbu[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  if (nsg.size() != N+1) {
    err_mgs.push_back("ocp_qp_dim.nsg.size() must be the same as N+1!: input value is " + std::to_string(nsg.size()));
  }
  else {
    for (int i=0; i<=N; ++i) {
      if (nsg[i] < 0) err_mgs.push_back("ocp_qp_dim.nsg[" + std::to_string(i) + "] must be non-negative!");
    }
  }
  return err_mgs;
}


void ocp_qp_dim::createHpipmData() {
  const hpipm_size_t new_memsize = d_ocp_qp_dim_memsize(N);
  if (memory_ && new_memsize >= memsize_) {
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


ocp_qp_dim ocp_qp_dim::from_hpipm(const d_ocp_qp_dim* ocp_qp_dim_hpipm) {
  ocp_qp_dim ret;
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
