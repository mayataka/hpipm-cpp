#include "hpipm-cpp/ocp_qp_dim.hpp"

#include <algorithm>
#include <cstdlib>


namespace hpipm {

ocp_qp_dim::~ocp_qp_dim() {
  if (memory_) {
    free(memory_);
  }
}


bool ocp_qp_dim::checkSize() {
  if (N <= 0) {
    return false;
  }
}


void ocp_qp_dim::create_hpipm() {
  const hpipm_size_t new_memsize = d_ocp_qp_dim_memsize(N);
  if (memory_ && new_memsize >= memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize);
	  d_ocp_qp_dim_create(N, &ocp_qp_dim_hpipm_, memory_);
  }
	d_ocp_qp_dim_set_all(nx.data(), nu.data(), nbx.data(), nbu.data(), ng.data(), 
                       nsbx.data(), nsbu.data(), nsg.data(), &ocp_qp_dim_hpipm_);
}


ocp_qp_dim ocp_qp_dim::from_hpipm(const d_ocp_qp_dim* ocp_qp_dim_hpipm) {
  ocp_qp_dim ret;
  ret.N = ocp_qp_dim_hpipm->N;
  for (int i=0; i<=N; ++i) {
    ret.nx.push_back(ocp_qp_dim_hpipm->nx[i]);
    ret.nu.push_back(ocp_qp_dim_hpipm->nu[i]);
    ret.nbx.push_back(ocp_qp_dim_hpipm->nbx[i]);
    ret.nbu.push_back(ocp_qp_dim_hpipm->nbu[i]);
    ret.ng.push_back(ocp_qp_dim_hpipm->ng[i]);
    ret.nsbx.push_back(ocp_qp_dim_hpipm->nsbx[i]);
    ret.nsbu.push_back(ocp_qp_dim_hpipm->nsbu[i]);
    ret.nsg.push_back(ocp_qp_dim_hpipm->nsg[i]);
  }
  return ocp_qp_dim;
}

} // namespace hpipm
