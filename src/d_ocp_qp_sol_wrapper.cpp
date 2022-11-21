#include "hpipm-cpp/d_ocp_qp_sol_wrapper.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>


namespace hpipm {

d_ocp_qp_sol_wrapper::d_ocp_qp_sol_wrapper(const d_ocp_qp_dim_wrapper& dim) 
  : d_ocp_qp_sol_wrapper() {
  resize(dim);
}


d_ocp_qp_sol_wrapper::d_ocp_qp_sol_wrapper() 
  : dim_(),
    ocp_qp_sol_hpipm_(),
    memory_(nullptr),
    memsize_(0) {
}


d_ocp_qp_sol_wrapper::~d_ocp_qp_sol_wrapper() {
  if (memory_) {
    free(memory_);
    memory_ = nullptr;
    memsize_ = 0;
  }
}


d_ocp_qp_sol_wrapper::d_ocp_qp_sol_wrapper(const d_ocp_qp_sol_wrapper& other) 
  : d_ocp_qp_sol_wrapper() {
  copy(other);
}


d_ocp_qp_sol_wrapper& d_ocp_qp_sol_wrapper::operator=(const d_ocp_qp_sol_wrapper& other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}


d_ocp_qp_sol_wrapper::d_ocp_qp_sol_wrapper(d_ocp_qp_sol_wrapper&& other) noexcept 
  : dim_(std::move(other.dim_)),
    ocp_qp_sol_hpipm_(other.ocp_qp_sol_hpipm_),
    memory_(other.memory_),
    memsize_(other.memsize_) {
  other.ocp_qp_sol_hpipm_.dim  = nullptr;
  other.ocp_qp_sol_hpipm_.ux   = nullptr;
  other.ocp_qp_sol_hpipm_.pi   = nullptr;
  other.ocp_qp_sol_hpipm_.lam  = nullptr;
  other.ocp_qp_sol_hpipm_.t    = nullptr;
  other.ocp_qp_sol_hpipm_.misc = nullptr;
  other.ocp_qp_sol_hpipm_.memsize = 0;
  other.memory_ = nullptr;
  other.memsize_ = 0;
}


d_ocp_qp_sol_wrapper& d_ocp_qp_sol_wrapper::operator=(d_ocp_qp_sol_wrapper&& other) noexcept {
  if (this == &other) return *this;

  if (memory_) {
    free(memory_);
    memory_ = nullptr;
    memsize_ = 0;
  }
  dim_ = std::move(other.dim_);
  ocp_qp_sol_hpipm_ = other.ocp_qp_sol_hpipm_;
  memory_ = other.memory_;
  memsize_ = other.memsize_;

  other.ocp_qp_sol_hpipm_.dim  = nullptr;
  other.ocp_qp_sol_hpipm_.ux   = nullptr;
  other.ocp_qp_sol_hpipm_.pi   = nullptr;
  other.ocp_qp_sol_hpipm_.lam  = nullptr;
  other.ocp_qp_sol_hpipm_.t    = nullptr;
  other.ocp_qp_sol_hpipm_.misc = nullptr;
  other.ocp_qp_sol_hpipm_.memsize = 0;
  other.memory_ = nullptr;
  other.memsize_ = 0;
  return *this;
}


d_ocp_qp_sol* d_ocp_qp_sol_wrapper::get() { 
  if (memory_ == nullptr) {
    throw std::runtime_error("[d_ocp_qp_sol_wrapper] hpipm memory is not created. Call resize() first.");
  }
  return &ocp_qp_sol_hpipm_; 
}


const d_ocp_qp_sol* d_ocp_qp_sol_wrapper::get() const { 
  if (memory_ == nullptr) {
    throw std::runtime_error("[d_ocp_qp_sol_wrapper] hpipm memory is not created. Call resize() first.");
  }
  return &ocp_qp_sol_hpipm_; 
}


void d_ocp_qp_sol_wrapper::resize(const d_ocp_qp_dim_wrapper& dim) {
  dim_ = dim;
  const hpipm_size_t new_memsize = d_ocp_qp_sol_memsize(dim_.get());
  if (memory_ != nullptr && new_memsize > memsize_) {
    free(memory_);
    memory_ = nullptr;
  }
  memsize_ = std::max(memsize_, new_memsize);
  if (memory_ == nullptr) {
    memory_ = malloc(memsize_);
  }
  d_ocp_qp_sol_create(dim_.get(), &ocp_qp_sol_hpipm_, memory_);
}


void d_ocp_qp_sol_wrapper::copy(const d_ocp_qp_sol_wrapper& other) {
  resize(other.dim_);
  d_ocp_qp_sol_copy_all(const_cast<d_ocp_qp_sol*>(other.get()), &ocp_qp_sol_hpipm_); 
}

} // namespace hpipm