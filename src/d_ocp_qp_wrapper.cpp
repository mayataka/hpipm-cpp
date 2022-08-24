#include "hpipm-cpp/d_ocp_qp_wrapper.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>


namespace hpipm {

d_ocp_qp_wrapper::d_ocp_qp_wrapper(const d_ocp_qp_dim_wrapper& dim) 
  : d_ocp_qp_wrapper() {
  resize(dim);
}


d_ocp_qp_wrapper::d_ocp_qp_wrapper() 
  : dim_(),
    ocp_qp_hpipm_(),
    memory_(nullptr),
    memsize_(0) {
}


d_ocp_qp_wrapper::~d_ocp_qp_wrapper() {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
  }
}


d_ocp_qp_wrapper::d_ocp_qp_wrapper(const d_ocp_qp_wrapper& other) {
  copy(other);
}


d_ocp_qp_wrapper& d_ocp_qp_wrapper::operator=(const d_ocp_qp_wrapper& other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}


d_ocp_qp* d_ocp_qp_wrapper::get() { 
  if (memory_ == nullptr) {
    throw std::runtime_error("[d_ocp_qp_wrapper] hpipm memory is not created. Call resize() first.");
  }
  return &ocp_qp_hpipm_; 
}


const d_ocp_qp* d_ocp_qp_wrapper::get() const { 
  return &ocp_qp_hpipm_; 
}


const d_ocp_qp_dim_wrapper& d_ocp_qp_wrapper::dim() const {
  return dim_;
}


void d_ocp_qp_wrapper::resize(const d_ocp_qp_dim_wrapper& dim) {
  dim_ = dim;
  const hpipm_size_t new_memsize = d_ocp_qp_memsize(dim_.get());
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
    d_ocp_qp_create(dim_.get(), &ocp_qp_hpipm_, memory_);
  }
}


void d_ocp_qp_wrapper::copy(const d_ocp_qp_wrapper& other) {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = 0;
  resize(other.dim());

  d_ocp_qp_copy_all(const_cast<d_ocp_qp*>(other.get()), &ocp_qp_hpipm_); 
}

} // namespace hpipm