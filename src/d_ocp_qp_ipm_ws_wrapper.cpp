#include "hpipm-cpp/d_ocp_qp_ipm_ws_wrapper.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>


namespace hpipm {

d_ocp_qp_ipm_ws_wrapper::d_ocp_qp_ipm_ws_wrapper(const d_ocp_qp_dim_wrapper& dim,
                                                 const d_ocp_qp_ipm_arg_wrapper& ipm_arg) 
  : d_ocp_qp_ipm_ws_wrapper() {
  resize(dim_, ipm_arg_);
}


d_ocp_qp_ipm_ws_wrapper::d_ocp_qp_ipm_ws_wrapper() 
  : dim_(),
    ipm_arg_(),
    ocp_qp_ipm_ws_hpipm_(),
    memory_(nullptr),
    memsize_(0) {
}


d_ocp_qp_ipm_ws_wrapper::~d_ocp_qp_ipm_ws_wrapper() {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
  }
}


d_ocp_qp_ipm_ws* d_ocp_qp_ipm_ws_wrapper::get() { 
  if (memory_ == nullptr) {
    throw std::runtime_error("[d_ocp_qp_ipm_ws_wrapper] hpipm memory is not created. Call resize() first.");
  }
  return &ocp_qp_ipm_ws_hpipm_; 
}


const d_ocp_qp_ipm_ws* d_ocp_qp_ipm_ws_wrapper::get() const { 
  return &ocp_qp_ipm_ws_hpipm_; 
}


const d_ocp_qp_dim_wrapper& d_ocp_qp_ipm_ws_wrapper::dim() const {
  return dim_;
}


const d_ocp_qp_ipm_arg_wrapper& d_ocp_qp_ipm_ws_wrapper::ipm_arg() const {
  return ipm_arg_;
}


void d_ocp_qp_ipm_ws_wrapper::resize(const d_ocp_qp_dim_wrapper& dim, 
                                     const d_ocp_qp_ipm_arg_wrapper& ipm_arg) {
  dim_ = dim;
  ipm_arg_ = ipm_arg;
  const hpipm_size_t new_memsize = d_ocp_qp_ipm_ws_memsize(dim_.get(), 
                                                           ipm_arg_.get());
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_ipm_ws_create(dim_.get(), ipm_arg_.get(), &ocp_qp_ipm_ws_hpipm_, memory_);
  }
}

} // namespace hpipm