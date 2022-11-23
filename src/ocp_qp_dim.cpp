#include "hpipm-cpp/ocp_qp_dim.hpp"

#include <stdexcept>
#include <string>


namespace hpipm {

OcpQpDim::OcpQpDim(const unsigned int N) {
  resize(N);
}


OcpQpDim::OcpQpDim(const std::vector<OcpQp>& ocp_qp) {
  resize(ocp_qp);
}


void OcpQpDim::resize(const unsigned int _N) {
  N = _N; 
  nx.resize(N+1);
  nu.resize(N+1);
  nbx.resize(N+1);
  nbu.resize(N+1);
  ng.resize(N+1);
  nsbx.resize(N+1);
  nsbu.resize(N+1);
  nsg.resize(N+1);
}


void OcpQpDim::resize(const std::vector<OcpQp>& ocp_qp) {
  if (ocp_qp.empty()) {
    throw std::runtime_error("ocp_qp.size() must not be empty");
  }
  resize(ocp_qp.size()-1);
  for (unsigned int i=0; i<N; ++i) {
    nx[i]   = ocp_qp[i].q.size();
    nu[i]   = ocp_qp[i].r.size();
    nbx[i]  = ocp_qp[i].idxbx.size();
    nbu[i]  = ocp_qp[i].idxbu.size();
    ng[i]   = ocp_qp[i].lg.size();
    nsbx[i] = ocp_qp[i].idxs.size();
    nsbu[i] = 0;
    nsg[i]  = 0;
  }
  nx[N]   = ocp_qp[N].q.size();
  nu[N]   = 0;
  nbx[N]  = ocp_qp[N].idxbx.size();
  nbu[N]  = 0;
  ng[N]   = ocp_qp[N].lg.size();
  nsbx[N] = ocp_qp[N].idxs.size();
  nsbu[N] = 0;
  nsg[N]  = 0;
  checkSize(ocp_qp);
}


void OcpQpDim::checkSize(const std::vector<OcpQp>& ocp_qp) const {
  if (ocp_qp.size() != N+1) {
    throw std::runtime_error("ocp_qp.size() must be " + std::to_string(N+1));
  }
  // dynamics
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].A.rows() != nx[i+1]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].A.rows() must be " + std::to_string(nx[i+1]));
    }
    if (ocp_qp[i].A.cols() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].A.cols() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].B.rows() != nx[i+1]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].B.rows() must be " + std::to_string(nx[i+1]));
    }
    if (ocp_qp[i].B.cols() != nu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].B.cols() must be " + std::to_string(nu[i]));
    }
    if (ocp_qp[i].b.size() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].b.size() must be " + std::to_string(nx[i]));
    }
  }
  // cost
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].Q.rows() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Q.rows() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].Q.cols() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Q.cols() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].S.rows() != nu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].S.rows() must be " + std::to_string(nu[i]));
    }
    if (ocp_qp[i].S.cols() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].S.cols() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].R.rows() != nu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].R.rows() must be " + std::to_string(nu[i]));
    }
    if (ocp_qp[i].R.cols() != nu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].R.cols() must be " + std::to_string(nu[i]));
    }
    if (ocp_qp[i].q.size() != nx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].q.size() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].r.size() != nu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].r.size() must be " + std::to_string(nu[i]));
    }
  }
  if (ocp_qp[N].Q.rows() != nx[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].Q.rows() must be " + std::to_string(nx[N]));
  }
  if (ocp_qp[N].Q.cols() != nx[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].Q.cols() must be " + std::to_string(nx[N]));
  }
  if (ocp_qp[N].q.size() != nx[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].q.size() must be " + std::to_string(nx[N]));
  }
  // box constraints on x
  for (unsigned int i=0; i<=N; ++i) {
    if (ocp_qp[i].idxbx.size() != nbx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].idxbx.size() must be " + std::to_string(nbx[i]));
    }
    if (ocp_qp[i].lbx.size() != nbx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbx.size() must be " + std::to_string(nbx[i]));
    }
    if (ocp_qp[i].ubx.size() != nbx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubx.size() must be " + std::to_string(nbx[i]));
    }
    if (ocp_qp[i].lbx_mask.size() != 0 && ocp_qp[i].lbx_mask.size() != nbx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbx_mask.size() must be 0 or " + std::to_string(nbx[i]));
    }
    if (ocp_qp[i].ubx_mask.size() != 0 && ocp_qp[i].ubx_mask.size() != nbx[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubx_mask.size() must be 0 or " + std::to_string(nbx[i]));
    }
  }
  // box constraints on u
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].idxbu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].idxbx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].lbu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].ubu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].lbu_mask.size() != 0 && ocp_qp[i].lbu_mask.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbu_mask.size() must be 0 or " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].ubu_mask.size() != 0 && ocp_qp[i].ubu_mask.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubu_mask.size() must be 0 or " + std::to_string(nbu[i]));
    }
  }
  // box constraints on u
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].idxbu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].idxbx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].lbu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].ubu.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubx.size() must be " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].lbu_mask.size() != 0 && ocp_qp[i].lbu_mask.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lbu_mask.size() must be 0 or " + std::to_string(nbu[i]));
    }
    if (ocp_qp[i].ubu_mask.size() != 0 && ocp_qp[i].ubu_mask.size() != nbu[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ubu_mask.size() must be 0 or " + std::to_string(nbu[i]));
    }
  }
  // constraints 
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].C.rows() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].C.rows() must be " + std::to_string(ng[i]));
    }
    if (ocp_qp[i].C.cols() != nx[i] && ng[i] > 0) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].C.cols() must be " + std::to_string(nx[i]));
    }
    if (ocp_qp[i].D.rows() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].D.rows() must be " + std::to_string(ng[i]));
    }
    if (ocp_qp[i].D.cols() != nu[i] && ng[i] > 0) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].D.cols() must be " + std::to_string(nu[i]));
    }
    if (ocp_qp[i].lg.size() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lg.size() must be " + std::to_string(ng[i]));
    }
    if (ocp_qp[i].ug.size() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ug.size() must be " + std::to_string(ng[i]));
    }
    if (ocp_qp[i].lg_mask.size() != 0 && ocp_qp[i].lg_mask.size() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lg_mask.size() must be 0 or " + std::to_string(ng[i]));
    }
    if (ocp_qp[i].ug_mask.size() != 0 && ocp_qp[i].ug_mask.size() != ng[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].ug_mask.size() must be 0 or " + std::to_string(ng[i]));
    }
  }
  if (ocp_qp[N].C.rows() != ng[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].C.rows() must be " + std::to_string(ng[N]));
  }
  if (ocp_qp[N].C.cols() != nx[N] && ng[N] > 0) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].C.cols() must be " + std::to_string(nx[N]));
  }
  if (ocp_qp[N].lg.size() != ng[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].lg.size() must be " + std::to_string(ng[N]));
  }
  if (ocp_qp[N].ug.size() != ng[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].ug.size() must be " + std::to_string(ng[N]));
  }
  if (ocp_qp[N].lg_mask.size() != 0 && ocp_qp[N].lg_mask.size() != ng[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].lg_mask.size() must be 0 or " + std::to_string(ng[N]));
  }
  if (ocp_qp[N].ug_mask.size() != 0 && ocp_qp[N].ug_mask.size() != ng[N]) {
    throw std::runtime_error("ocp_qp[" + std::to_string(N) + "].ug_mask.size() must be 0 or " + std::to_string(ng[N]));
  }
  // soft constraints 
  for (unsigned int i=0; i<N; ++i) {
    if (ocp_qp[i].Zl.rows() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Zl.rows() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].Zl.cols() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Zl.cols() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].Zu.rows() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Zu.rows() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].Zu.cols() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].Zu.cols() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].zl.size() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].zl.size() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].zu.size() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].zl.size() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].idxs.size() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].idxs.size() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].lls.size() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lls.size() must be " + std::to_string(nsg[i]));
    }
    if (ocp_qp[i].lus.size() != nsg[i]) {
      throw std::runtime_error("ocp_qp[" + std::to_string(i) + "].lus.size() must be " + std::to_string(nsg[i]));
    }
  }
}

} // namespace hpipm
