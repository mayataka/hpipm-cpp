#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/d_ocp_qp_dim_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_dim_wrapper_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

bool hasNullptr(const d_ocp_qp_dim_wrapper& dim) {
  return dim.get()->nx == nullptr
      || dim.get()->nu == nullptr
      || dim.get()->nb == nullptr
      || dim.get()->nbx == nullptr
      || dim.get()->nbu == nullptr
      || dim.get()->ng == nullptr
      || dim.get()->ns == nullptr
      || dim.get()->nsbx == nullptr
      || dim.get()->nsbu == nullptr
      || dim.get()->nsg == nullptr
      || dim.get()->nbxe == nullptr
      || dim.get()->nbue == nullptr
      || dim.get()->nge == nullptr;
}

bool hasOnlyNullptr(const d_ocp_qp_dim_wrapper& dim) {
  return dim.get()->nx == nullptr
      && dim.get()->nu == nullptr
      && dim.get()->nb == nullptr
      && dim.get()->nbx == nullptr
      && dim.get()->nbu == nullptr
      && dim.get()->ng == nullptr
      && dim.get()->ns == nullptr
      && dim.get()->nsbx == nullptr
      && dim.get()->nsbu == nullptr
      && dim.get()->nsg == nullptr
      && dim.get()->nbxe == nullptr
      && dim.get()->nbue == nullptr
      && dim.get()->nge == nullptr;
}

bool hasSameSize(const d_ocp_qp_dim_wrapper& dim1, 
                 const d_ocp_qp_dim_wrapper& dim2) {
  if (dim1.get()->memsize != dim2.get()->memsize) return false;
  if (dim1.get()->N != dim2.get()->N) return false;
  for (unsigned int i=0; i<=dim1.get()->N; ++i) {
    if (dim1.get()->nx[i] != dim2.get()->nx[i]) return false;
    if (dim1.get()->nu[i] != dim2.get()->nu[i]) return false;
    if (dim1.get()->nb[i] != dim2.get()->nb[i]) return false;
    if (dim1.get()->nbx[i] != dim2.get()->nbx[i]) return false;
    if (dim1.get()->nbu[i] != dim2.get()->nbu[i]) return false;
    if (dim1.get()->ng[i] != dim2.get()->ng[i]) return false;
    if (dim1.get()->ns[i] != dim2.get()->ns[i]) return false;
    if (dim1.get()->nsbx[i] != dim2.get()->nsbx[i]) return false;
    if (dim1.get()->nsbu[i] != dim2.get()->nsbu[i]) return false;
    if (dim1.get()->nsg[i] != dim2.get()->nsg[i]) return false;
    if (dim1.get()->nbxe[i] != dim2.get()->nbxe[i]) return false;
    if (dim1.get()->nbue[i] != dim2.get()->nbue[i]) return false;
    if (dim1.get()->nge[i] != dim2.get()->nge[i]) return false;
  }
  return true;
}

bool areSamePtr(const d_ocp_qp_dim_wrapper& dim1, 
                const d_ocp_qp_dim_wrapper& dim2) {
  return dim1.get() == dim2.get()
      && dim1.get()->nx == dim2.get()->nx
      && dim1.get()->nu == dim2.get()->nu
      && dim1.get()->nb == dim2.get()->nb
      && dim1.get()->nbx == dim2.get()->nbx
      && dim1.get()->nbu == dim2.get()->nbu
      && dim1.get()->ng == dim2.get()->ng
      && dim1.get()->ns == dim2.get()->ns
      && dim1.get()->nsbx == dim2.get()->nsbx
      && dim1.get()->nsbu == dim2.get()->nsbu
      && dim1.get()->nsg == dim2.get()->nsg
      && dim1.get()->nbxe == dim2.get()->nbxe
      && dim1.get()->nbue == dim2.get()->nbue
      && dim1.get()->nge == dim2.get()->nge;
}

