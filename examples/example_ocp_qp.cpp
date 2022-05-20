#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/ocp_qp.hpp"
#include "hpipm-cpp/ocp_qp_ipm_arg.hpp"
#include "hpipm-cpp/ocp_qp_ipm.hpp"

#include "getting_started_data.hpp"

#include <vector>
#include "Eigen/Core"


int main() {
  QPSize qp_size;
  hpipm::ocp_qp_dim dim;
  dim.N    = qp_size.N;
  dim.nx   = qp_size.nx;
  dim.nu   = qp_size.nu;
  dim.nbx  = qp_size.nbx;
  dim.nbu  = qp_size.nbu;
  dim.ng   = qp_size.ng;
  dim.nsbx = qp_size.nsbx;
  dim.nsbu = qp_size.nsbu;
  dim.nsg  = qp_size.nsg;
  dim.create_hpipm();

  QPData qp_data;
  hpipm::ocp_qp qp;
  for (int i=0; i<dim.N; ++i) {
    qp.A.push_back(qp_data.A);
    qp.B.push_back(qp_data.B);
    qp.b.push_back(qp_data.b);
  }
  for (int i=0; i<=dim.N; ++i) {
    qp.Q.push_back(qp_data.q);
    qp.R.push_back(qp_data.R);
    qp.S.push_back(qp_data.S);
    qp.q.push_back(qp_data.q);
    qp.r.push_back(qp_data.r);
  }
  qp.idxbx.push_back(qp_data.idxbx0);

  return 0;
}