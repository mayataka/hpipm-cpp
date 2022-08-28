#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>


namespace hpipm {

d_ocp_qp_dim_wrapper::d_ocp_qp_dim_wrapper(const unsigned int N) 
  : d_ocp_qp_dim_wrapper() {
  if (N > 0) {
    resize(N);
  }
}


d_ocp_qp_dim_wrapper::d_ocp_qp_dim_wrapper() 
  : ocp_qp_dim_hpipm_(),
    memory_(nullptr),
    memsize_(0) {
}


d_ocp_qp_dim_wrapper::~d_ocp_qp_dim_wrapper() {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
    memsize_ = 0;
  }
}


d_ocp_qp_dim_wrapper::d_ocp_qp_dim_wrapper(const d_ocp_qp_dim_wrapper& other) 
  : d_ocp_qp_dim_wrapper() {
  copy(other);
}


d_ocp_qp_dim_wrapper& d_ocp_qp_dim_wrapper::operator=(const d_ocp_qp_dim_wrapper& other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}


d_ocp_qp_dim_wrapper::d_ocp_qp_dim_wrapper(d_ocp_qp_dim_wrapper&& other) noexcept
  : ocp_qp_dim_hpipm_(other.ocp_qp_dim_hpipm_),
    memory_(other.memory_),
    memsize_(other.memsize_) {
  other.ocp_qp_dim_hpipm_.nx   = nullptr;
  other.ocp_qp_dim_hpipm_.nu   = nullptr;
  other.ocp_qp_dim_hpipm_.nb   = nullptr;
  other.ocp_qp_dim_hpipm_.nbx  = nullptr;
  other.ocp_qp_dim_hpipm_.nbu  = nullptr;
  other.ocp_qp_dim_hpipm_.ng   = nullptr;
  other.ocp_qp_dim_hpipm_.ns   = nullptr;
  other.ocp_qp_dim_hpipm_.nsbx = nullptr;
  other.ocp_qp_dim_hpipm_.nsbu = nullptr;
  other.ocp_qp_dim_hpipm_.nsg  = nullptr;
  other.ocp_qp_dim_hpipm_.nbxe = nullptr;
  other.ocp_qp_dim_hpipm_.nbue = nullptr;
  other.ocp_qp_dim_hpipm_.nge  = nullptr;
  other.ocp_qp_dim_hpipm_.N = 0;
  other.ocp_qp_dim_hpipm_.memsize = 0;
  other.memory_ = nullptr;
  other.memsize_ = 0;
}


d_ocp_qp_dim_wrapper& d_ocp_qp_dim_wrapper::operator=(d_ocp_qp_dim_wrapper&& other) noexcept {
  if (this != &other) {
    if (memory_) {
      free(memory_);
      memory_ = nullptr;
      memsize_ = 0;
    }
    ocp_qp_dim_hpipm_ = other.ocp_qp_dim_hpipm_;
    memory_ = other.memory_;
    memsize_ = other.memsize_;
    other.ocp_qp_dim_hpipm_.nx   = nullptr;
    other.ocp_qp_dim_hpipm_.nu   = nullptr;
    other.ocp_qp_dim_hpipm_.nb   = nullptr;
    other.ocp_qp_dim_hpipm_.nbx  = nullptr;
    other.ocp_qp_dim_hpipm_.nbu  = nullptr;
    other.ocp_qp_dim_hpipm_.ng   = nullptr;
    other.ocp_qp_dim_hpipm_.ns   = nullptr;
    other.ocp_qp_dim_hpipm_.nsbx = nullptr;
    other.ocp_qp_dim_hpipm_.nsbu = nullptr;
    other.ocp_qp_dim_hpipm_.nsg  = nullptr;
    other.ocp_qp_dim_hpipm_.nbxe = nullptr;
    other.ocp_qp_dim_hpipm_.nbue = nullptr;
    other.ocp_qp_dim_hpipm_.nge  = nullptr;
    other.ocp_qp_dim_hpipm_.N = 0;
    other.ocp_qp_dim_hpipm_.memsize = 0;
    other.memory_ = nullptr;
    other.memsize_ = 0;
  }
  return *this;
}


d_ocp_qp_dim* d_ocp_qp_dim_wrapper::get() { 
  if (memory_ == nullptr) {
    throw std::runtime_error("[d_ocp_qp_dim_wrapper] hpipm memory is not created. Call resize() first.");
  }
  return &ocp_qp_dim_hpipm_; 
}


const d_ocp_qp_dim* d_ocp_qp_dim_wrapper::get() const { 
  return &ocp_qp_dim_hpipm_; 
}


void d_ocp_qp_dim_wrapper::resize(const unsigned int N) {
  const hpipm_size_t new_memsize = d_ocp_qp_dim_memsize(N);
  if (memory_ && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (!memory_) {
    memory_ = malloc(memsize_);
	  d_ocp_qp_dim_create(N, &ocp_qp_dim_hpipm_, memory_);
  }
}


void d_ocp_qp_dim_wrapper::copy(const d_ocp_qp_dim_wrapper& other) {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = 0;
  resize(static_cast<unsigned int>(other.get()->N));

  d_ocp_qp_dim_copy_all(const_cast<d_ocp_qp_dim*>(other.get()), &ocp_qp_dim_hpipm_); 
}

} // namespace hpipm