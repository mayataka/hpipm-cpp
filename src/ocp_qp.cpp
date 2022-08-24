#include "hpipm-cpp/ocp_qp.hpp"

#include <stdexcept>
#include <string>


namespace hpipm {

OcpQp::OcpQp(const OcpQpDim& dim) {
  resize(dim);
}


// std::vector<std::string> OcpQp::checkSize(const OcpQpDim& dim) const {
//   std::vector<std::string> err_mgs = dim.checkSize();
//   if (!err_mgs.empty()) {
//     err_mgs.push_back("Call ocp_qp.checkSize() with correct ocp_qp_dim! Please check the above errors.");
//     return err_mgs;
//   }
//   // initial state
//   if (x0.size() != dim.nx[0]) err_mgs.push_back("ocp_qp.x0.size() must be ocp_qp_dim.nx[0]!");
//   // dynamics
//   if (A.size() != dim.N) err_mgs.push_back("ocp_qp.A.size() must be ocp_qp_dim.N!");
//   if (B.size() != dim.N) err_mgs.push_back("ocp_qp.B.size() must be ocp_qp_dim.N!");
//   if (b.size() != dim.N) err_mgs.push_back("ocp_qp.b.size() must be ocp_qp_dim.N!");
//   for (int i=0; i<dim.N; ++i) {
//     if (A[i].rows() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.A[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (A[i].cols() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.A[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (B[i].rows() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.A[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (B[i].cols() != dim.nu[i]) 
//       err_mgs.push_back("ocp_qp.B[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     if (b[i].size() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.b[" + std::to_string(i) + "].size() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (b[i].cols() != 1) 
//       err_mgs.push_back("ocp_qp.b[" + std::to_string(i) + "] must be a vector!");
//   }
//   // costs 
//   if (Q.size() != dim.N+1) err_mgs.push_back("ocp_qp.Q.size() must be ocp_qp_dim.N+1!");
//   if (S.size() != dim.N) err_mgs.push_back("ocp_qp.S.size() must be ocp_qp_dim.N!");
//   if (R.size() != dim.N) err_mgs.push_back("ocp_qp.R.size() must be ocp_qp_dim.N!");
//   if (q.size() != dim.N+1) err_mgs.push_back("ocp_qp.q.size() must be ocp_qp_dim.N+1!");
//   if (r.size() != dim.N) err_mgs.push_back("ocp_qp.r.size() must be ocp_qp_dim.N!");
//   for (int i=0; i<dim.N; ++i) {
//     if (Q[i].rows() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.Q[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (Q[i].cols() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.Q[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (S[i].rows() != dim.nu[i]) 
//       err_mgs.push_back("ocp_qp.S[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     if (S[i].cols() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.S[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (R[i].rows() != dim.nu[i]) 
//       err_mgs.push_back("ocp_qp.R[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     if (R[i].cols() != dim.nu[i]) 
//       err_mgs.push_back("ocp_qp.R[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     if (q[i].size() != dim.nx[i]) 
//       err_mgs.push_back("ocp_qp.q[" + std::to_string(i) + "].size() must be ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//     if (q[i].cols() != 1) 
//       err_mgs.push_back("ocp_qp.q[" + std::to_string(i) + "] must be a vector!");
//     if (r[i].size() != dim.nu[i]) 
//       err_mgs.push_back("ocp_qp.r[" + std::to_string(i) + "].size() must be ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//     if (r[i].cols() != 1) 
//       err_mgs.push_back("ocp_qp.r[" + std::to_string(i) + "] must be a vector!");
//   }
//   if (Q[dim.N].rows() != dim.nx[dim.N]) 
//     err_mgs.push_back("ocp_qp.Q[" + std::to_string(dim.N) + "].rows() must be ocp_qp_dim.nx[" + std::to_string(dim.N) + "]!");
//   if (Q[dim.N].cols() != dim.nx[dim.N]) 
//     err_mgs.push_back("ocp_qp.Q[" + std::to_string(dim.N) + "].cols() must be ocp_qp_dim.nx[" + std::to_string(dim.N) + "]!");
//   if (q[dim.N].size() != dim.nx[dim.N]) 
//     err_mgs.push_back("ocp_qp.q[" + std::to_string(dim.N) + "].size() must be ocp_qp_dim.nx[" + std::to_string(dim.N) + "]!");
//   if (q[dim.N].cols() != 1) 
//     err_mgs.push_back("ocp_qp.q[" + std::to_string(dim.N) + "] must be a vector!");
//   // box constraints
//   if (idxbx.empty()) {
//     if (!lbx.empty()) err_mgs.push_back("lbx must be empty because idxbx is empty!");
//     if (!ubx.empty()) err_mgs.push_back("ubx must be empty because idxbx is empty!");
//   }
//   else {
//     if (idxbx.size() != dim.N+1) err_mgs.push_back("ocp_qp.idxbx.size() must be ocp_qp_dim.N+1 or 0!");
//     if (lbx.size() != dim.N+1) err_mgs.push_back("ocp_qp.lbx.size() must be ocp_qp_dim.N+1 or 0!");
//     if (ubx.size() != dim.N+1) err_mgs.push_back("ocp_qp.ubx.size() must be ocp_qp_dim.N+1 or 0!");
//     for (int i=0; i<=dim.N; ++i) {
//       if (idxbx[i].size() != dim.nbx[i]) 
//         err_mgs.push_back("ocp_qp.idxbx[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbx[" + std::to_string(i) + "]!");
//       if (lbx[i].size() != dim.nbx[i]) 
//         err_mgs.push_back("ocp_qp.lbx[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbx[" + std::to_string(i) + "]!");
//       if (ubx[i].size() != dim.nbx[i]) 
//         err_mgs.push_back("ocp_qp.ubx[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbx[" + std::to_string(i) + "]!");
//     }
//   }
//   if (lbx_mask.size() != 0 && lbx_mask.size() != dim.N+1) err_mgs.push_back("ocp_qp.lbx_mask.size() must be ocp_qp_dim.N+1 or 0!");
//   if (ubx_mask.size() != 0 && ubx_mask.size() != dim.N+1) err_mgs.push_back("ocp_qp.ubx_mask.size() must be ocp_qp_dim.N+1 or 0!");
//   if (lbx_mask.size() == dim.N+1) {
//     for (int i=1; i<=dim.N; ++i) {
//       if (lbx_mask[i].size() != 0 && lbx_mask[i].size() != dim.nbx[i]) {
//         err_mgs.push_back("ocp_qp.lbx_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.nbx[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<lbx_mask[i].size(); ++j) {
//           if (lbx_mask[i][j] != 1.0 && lbx_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.lbx_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   if (ubx_mask.size() == dim.N+1) {
//     for (int i=1; i<=dim.N; ++i) {
//       if (ubx_mask[i].size() != 0 && ubx_mask[i].size() != dim.nbx[i]) {
//         err_mgs.push_back("ocp_qp.ubx_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.nbx[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<ubx_mask[i].size(); ++j) {
//           if (ubx_mask[i][j] != 1.0 && ubx_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.ubx_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   if (idxbu.empty()) {
//     if (!lbu.empty()) err_mgs.push_back("lbu must be empty because idxbu is empty!");
//     if (!ubu.empty()) err_mgs.push_back("ubu must be empty because idxbu is empty!");
//   }
//   else {
//     if (idxbu.size() != dim.N)  err_mgs.push_back("ocp_qp.idxbu.size() must be ocp_qp_dim.N or 0!");
//     if (lbu.size() != dim.N) err_mgs.push_back("ocp_qp.lbu.size() must be ocp_qp_dim.N or 0!");
//     if (ubu.size() != dim.N) err_mgs.push_back("ocp_qp.ubu.size() must be ocp_qp_dim.N or 0!");
//     for (int i=0; i<dim.N; ++i) {
//       if (idxbu[i].size() != dim.nbu[i]) 
//         err_mgs.push_back("ocp_qp.idxbu[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbu[" + std::to_string(i) + "]!");
//       if (lbu[i].size() != dim.nbu[i]) 
//         err_mgs.push_back("ocp_qp.lbx[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbu[" + std::to_string(i) + "]!");
//       if (ubu[i].size() != dim.nbu[i]) 
//         err_mgs.push_back("ocp_qp.ubx[" + std::to_string(i) + "].size() must be ocp_qp_dim.nbu[" + std::to_string(i) + "]!");
//     }
//   }
//   if (lbu_mask.size() != 0 && lbu_mask.size() != dim.N) err_mgs.push_back("ocp_qp.lbu_mask.size() must be ocp_qp_dim.N or 0!");
//   if (ubu_mask.size() != 0 && ubu_mask.size() != dim.N) err_mgs.push_back("ocp_qp.ubu_mask.size() must be ocp_qp_dim.N or 0!");
//   if (lbu_mask.size() == dim.N) {
//     for (int i=0; i<dim.N; ++i) {
//       if (lbu_mask[i].size() != 0 && lbu_mask[i].size() != dim.nbu[i]) {
//         err_mgs.push_back("ocp_qp.lbu_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.nbu[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<lbu_mask[i].size(); ++j) {
//           if (lbu_mask[i][j] != 1.0 && lbu_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.lbu_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   if (ubu_mask.size() == dim.N) {
//     for (int i=0; i<dim.N; ++i) {
//       if (ubu_mask[i].size() != 0 && ubu_mask[i].size() != dim.nbu[i]) {
//         err_mgs.push_back("ocp_qp.ubu_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.nbu[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<ubu_mask[i].size(); ++j) {
//           if (ubu_mask[i][j] != 1.0 && ubu_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.lbu_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   // constraints
//   if (C.empty()) {
//     if (!D.empty()) err_mgs.push_back("D must be empty because C is empty!");
//     if (!lg.empty()) err_mgs.push_back("lg must be empty because C is empty!");
//     if (!ug.empty()) err_mgs.push_back("ug must be empty because C is empty!");
//   }
//   else {
//     if (C.size() != dim.N+1) err_mgs.push_back("ocp_qp.C.size() must be ocp_qp_dim.N+1 or 0!");
//     if (D.size() != dim.N) err_mgs.push_back("ocp_qp.D.size() must be ocp_qp_dim.N or 0!");
//     if (lg.size() != dim.N+1) err_mgs.push_back("ocp_qp.lg.size() must be ocp_qp_dim.N+1 or 0!");
//     if (ug.size() != dim.N+1) err_mgs.push_back("ocp_qp.ug.size() must be ocp_qp_dim.N+1 or 0!");
//     for (int i=0; i<dim.N; ++i) {
//       if (C[i].rows() != dim.ng[i]) 
//         err_mgs.push_back("ocp_qp.C[" + std::to_string(i) + "].rows() must ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       if (C[i].rows() > 0 && C[i].cols() != dim.nx[i]) 
//         err_mgs.push_back("ocp_qp.C[" + std::to_string(i) + "].cols() must ocp_qp_dim.nx[" + std::to_string(i) + "]!");
//       if (D[i].rows() != dim.ng[i]) 
//         err_mgs.push_back("ocp_qp.D[" + std::to_string(i) + "].rows() must ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       if (D[i].rows() > 0 && D[i].cols() != dim.nu[i]) 
//         err_mgs.push_back("ocp_qp.D[" + std::to_string(i) + "].cols() must ocp_qp_dim.nu[" + std::to_string(i) + "]!");
//       if (lg[i].size() != dim.ng[i]) 
//         err_mgs.push_back("ocp_qp.lg[" + std::to_string(i) + "].size() must ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       if (lg[i].size() > 0 && lg[i].cols() != 1) 
//         err_mgs.push_back("ocp_qp.lg[" + std::to_string(i) + "] must be a vector!");
//       if (ug[i].size() != dim.ng[i]) 
//         err_mgs.push_back("ocp_qp.ug[" + std::to_string(i) + "].size() must be ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       if (ug[i].size() > 0 && ug[i].cols() != 1) 
//         err_mgs.push_back("ocp_qp.ug[" + std::to_string(i) + "] must be a vector!");
//     }
//     if (C[dim.N].rows() != dim.ng[dim.N]) 
//       err_mgs.push_back("ocp_qp.C[" + std::to_string(dim.N) + "].rows() must be ocp_qp_dim.ng[" + std::to_string(dim.N) + "]!");
//     if (C[dim.N].cols() != dim.nx[dim.N]) 
//       err_mgs.push_back("ocp_qp.C[" + std::to_string(dim.N) + "].cols() must be ocp_qp_dim.nx[" + std::to_string(dim.N) + "]!");
//     if (lg[dim.N].size() != dim.ng[dim.N]) 
//       err_mgs.push_back("ocp_qp.lg[" + std::to_string(dim.N) + "].size() must be ocp_qp_dim.ng[" + std::to_string(dim.N) + "]!");
//     if (lg[dim.N].cols() != 1) 
//       err_mgs.push_back("ocp_qp.lg[" + std::to_string(dim.N) + "] must be a vector!");
//     if (ug[dim.N].size() != dim.ng[dim.N]) 
//       err_mgs.push_back("ocp_qp.ug[" + std::to_string(dim.N) + "].size() must be ocp_qp_dim.ng[" + std::to_string(dim.N) + "]!");
//     if (ug[dim.N].cols() != 1) 
//       err_mgs.push_back("ocp_qp.ug[" + std::to_string(dim.N) + "] must be a vector!");
//   }
//   if (lg_mask.size() != 0 && lg_mask.size() != dim.N+1) err_mgs.push_back("ocp_qp.lg_mask.size() must be ocp_qp_dim.N+1 or 0!");
//   if (ug_mask.size() != 0 && ug_mask.size() != dim.N+1) err_mgs.push_back("ocp_qp.ug_mask.size() must be ocp_qp_dim.N+1 or 0!");
//   if (lg_mask.size() == dim.N+1) {
//     for (int i=0; i<=dim.N; ++i) {
//       if (lg_mask[i].size() != 0 && lg_mask[i].size() != dim.ng[i]) {
//         err_mgs.push_back("ocp_qp.lg_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<lg_mask[i].size(); ++j) {
//           if (lg_mask[i][j] != 1.0 && lg_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.lg_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   if (ug_mask.size() == dim.N+1) {
//     for (int i=0; i<=dim.N; ++i) {
//       if (ug_mask[i].size() != 0 && ug_mask[i].size() != dim.ng[i]) {
//         err_mgs.push_back("ocp_qp.ug_mask[" + std::to_string(i) + "].size() must be 0 or ocp_qp_dim.ng[" + std::to_string(i) + "]!");
//       }
//       else {
//         for (int j=0; j<ug_mask[i].size(); ++j) {
//           if (ug_mask[i][j] != 1.0 && ug_mask[i][j] != 0.0) 
//             err_mgs.push_back("ocp_qp.ug_mask[" + std::to_string(i) + "][" + std::to_string(j) + "] must be 1.0 or 0.0!");
//         }
//       }
//     }
//   }
//   // soft constraints
//   if (Zl.empty()) {
//     if (!Zu.empty()) err_mgs.push_back("Zu must be empty because Zu is empty!");
//     if (!zl.empty()) err_mgs.push_back("lg must be empty because zl is empty!");
//     if (!zu.empty()) err_mgs.push_back("lg must be empty because zu is empty!");
//   }
//   else {
//     for (int i=0; i<=dim.N; ++i) {
//       if (Zu[i].rows() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.Zu[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (Zu[i].cols() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.Zu[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (Zl[i].rows() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.Zl[" + std::to_string(i) + "].rows() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (Zl[i].cols() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.Zl[" + std::to_string(i) + "].cols() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (zu[i].size() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.zu[" + std::to_string(i) + "].size() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (zu[i].cols() != 1) 
//         err_mgs.push_back("ocp_qp.zu[" + std::to_string(i) + "] must be a vector!");
//       if (zl[i].size() != dim.nsg[i]) 
//         err_mgs.push_back("ocp_qp.zl[" + std::to_string(i) + "].size() must be ocp_qp_dim.nsg[" + std::to_string(i) + "]!");
//       if (zl[i].cols() != 1) 
//         err_mgs.push_back("ocp_qp.zl[" + std::to_string(i) + "] must be a vector!");
//     }
//   }
//   if (idxs.empty()) {
//     if (!lls.empty()) err_mgs.push_back("lls must be empty because idxs is empty!");
//     if (!lus.empty()) err_mgs.push_back("lus must be empty because idxs is empty!");
//   }
//   else {
//     for (int i=0; i<=dim.N; ++i) {
//       if (idxs.size() != dim.N+1) err_mgs.push_back("ocp_qp.idxs.size() must be ocp_qp_dim.N+1 or 0!");
//       if (lls.size() != dim.N+1) err_mgs.push_back("ocp_qp.lls.size() must be ocp_qp_dim.N+1 or 0!");
//       if (lus.size() != dim.N+1) err_mgs.push_back("ocp_qp.lus.size() must be ocp_qp_dim.N+1 or 0!");
//       for (int i=0; i<=dim.N; ++i) {
//         if (idxs[i].size() != dim.nsbx[i]) 
//           err_mgs.push_back("ocp_qp.idxs[" + std::to_string(i) + "].size() must be ocp_qp_dim.nsbx[" + std::to_string(i) + "]!");
//         if (lls[i].size() != dim.nsbx[i]) 
//           err_mgs.push_back("ocp_qp.lls[" + std::to_string(i) + "].size() must be ocp_qp_dim.nsbx[" + std::to_string(i) + "]!");
//         if (lus[i].size() != dim.nsbx[i]) 
//           err_mgs.push_back("ocp_qp.lus[" + std::to_string(i) + "].size() must be ocp_qp_dim.nsbx[" + std::to_string(i) + "]!");
//       }
//     }
//   }
//   return err_mgs;
// }

void OcpQp::resize(const OcpQpDim& dim) {
  dim_ = dim;
  ocp_qp_wrapper_.resize(dim_.getHpipmWrapper());
  resize();
}


d_ocp_qp_wrapper& OcpQp::getHpipmWrapper() {
  A_ptr_.resize(dim_.N);
  B_ptr_.resize(dim_.N);
  b_ptr_.resize(dim_.N);
  Q_ptr_.resize(dim_.N+1);
  S_ptr_.resize(dim_.N+1);
  R_ptr_.resize(dim_.N+1);
  q_ptr_.resize(dim_.N+1);
  r_ptr_.resize(dim_.N+1);
  idxbx_ptr_.resize(dim_.N+1);
  lbx_ptr_.resize(dim_.N+1);
  ubx_ptr_.resize(dim_.N+1);
  lbx_mask_ptr_.resize(dim_.N+1);
  ubx_mask_ptr_.resize(dim_.N+1);
  idxbu_ptr_.resize(dim_.N+1);
  lbu_ptr_.resize(dim_.N+1);
  ubu_ptr_.resize(dim_.N+1);
  lbu_mask_ptr_.resize(dim_.N+1);
  ubu_mask_ptr_.resize(dim_.N+1);
  C_ptr_.resize(dim_.N+1);
  D_ptr_.resize(dim_.N+1);
  lg_ptr_.resize(dim_.N+1);
  ug_ptr_.resize(dim_.N+1);
  lg_mask_ptr_.resize(dim_.N+1);
  ug_mask_ptr_.resize(dim_.N+1);
  Zl_ptr_.resize(dim_.N+1);
  Zu_ptr_.resize(dim_.N+1);
  zl_ptr_.resize(dim_.N+1);
  zu_ptr_.resize(dim_.N+1);
  idxs_ptr_.resize(dim_.N+1);
  lls_ptr_.resize(dim_.N+1);
  lus_ptr_.resize(dim_.N+1);

  // dynamics
  for (int i=0; i<dim_.N; ++i) {
    A_ptr_[i] = A[i].data();
    B_ptr_[i] = B[i].data();
    b_ptr_[i] = b[i].data();
  }
  // costs
  for (int i=0; i<dim_.N; ++i) {
    Q_ptr_[i] = Q[i].data();
    S_ptr_[i] = S[i].data();
    R_ptr_[i] = R[i].data();
    q_ptr_[i] = q[i].data();
    r_ptr_[i] = r[i].data();
  }
  Q_ptr_[dim_.N] = Q[dim_.N].data();
  q_ptr_[dim_.N] = q[dim_.N].data();
  // box constraints on state
  if (idxbx.empty() || lbx.empty() || ubx.empty()) {
    idxbx.resize(dim_.N+1);
    lbx.resize(dim_.N+1);
    ubx.resize(dim_.N+1);
  }
  idxbx[0].resize(dim_.nx[0]);
  for (int i=0; i<dim_.nx[0]; ++i) {
    idxbx[0][i] = i;
  }
  lbx[0] = x0;
  ubx[0] = x0;
  for (int i=0; i<=dim_.N; ++i) {
    idxbx_ptr_[i] = idxbx[i].data();
    lbx_ptr_[i]   = lbx[i].data();
    ubx_ptr_[i]   = ubx[i].data();
  }
  // box constraints on control input
  if (idxbu.empty() || lbu.empty() || ubu.empty()) {
    idxbu.resize(dim_.N+1);
    lbu.resize(dim_.N+1);
    ubu.resize(dim_.N+1);
  }
  for (int i=0; i<dim_.N; ++i) {
    idxbu_ptr_[i] = idxbu[i].data();
    lbu_ptr_[i] = lbu[i].data();
    ubu_ptr_[i] = ubu[i].data();
  }
  // constraints
  if (C.empty() || D.empty() || lg.empty() || ug.empty()) {
    C.resize(dim_.N+1);
    D.resize(dim_.N+1);
    lg.resize(dim_.N+1);
    ug.resize(dim_.N+1);
  }
  for (int i=0; i<dim_.N; ++i) {
    C_ptr_[i]  = C[i].data();
    D_ptr_[i]  = D[i].data();
    lg_ptr_[i] = lg[i].data();
    ug_ptr_[i] = ug[i].data();
  }
  C_ptr_[dim_.N]  = C[dim_.N].data();
  lg_ptr_[dim_.N] = lg[dim_.N].data();
  ug_ptr_[dim_.N] = ug[dim_.N].data();
  // soft constraints
  if (Zl.empty() || Zu.empty() || zl.empty() || zu.empty()) {
    Zl.resize(dim_.N+1);
    Zu.resize(dim_.N+1);
    zl.resize(dim_.N+1);
    zu.resize(dim_.N+1);
  }
  for (int i=0; i<=dim_.N; ++i) {
    Zl_ptr_[i] = Zu[i].data();
    Zu_ptr_[i] = Zu[i].data();
    zl_ptr_[i] = zl[i].data();
    zu_ptr_[i] = zu[i].data();
  }
  // TODO: what is this??
  if (idxs.empty() || lls.empty() || lus.empty()) {
    idxs.resize(dim_.N+1);
    lls.resize(dim_.N+1);
    lus.resize(dim_.N+1);
  }
  for (int i=0; i<=dim_.N; ++i) {
    idxs_ptr_[i] = idxs[i].data();
    lls_ptr_[i]  = lls[i].data();
    lus_ptr_[i]  = lus[i].data();
  }

  d_ocp_qp* hpipm_ptr = ocp_qp_wrapper_.get();
  d_ocp_qp_set_all(A_ptr_.data(), B_ptr_.data(), b_ptr_.data(), 
                   Q_ptr_.data(), S_ptr_.data(), R_ptr_.data(), q_ptr_.data(), r_ptr_.data(), 
                   idxbx_ptr_.data(), lbx_ptr_.data(), ubx_ptr_.data(),
                   idxbu_ptr_.data(), lbu_ptr_.data(), ubu_ptr_.data(),
                   C_ptr_.data(), D_ptr_.data(), lg_ptr_.data(), ug_ptr_.data(), 
                   Zl_ptr_.data(), Zu_ptr_.data(), zl_ptr_.data(), zu_ptr_.data(), 
                   idxs_ptr_.data(), lls_ptr_.data(), lus_ptr_.data(), hpipm_ptr);

  // initial state embedding
  hidxe_.resize(x0.size());
  for (int i=0; i<x0.size(); ++i) {
    hidxe_[i] = i;
  }
  d_ocp_qp_set_lbx(0, x0.data(), hpipm_ptr);
  d_ocp_qp_set_ubx(0, x0.data(), hpipm_ptr);
  d_ocp_qp_set_idxe(0, hidxe_.data(), hpipm_ptr);
  // masks
  if (lbx_mask.size() == dim_.N+1) {
    for (int i=1; i<=dim_.N; ++i) {
      if (lbx_mask[i].size() == dim_.nbx[i]) {
        lbx_mask_ptr_[i] = lbx[i].data();
        d_ocp_qp_set_lbx_mask(i, lbx_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ubx_mask.size() == dim_.N+1) {
    for (int i=1; i<=dim_.N; ++i) {
      if (ubx_mask[i].size() == dim_.nbx[i]) {
        ubx_mask_ptr_[i] = ubx[i].data();
        d_ocp_qp_set_ubx_mask(i, ubx_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (lbu_mask.size() == dim_.N) {
    for (int i=0; i<dim_.N; ++i) {
      if (lbu_mask[i].size() == dim_.nbu[i]) {
        lbu_mask_ptr_[i] = lbu[i].data();
        d_ocp_qp_set_lbu_mask(i, lbu_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ubu_mask.size() == dim_.N) {
    for (int i=0; i<dim_.N; ++i) {
      if (ubu_mask[i].size() == dim_.nbu[i]) {
        ubu_mask_ptr_[i] = ubu[i].data();
        d_ocp_qp_set_ubu_mask(i, ubu_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (lg_mask.size() == dim_.N+1) {
    for (int i=0; i<=dim_.N; ++i) {
      if (lg_mask[i].size() == dim_.ng[i]) {
        lg_mask_ptr_[i] = lg[i].data();
        d_ocp_qp_set_lg_mask(i, lg_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  if (ug_mask.size() == dim_.N+1) {
    for (int i=0; i<=dim_.N; ++i) {
      if (ug_mask[i].size() == dim_.ng[i]) {
        ug_mask_ptr_[i] = ug[i].data();
        d_ocp_qp_set_ug_mask(i, ug_mask_ptr_[i], hpipm_ptr);
      }
    }
  }
  return ocp_qp_wrapper_;
}


void OcpQp::resize() {
  x0.resize(dim_.nx[0]); 
  // dynamics
  A.resize(dim_.N);
  B.resize(dim_.N);
  b.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    A[i].resize(dim_.nx[i], dim_.nx[i]);
    B[i].resize(dim_.nx[i], dim_.nu[i]);
    b[i].resize(dim_.nx[i]);
  }
  // cost
  Q.resize(dim_.N+1);
  S.resize(dim_.N);
  R.resize(dim_.N);
  q.resize(dim_.N+1);
  r.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    Q[i].resize(dim_.nx[i], dim_.nx[i]);
    S[i].resize(dim_.nu[i], dim_.nx[i]);
    R[i].resize(dim_.nu[i], dim_.nu[i]);
    q[i].resize(dim_.nx[i]);
    r[i].resize(dim_.nu[i]);
  }
  Q[dim_.N].resize(dim_.nx[dim_.N], dim_.nx[dim_.N]);
  q[dim_.N].resize(dim_.nx[dim_.N]);
  // constraints
  idxbx.resize(dim_.N+1);
  lbx.resize(dim_.N+1);
  ubx.resize(dim_.N+1);
  lbx_mask.resize(dim_.N+1);
  ubx_mask.resize(dim_.N+1);
  for (int i=0; i<dim_.N+1; ++i) {
    idxbx[i].resize(dim_.nbx[i]);
    lbx[i].resize(dim_.nbx[i]);
    ubx[i].resize(dim_.nbx[i]);
    lbx_mask[i].resize(0);
    ubx_mask[i].resize(0);
  }
  idxbu.resize(dim_.N);
  lbu.resize(dim_.N);
  ubu.resize(dim_.N);
  lbu_mask.resize(dim_.N);
  ubu_mask.resize(dim_.N);
  for (int i=0; i<dim_.N; ++i) {
    idxbu[i].resize(dim_.nbu[i]);
    lbu[i].resize(dim_.nbu[i]);
    ubu[i].resize(dim_.nbu[i]);
    lbu_mask[i].resize(0);
    ubu_mask[i].resize(0);
  }
  C.resize(dim_.N+1);
  D.resize(dim_.N);
  lg.resize(dim_.N+1);
  ug.resize(dim_.N+1);
  lg_mask.resize(dim_.N+1);
  ug_mask.resize(dim_.N+1);
  for (int i=0; i<dim_.N; ++i) {
    C[i].resize(dim_.ng[i], dim_.nx[i]);
    D[i].resize(dim_.ng[i], dim_.nx[i]);
    lg[i].resize(dim_.ng[i]);
    ug[i].resize(dim_.ng[i]);
    lg_mask[i].resize(0);
    ug_mask[i].resize(0);
  }
  C[dim_.N].resize(dim_.ng[dim_.N], dim_.nx[dim_.N]);
  lg[dim_.N].resize(dim_.ng[dim_.N]);
  ug[dim_.N].resize(dim_.ng[dim_.N]);
  lg_mask[dim_.N].resize(0);
  ug_mask[dim_.N].resize(0);
  // soft constraints
  Zl.resize(dim_.N+1);
  Zu.resize(dim_.N+1);
  zl.resize(dim_.N+1);
  zu.resize(dim_.N+1);
  for (int i=0; i<=dim_.N; ++i) {
    Zl[i].resize(dim_.nsg[i], dim_.nsg[i]);
    Zu[i].resize(dim_.nsg[i], dim_.nsg[i]);
    zl[i].resize(dim_.nsg[i]);
    zu[i].resize(dim_.nsg[i]);
  }
  idxs.resize(dim_.N+1);
  lls.resize(dim_.N+1);
  lus.resize(dim_.N+1);
  for (int i=0; i<=dim_.N; ++i) {
    idxs[i].resize(dim_.nsbx[i]);
    lls[i].resize(dim_.nsbx[i]);
    lus[i].resize(dim_.nsbx[i]);
  }
}

} // namespace hpipm
