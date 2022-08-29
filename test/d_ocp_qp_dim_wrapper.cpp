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


TEST_F(d_ocp_qp_dim_wrapper_test, copy) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> distr(0, 10);

  const unsigned int N = 10;
  d_ocp_qp_dim_wrapper dim(N);
  EXPECT_EQ(dim.get()->N, 10);
  for (unsigned int i=0; i<=10; ++i) {
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
  EXPECT_EQ(dim2.get()->N, dim.get()->N);
  for (unsigned int i=0; i<=10; ++i) {
    EXPECT_EQ(dim2.get()->nx[i],   dim.get()->nx[i]);
    EXPECT_EQ(dim2.get()->nu[i],   dim.get()->nu[i]);
    EXPECT_EQ(dim2.get()->nbx[i],  dim.get()->nbx[i]);
    EXPECT_EQ(dim2.get()->nbu[i],  dim.get()->nbu[i]);
    EXPECT_EQ(dim2.get()->ng[i],   dim.get()->ng[i]);
    EXPECT_EQ(dim2.get()->ns[i],   dim.get()->ns[i]);
    EXPECT_EQ(dim2.get()->nsbx[i], dim.get()->nsbx[i]);
    EXPECT_EQ(dim2.get()->nsbu[i], dim.get()->nsbu[i]);
    EXPECT_EQ(dim2.get()->nsg[i],  dim.get()->nsg[i]);
    EXPECT_EQ(dim2.get()->nbxe[i], dim.get()->nbxe[i]);
    EXPECT_EQ(dim2.get()->nbue[i], dim.get()->nbue[i]);
    EXPECT_EQ(dim2.get()->ng[i],   dim.get()->ng[i]);
  }
  EXPECT_EQ(dim2.get()->memsize, dim.get()->memsize);
  EXPECT_TRUE(dim2.get() != dim.get());
  EXPECT_TRUE(dim2.get()->nx != dim.get()->nx);
  EXPECT_TRUE(dim2.get()->nu != dim.get()->nu);
  EXPECT_TRUE(dim2.get()->nb != dim.get()->nb);
  EXPECT_TRUE(dim2.get()->nbx != dim.get()->nbx);
  EXPECT_TRUE(dim2.get()->nbu != dim.get()->nbu);
  EXPECT_TRUE(dim2.get()->ng != dim.get()->ng);
  EXPECT_TRUE(dim2.get()->ns != dim.get()->ns);
  EXPECT_TRUE(dim2.get()->nsbx != dim.get()->nsbx);
  EXPECT_TRUE(dim2.get()->nsbu != dim.get()->nsbu);
  EXPECT_TRUE(dim2.get()->nsg != dim.get()->nsg);
  EXPECT_TRUE(dim2.get()->nbxe != dim.get()->nbxe);
  EXPECT_TRUE(dim2.get()->nbue != dim.get()->nbue);
  EXPECT_TRUE(dim2.get()->nge != dim.get()->nge);

  d_ocp_qp_dim_wrapper dim3;
  dim3 = dim;
  EXPECT_EQ(dim3.get()->N, dim.get()->N);
  for (unsigned int i=0; i<=10; ++i) {
    EXPECT_EQ(dim3.get()->nx[i],   dim.get()->nx[i]);
    EXPECT_EQ(dim3.get()->nu[i],   dim.get()->nu[i]);
    EXPECT_EQ(dim3.get()->nbx[i],  dim.get()->nbx[i]);
    EXPECT_EQ(dim3.get()->nbu[i],  dim.get()->nbu[i]);
    EXPECT_EQ(dim3.get()->ng[i],   dim.get()->ng[i]);
    EXPECT_EQ(dim3.get()->ns[i],   dim.get()->ns[i]);
    EXPECT_EQ(dim3.get()->nsbx[i], dim.get()->nsbx[i]);
    EXPECT_EQ(dim3.get()->nsbu[i], dim.get()->nsbu[i]);
    EXPECT_EQ(dim3.get()->nsg[i],  dim.get()->nsg[i]);
    EXPECT_EQ(dim3.get()->nbxe[i], dim.get()->nbxe[i]);
    EXPECT_EQ(dim3.get()->nbue[i], dim.get()->nbue[i]);
    EXPECT_EQ(dim3.get()->ng[i],   dim.get()->ng[i]);
  }
  EXPECT_EQ(dim3.get()->memsize, dim.get()->memsize);
  EXPECT_TRUE(dim3.get() != dim.get());
  EXPECT_TRUE(dim3.get()->nx != dim.get()->nx);
  EXPECT_TRUE(dim3.get()->nu != dim.get()->nu);
  EXPECT_TRUE(dim3.get()->nb != dim.get()->nb);
  EXPECT_TRUE(dim3.get()->nbx != dim.get()->nbx);
  EXPECT_TRUE(dim3.get()->nbu != dim.get()->nbu);
  EXPECT_TRUE(dim3.get()->ng != dim.get()->ng);
  EXPECT_TRUE(dim3.get()->ns != dim.get()->ns);
  EXPECT_TRUE(dim3.get()->nsbx != dim.get()->nsbx);
  EXPECT_TRUE(dim3.get()->nsbu != dim.get()->nsbu);
  EXPECT_TRUE(dim3.get()->nsg != dim.get()->nsg);
  EXPECT_TRUE(dim3.get()->nbxe != dim.get()->nbxe);
  EXPECT_TRUE(dim3.get()->nbue != dim.get()->nbue);
  EXPECT_TRUE(dim3.get()->nge != dim.get()->nge);
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}