#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/d_ocp_qp_ipm_arg_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_ipm_arg_wrapper_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  void haveSameValues(const d_ocp_qp_ipm_arg_wrapper& arg1,
                      const d_ocp_qp_ipm_arg_wrapper& arg2) {
    EXPECT_DOUBLE_EQ(arg1.get()->mu0, arg2.get()->mu0);
    EXPECT_DOUBLE_EQ(arg1.get()->alpha_min, arg2.get()->alpha_min);
    EXPECT_DOUBLE_EQ(arg1.get()->res_g_max, arg2.get()->res_g_max);
    EXPECT_DOUBLE_EQ(arg1.get()->res_b_max, arg2.get()->res_b_max);
    EXPECT_DOUBLE_EQ(arg1.get()->res_m_max, arg2.get()->res_m_max);
    EXPECT_DOUBLE_EQ(arg1.get()->reg_prim, arg2.get()->reg_prim);
    EXPECT_DOUBLE_EQ(arg1.get()->lam_min, arg2.get()->lam_min);
    EXPECT_DOUBLE_EQ(arg1.get()->t_min, arg2.get()->t_min);
    EXPECT_DOUBLE_EQ(arg1.get()->tau_min, arg2.get()->tau_min);
    EXPECT_EQ(arg1.get()->iter_max, arg2.get()->iter_max);
    EXPECT_EQ(arg1.get()->stat_max, arg2.get()->stat_max);
    EXPECT_EQ(arg1.get()->pred_corr, arg2.get()->pred_corr);
    EXPECT_EQ(arg1.get()->cond_pred_corr, arg2.get()->cond_pred_corr);
    EXPECT_EQ(arg1.get()->itref_pred_max, arg2.get()->itref_pred_max);
    EXPECT_EQ(arg1.get()->itref_corr_max, arg2.get()->itref_corr_max);
    EXPECT_EQ(arg1.get()->warm_start, arg2.get()->warm_start);
    EXPECT_EQ(arg1.get()->square_root_alg, arg2.get()->square_root_alg);
    EXPECT_EQ(arg1.get()->lq_fact, arg2.get()->lq_fact);
    EXPECT_EQ(arg1.get()->abs_form, arg2.get()->abs_form);
    EXPECT_EQ(arg1.get()->comp_dual_sol_eq, arg2.get()->comp_dual_sol_eq);
    EXPECT_EQ(arg1.get()->comp_res_exit, arg2.get()->comp_res_exit);
    EXPECT_EQ(arg1.get()->comp_res_pred, arg2.get()->comp_res_pred);
    EXPECT_EQ(arg1.get()->split_step, arg2.get()->split_step);
    EXPECT_EQ(arg1.get()->var_init_scheme, arg2.get()->var_init_scheme);
    EXPECT_EQ(arg1.get()->t_lam_min, arg2.get()->t_lam_min);
  }
};

TEST_F(d_ocp_qp_ipm_arg_wrapper_test, copy) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> int_distr(0, 10);
  std::uniform_real_distribution<double> double_distr(0, 10);

  d_ocp_qp_ipm_arg_wrapper arg;
  arg.get()->mu0 = double_distr(eng);
  arg.get()->alpha_min = double_distr(eng);
  arg.get()->res_g_max = double_distr(eng);
  arg.get()->res_b_max = double_distr(eng);
  arg.get()->res_d_max = double_distr(eng);
  arg.get()->res_m_max = double_distr(eng);
  arg.get()->reg_prim = double_distr(eng);
  arg.get()->lam_min = double_distr(eng);
  arg.get()->t_min = double_distr(eng);
  arg.get()->tau_min = double_distr(eng);
  arg.get()->iter_max = int_distr(eng);
  arg.get()->stat_max = int_distr(eng);
  arg.get()->pred_corr = int_distr(eng);
  arg.get()->cond_pred_corr = int_distr(eng);
  arg.get()->itref_pred_max = int_distr(eng);
  arg.get()->itref_corr_max = int_distr(eng);
  arg.get()->warm_start = int_distr(eng);
  arg.get()->square_root_alg = int_distr(eng);
  arg.get()->lq_fact = int_distr(eng);
  arg.get()->abs_form = int_distr(eng);
  arg.get()->comp_dual_sol_eq = int_distr(eng);
  arg.get()->comp_res_exit = int_distr(eng);
  arg.get()->comp_res_pred = int_distr(eng);
  arg.get()->split_step = int_distr(eng);
  arg.get()->var_init_scheme = int_distr(eng);
  arg.get()->t_lam_min = int_distr(eng);

  d_ocp_qp_ipm_arg_wrapper arg2(arg);
  haveSameValues(arg2, arg);

  d_ocp_qp_ipm_arg_wrapper arg3;
  arg3 = arg;
  haveSameValues(arg3, arg);
}


TEST_F(d_ocp_qp_ipm_arg_wrapper_test, move) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> int_distr(0, 10);
  std::uniform_real_distribution<double> double_distr(0, 10);

  d_ocp_qp_ipm_arg_wrapper arg;
  arg.get()->mu0 = double_distr(eng);
  arg.get()->alpha_min = double_distr(eng);
  arg.get()->res_g_max = double_distr(eng);
  arg.get()->res_b_max = double_distr(eng);
  arg.get()->res_d_max = double_distr(eng);
  arg.get()->res_m_max = double_distr(eng);
  arg.get()->reg_prim = double_distr(eng);
  arg.get()->lam_min = double_distr(eng);
  arg.get()->t_min = double_distr(eng);
  arg.get()->tau_min = double_distr(eng);
  arg.get()->iter_max = int_distr(eng);
  arg.get()->stat_max = int_distr(eng);
  arg.get()->pred_corr = int_distr(eng);
  arg.get()->cond_pred_corr = int_distr(eng);
  arg.get()->itref_pred_max = int_distr(eng);
  arg.get()->itref_corr_max = int_distr(eng);
  arg.get()->warm_start = int_distr(eng);
  arg.get()->square_root_alg = int_distr(eng);
  arg.get()->lq_fact = int_distr(eng);
  arg.get()->abs_form = int_distr(eng);
  arg.get()->comp_dual_sol_eq = int_distr(eng);
  arg.get()->comp_res_exit = int_distr(eng);
  arg.get()->comp_res_pred = int_distr(eng);
  arg.get()->split_step = int_distr(eng);
  arg.get()->var_init_scheme = int_distr(eng);
  arg.get()->t_lam_min = int_distr(eng);

  d_ocp_qp_ipm_arg_wrapper arg2(arg);

  d_ocp_qp_ipm_arg_wrapper arg3(std::move(arg2));
  haveSameValues(arg3, arg);

  d_ocp_qp_ipm_arg_wrapper arg4(arg);
  d_ocp_qp_ipm_arg_wrapper arg5;
  arg5 = std::move(arg4);
  haveSameValues(arg5, arg);
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}