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
    err_mgs.push_back("N must be positive!: N is " + std::to_string(N));
  }
  if (nx.size() != N+1) {
    err_mgs.push_back("nx.size() must be the same as N+1!: nx.size() is " + std::to_string(nx.size()));
  }
  if (nu.size() != N+1) {
    err_mgs.push_back("nu.size() must be the same as N+1!: nu.size() is " + std::to_string(nu.size()));
  }
  if (nbx.size() != N+1) {
    err_mgs.push_back("nbx.size() must be the same as N+1!: nbx.size() is " + std::to_string(nbx.size()));
  }
  if (nbu.size() != N+1) {
    err_mgs.push_back("nbu.size() must be the same as N+1!: nbu.size() is " + std::to_string(nbu.size()));
  }
  if (ng.size() != N+1) {
    err_mgs.push_back("ng.size() must be the same as N+1!: ng.size() is " + std::to_string(ng.size()));
  }
  if (nsbx.size() != N+1) {
    err_mgs.push_back("nsbx.size() must be the same as N+1!: nsbx.size() is " + std::to_string(nsbx.size()));
  }
  if (nsbu.size() != N+1) {
    err_mgs.push_back("nsbu.size() must be the same as N+1!: nsbu.size() is " + std::to_string(nsbu.size()));
  }
  if (nsg.size() != N+1) {
    err_mgs.push_back("nsg.size() must be the same as N+1!: nsg.size() is " + std::to_string(nsg.size()));
  }
  return err_mgs;
}


void ocp_qp_dim::create_hpipm() {
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
