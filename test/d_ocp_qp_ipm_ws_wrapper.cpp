#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/detail/d_ocp_qp_ipm_ws_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_ipm_ws_wrapper_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

bool hasNullptr(const d_ocp_qp_ipm_ws_wrapper& ws) {
  return ws.get()->core_workspace == nullptr
      || ws.get()->dim == nullptr
      || ws.get()->res_workspace == nullptr
      || ws.get()->sol_step == nullptr
      || ws.get()->sol_itref == nullptr
      || ws.get()->qp_step == nullptr
      || ws.get()->qp_itref == nullptr
      || ws.get()->res_itref == nullptr
      || ws.get()->res == nullptr
      || ws.get()->Gamma == nullptr
      || ws.get()->gamma == nullptr
      || ws.get()->tmp_nuxM == nullptr
      || ws.get()->tmp_nbgM == nullptr
      || ws.get()->tmp_nsM == nullptr
      || ws.get()->Pb == nullptr
      || ws.get()->Zs_inv == nullptr
      || ws.get()->tmp_m == nullptr
      || ws.get()->l == nullptr
      || ws.get()->L == nullptr
      || ws.get()->Ls == nullptr
      || ws.get()->P == nullptr
      || ws.get()->Lh == nullptr
      || ws.get()->AL == nullptr
      || ws.get()->lq0 == nullptr
      || ws.get()->tmp_nxM_nxM == nullptr
      || ws.get()->stat == nullptr
      || ws.get()->use_hess_fact == nullptr
      || ws.get()->lq_work0 == nullptr;
}

bool hasOnlyNullptr(const d_ocp_qp_ipm_ws_wrapper& ws) {
  return ws.get()->core_workspace == nullptr
      && ws.get()->dim == nullptr
      && ws.get()->res_workspace == nullptr
      && ws.get()->sol_step == nullptr
      && ws.get()->sol_itref == nullptr
      && ws.get()->qp_step == nullptr
      && ws.get()->qp_itref == nullptr
      && ws.get()->res_itref == nullptr
      && ws.get()->res == nullptr
      && ws.get()->Gamma == nullptr
      && ws.get()->gamma == nullptr
      && ws.get()->tmp_nuxM == nullptr
      && ws.get()->tmp_nbgM == nullptr
      && ws.get()->tmp_nsM == nullptr
      && ws.get()->Pb == nullptr
      && ws.get()->Zs_inv == nullptr
      && ws.get()->tmp_m == nullptr
      && ws.get()->l == nullptr
      && ws.get()->L == nullptr
      && ws.get()->Ls == nullptr
      && ws.get()->P == nullptr
      && ws.get()->Lh == nullptr
      && ws.get()->AL == nullptr
      && ws.get()->lq0 == nullptr
      && ws.get()->tmp_nxM_nxM == nullptr
      && ws.get()->stat == nullptr
      && ws.get()->use_hess_fact == nullptr
      && ws.get()->lq_work0 == nullptr;
}

bool hasSamePtr(const d_ocp_qp_ipm_ws_wrapper& ws1, 
                const d_ocp_qp_ipm_ws_wrapper& ws2) {
  return ws1.get() == ws2.get()
      // || ws1.get()->dim == ws2.get()->dim
      || ws1.get()->res_workspace == ws2.get()->res_workspace
      || ws1.get()->sol_step == ws2.get()->sol_step
      || ws1.get()->sol_itref == ws2.get()->sol_itref
      || ws1.get()->qp_step == ws2.get()->qp_step
      || ws1.get()->qp_itref == ws2.get()->qp_itref
      || ws1.get()->res_itref == ws2.get()->res_itref
      || ws1.get()->res == ws2.get()->res
      || ws1.get()->Gamma == ws2.get()->Gamma
      || ws1.get()->gamma == ws2.get()->gamma
      || ws1.get()->tmp_nuxM == ws2.get()->tmp_nuxM
      || ws1.get()->tmp_nbgM == ws2.get()->tmp_nbgM
      || ws1.get()->tmp_nsM == ws2.get()->tmp_nsM
      || ws1.get()->Pb == ws2.get()->Pb
      || ws1.get()->Zs_inv == ws2.get()->Zs_inv
      || ws1.get()->tmp_m == ws2.get()->tmp_m
      || ws1.get()->l == ws2.get()->l
      || ws1.get()->L == ws2.get()->L
      || ws1.get()->Ls == ws2.get()->Ls
      || ws1.get()->P == ws2.get()->P
      || ws1.get()->Lh == ws2.get()->Lh
      || ws1.get()->AL == ws2.get()->AL
      || ws1.get()->lq0 == ws2.get()->lq0
      || ws1.get()->tmp_nxM_nxM == ws2.get()->tmp_nxM_nxM
      || ws1.get()->stat == ws2.get()->stat
      || ws1.get()->use_hess_fact == ws2.get()->use_hess_fact
      || ws1.get()->lq_work0 == ws2.get()->lq_work0;
}


TEST_F(d_ocp_qp_ipm_ws_wrapper_test, move) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> distr(0, 10);

  const unsigned int N = 10 + distr(eng);
  auto dim = std::make_shared<d_ocp_qp_dim_wrapper>(N);
  for (unsigned int i=0; i<=N; ++i) {
    dim->get()->nx[i]   = distr(eng);
    dim->get()->nu[i]   = distr(eng);
    dim->get()->nb[i]   = distr(eng);
    dim->get()->nbx[i]  = distr(eng);
    dim->get()->nbu[i]  = distr(eng);
    dim->get()->ng[i]   = distr(eng);
    dim->get()->ns[i]   = distr(eng);
    dim->get()->nsbx[i] = distr(eng);
    dim->get()->nsbu[i] = distr(eng);
    dim->get()->nsg[i]  = distr(eng);
    dim->get()->nbxe[i] = distr(eng);
    dim->get()->nbue[i] = distr(eng);
    dim->get()->nge[i]  = distr(eng);
  }

  auto arg = std::make_shared<d_ocp_qp_ipm_arg_wrapper>();
  arg->get()->iter_max = distr(eng);
  arg->get()->stat_max = distr(eng);
  arg->get()->pred_corr = distr(eng);
  arg->get()->cond_pred_corr = distr(eng);
  arg->get()->itref_pred_max = distr(eng);
  arg->get()->itref_corr_max = distr(eng);
  arg->get()->warm_start = distr(eng);
  arg->get()->square_root_alg = distr(eng);
  arg->get()->lq_fact = distr(eng);
  arg->get()->abs_form = distr(eng);
  arg->get()->comp_dual_sol_eq = distr(eng);
  arg->get()->comp_res_exit = distr(eng);
  arg->get()->comp_res_pred = distr(eng);
  arg->get()->split_step = distr(eng);
  arg->get()->var_init_scheme = distr(eng);
  arg->get()->t_lam_min = distr(eng);

  d_ocp_qp_ipm_ws_wrapper ws(dim, arg);

  d_ocp_qp_ipm_ws_wrapper ws2(std::move(ws));
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(ws)), std::runtime_error);

  d_ocp_qp_ipm_ws_wrapper ws3;
  ws3 = (std::move(ws2));
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(ws2)), std::runtime_error);

  const unsigned int N_large = N + distr(eng);
  dim->resize(N_large);
  ws.resize(dim, arg);

  const unsigned int N_small = N - distr(eng);
  dim->resize(N_small);
  ws.resize(dim, arg);
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}