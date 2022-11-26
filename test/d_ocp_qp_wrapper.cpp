#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/detail/d_ocp_qp_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_wrapper_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

bool hasNullptr(const d_ocp_qp_wrapper& qp) {
  return qp.get()->dim == nullptr
      || qp.get()->BAbt == nullptr
      || qp.get()->RSQrq == nullptr
      || qp.get()->DCt == nullptr
      || qp.get()->b == nullptr
      || qp.get()->rqz == nullptr
      || qp.get()->d == nullptr
      || qp.get()->d_mask == nullptr
      || qp.get()->m == nullptr
      || qp.get()->Z == nullptr
      || qp.get()->idxb == nullptr
      || qp.get()->idxs_rev == nullptr
      || qp.get()->idxe == nullptr
      || qp.get()->diag_H_flag == nullptr;
}

bool hasOnlyNullptr(const d_ocp_qp_wrapper& qp) {
  return qp.get()->dim == nullptr
      && qp.get()->BAbt == nullptr
      && qp.get()->RSQrq == nullptr
      && qp.get()->DCt == nullptr
      && qp.get()->b == nullptr
      && qp.get()->rqz == nullptr
      && qp.get()->d == nullptr
      && qp.get()->d_mask == nullptr
      && qp.get()->m == nullptr
      && qp.get()->Z == nullptr
      && qp.get()->idxb == nullptr
      && qp.get()->idxs_rev == nullptr
      && qp.get()->idxe == nullptr
      && qp.get()->diag_H_flag == nullptr;
}

bool hasSamePtr(const d_ocp_qp_wrapper& qp1, 
                const d_ocp_qp_wrapper& qp2) {
  return qp1.get() == qp2.get()
      // || qp1.get()->dim == qp2.get()->dim
      || qp1.get()->BAbt == qp2.get()->BAbt
      || qp1.get()->RSQrq == qp2.get()->RSQrq
      || qp1.get()->DCt == qp2.get()->DCt
      || qp1.get()->b == qp2.get()->b
      || qp1.get()->rqz == qp2.get()->rqz
      || qp1.get()->d == qp2.get()->d
      || qp1.get()->d_mask == qp2.get()->d_mask
      || qp1.get()->m == qp2.get()->m
      || qp1.get()->Z == qp2.get()->Z
      || qp1.get()->idxb == qp2.get()->idxb
      || qp1.get()->idxs_rev == qp2.get()->idxs_rev
      || qp1.get()->idxe == qp2.get()->idxe
      || qp1.get()->diag_H_flag == qp2.get()->diag_H_flag;
}


TEST_F(d_ocp_qp_wrapper_test, copy) {
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

  d_ocp_qp_wrapper qp(dim);
  EXPECT_FALSE(hasNullptr(qp));

  d_ocp_qp_wrapper qp2(qp);
  EXPECT_FALSE(hasNullptr(qp2));
  EXPECT_FALSE(hasSamePtr(qp2, qp));
  EXPECT_TRUE(qp2.get()->dim == qp.get()->dim);

  d_ocp_qp_wrapper qp3;
  qp3 = qp;
  EXPECT_FALSE(hasNullptr(qp3));
  EXPECT_FALSE(hasSamePtr(qp3, qp));
  EXPECT_TRUE(qp3.get()->dim == qp.get()->dim);
}


TEST_F(d_ocp_qp_wrapper_test, move) {
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

  d_ocp_qp_wrapper qp(dim);
  EXPECT_FALSE(hasNullptr(qp));

  d_ocp_qp_wrapper qp2(qp);

  d_ocp_qp_wrapper qp3(std::move(qp2));
  EXPECT_FALSE(hasNullptr(qp3));
  EXPECT_FALSE(hasSamePtr(qp3, qp));
  EXPECT_TRUE(qp3.get()->dim == qp.get()->dim);
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(qp2)), std::runtime_error);

  d_ocp_qp_wrapper qp4(qp);

  d_ocp_qp_wrapper qp5;
  qp5 = std::move(qp4);
  EXPECT_FALSE(hasNullptr(qp5));
  EXPECT_FALSE(hasSamePtr(qp5, qp));
  EXPECT_TRUE(qp5.get()->dim == qp.get()->dim);
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(qp4)), std::runtime_error);
}


TEST_F(d_ocp_qp_wrapper_test, resize) {
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

  d_ocp_qp_wrapper qp(dim);

  const unsigned int N_large = N + distr(eng);
  dim->resize(N_large);
  qp.resize(dim);
  EXPECT_FALSE(hasNullptr(qp));

  const unsigned int N_small = N - distr(eng);
  dim->resize(N_small);
  qp.resize(dim);
  EXPECT_FALSE(hasNullptr(qp));
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}