bool hasSamePtr(const d_ocp_qp_dim_wrapper& dim1, 
                const d_ocp_qp_dim_wrapper& dim2) {
  return dim1.get() == dim2.get()
      || dim1.get()->nx == dim2.get()->nx
      || dim1.get()->nu == dim2.get()->nu
      || dim1.get()->nb == dim2.get()->nb
      || dim1.get()->nbx == dim2.get()->nbx
      || dim1.get()->nbu == dim2.get()->nbu
      || dim1.get()->ng == dim2.get()->ng
      || dim1.get()->ns == dim2.get()->ns
      || dim1.get()->nsbx == dim2.get()->nsbx
      || dim1.get()->nsbu == dim2.get()->nsbu
      || dim1.get()->nsg == dim2.get()->nsg
      || dim1.get()->nbxe == dim2.get()->nbxe
      || dim1.get()->nbue == dim2.get()->nbue
      || dim1.get()->nge == dim2.get()->nge;
}


TEST_F(d_ocp_qp_dim_wrapper_test, copy) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> distr(0, 10);

  const unsigned int N = 10 + distr(eng);
  d_ocp_qp_dim_wrapper dim(N);
  EXPECT_FALSE(hasNullptr(dim));
  EXPECT_EQ(dim.get()->N, N);

  for (unsigned int i=0; i<=N; ++i) {
    dim.get()->nx[i]   = distr(eng);
    dim.get()->nu[i]   = distr(eng);
    dim.get()->nb[i]   = distr(eng);
    dim.get()->nbx[i]  = distr(eng);
    dim.get()->nbu[i]  = distr(eng);
    dim.get()->ng[i]   = distr(eng);
    dim.get()->ns[i]   = distr(eng);
    dim.get()->nsbx[i] = distr(eng);
    dim.get()->nsbu[i] = distr(eng);
    dim.get()->nsg[i]  = distr(eng);
    dim.get()->nbxe[i] = distr(eng);
    dim.get()->nbue[i] = distr(eng);
    dim.get()->nge[i]  = distr(eng);
  }

  d_ocp_qp_dim_wrapper dim2(dim);
  EXPECT_FALSE(hasNullptr(dim2));
  EXPECT_TRUE(hasSameSize(dim2, dim));
  EXPECT_FALSE(hasSamePtr(dim2, dim));

  d_ocp_qp_dim_wrapper dim3;
  dim3 = dim;
  EXPECT_FALSE(hasNullptr(dim3));
  EXPECT_TRUE(hasSameSize(dim3, dim));
  EXPECT_FALSE(hasSamePtr(dim3, dim));
  EXPECT_FALSE(hasSamePtr(dim3, dim2));
}


TEST_F(d_ocp_qp_dim_wrapper_test, move) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> distr(0, 10);

  const unsigned int N = 10 + distr(eng);
  d_ocp_qp_dim_wrapper dim(N);
  EXPECT_EQ(dim.get()->N, N);

  for (unsigned int i=0; i<=N; ++i) {
    dim.get()->nx[i]   = distr(eng);
    dim.get()->nu[i]   = distr(eng);
    dim.get()->nb[i]   = distr(eng);
    dim.get()->nbx[i]  = distr(eng);
    dim.get()->nbu[i]  = distr(eng);
    dim.get()->ng[i]   = distr(eng);
    dim.get()->ns[i]   = distr(eng);
    dim.get()->nsbx[i] = distr(eng);
    dim.get()->nsbu[i] = distr(eng);
    dim.get()->nsg[i]  = distr(eng);
    dim.get()->nbxe[i] = distr(eng);
    dim.get()->nbue[i] = distr(eng);
    dim.get()->nge[i]  = distr(eng);
  }

  d_ocp_qp_dim_wrapper dim2(dim);

  d_ocp_qp_dim_wrapper dim3(std::move(dim2));
  EXPECT_FALSE(hasNullptr(dim3));
  EXPECT_TRUE(hasSameSize(dim3, dim));
  EXPECT_FALSE(hasSamePtr(dim3, dim));
  EXPECT_TRUE(hasOnlyNullptr(dim2));

  d_ocp_qp_dim_wrapper dim4(dim);
  d_ocp_qp_dim_wrapper dim5;
  dim5 = std::move(dim4);
  EXPECT_FALSE(hasNullptr(dim5));
  EXPECT_TRUE(hasSameSize(dim5, dim));
  EXPECT_FALSE(hasSamePtr(dim5, dim));
  EXPECT_TRUE(hasOnlyNullptr(dim4));
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}