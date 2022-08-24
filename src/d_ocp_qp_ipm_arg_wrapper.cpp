#include "hpipm-cpp/d_ocp_qp_ipm_arg_wrapper.hpp"


namespace hpipm {

d_ocp_qp_ipm_arg_wrapper::d_ocp_qp_ipm_arg_wrapper() 
  : ocp_qp_ipm_arg_hpipm_(),
    memory_(nullptr),
    memsize_(0) {
  resize();
}


d_ocp_qp_ipm_arg_wrapper::~d_ocp_qp_ipm_arg_wrapper() {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
  }
}


d_ocp_qp_ipm_arg_wrapper::d_ocp_qp_ipm_arg_wrapper(const d_ocp_qp_ipm_arg_wrapper& other)
  : d_ocp_qp_ipm_arg_wrapper() {
  copy(other);
}


d_ocp_qp_ipm_arg_wrapper& d_ocp_qp_ipm_arg_wrapper::operator=(const d_ocp_qp_ipm_arg_wrapper& other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}


d_ocp_qp_ipm_arg* d_ocp_qp_ipm_arg_wrapper::get() { 
  return &ocp_qp_ipm_arg_hpipm_; 
}


const d_ocp_qp_ipm_arg* d_ocp_qp_ipm_arg_wrapper::get() const { 
  return &ocp_qp_ipm_arg_hpipm_; 
}


void d_ocp_qp_ipm_arg_wrapper::resize() {
  d_ocp_qp_dim ocp_qp_dim_hpipm; // this does nothing in the below
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_arg_memsize(&ocp_qp_dim_hpipm);
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_ipm_arg_create(&ocp_qp_dim_hpipm, &ocp_qp_ipm_arg_hpipm_, memory_);
  }
}


void d_ocp_qp_ipm_arg_wrapper::copy(const d_ocp_qp_ipm_arg_wrapper& other) {
  d_ocp_qp_ipm_arg* other_ptr = const_cast<d_ocp_qp_ipm_arg_wrapper&>(other).get();
  d_ocp_qp_ipm_arg_set_mu0(&other_ptr->mu0, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_alpha_min(&other_ptr->alpha_min, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_stat(&other_ptr->res_g_max, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_eq(&other_ptr->res_b_max, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_ineq(&other_ptr->res_d_max, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tol_comp(&other_ptr->res_m_max, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_iter_max(&other_ptr->iter_max, &ocp_qp_ipm_arg_hpipm_);
  ocp_qp_ipm_arg_hpipm_.stat_max = other_ptr->stat_max;
  d_ocp_qp_ipm_arg_set_pred_corr(&other_ptr->pred_corr, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_cond_pred_corr(&other_ptr->cond_pred_corr, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_ric_alg(&other_ptr->square_root_alg, &ocp_qp_ipm_arg_hpipm_);
  ocp_qp_ipm_arg_hpipm_.itref_pred_max = other_ptr->itref_pred_max;
  ocp_qp_ipm_arg_hpipm_.itref_corr_max = other_ptr->itref_corr_max;
  d_ocp_qp_ipm_arg_set_reg_prim(&other_ptr->reg_prim, &ocp_qp_ipm_arg_hpipm_);
  ocp_qp_ipm_arg_hpipm_.lq_fact = other_ptr->lq_fact;
  d_ocp_qp_ipm_arg_set_lam_min(&other_ptr->lam_min, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_t_min(&other_ptr->t_min, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_tau_min(&other_ptr->tau_min, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_warm_start(&other_ptr->warm_start, &ocp_qp_ipm_arg_hpipm_);
  ocp_qp_ipm_arg_hpipm_.abs_form = other_ptr->abs_form;
  d_ocp_qp_ipm_arg_set_comp_dual_sol_eq(&other_ptr->comp_dual_sol_eq, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_comp_res_pred(&other_ptr->comp_res_pred, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_comp_res_exit(&other_ptr->comp_res_pred, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_split_step(&other_ptr->split_step, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_var_init_scheme(&other_ptr->var_init_scheme, &ocp_qp_ipm_arg_hpipm_);
  d_ocp_qp_ipm_arg_set_t_lam_min(&other_ptr->t_lam_min, &ocp_qp_ipm_arg_hpipm_);
}

} // namespace hpipm