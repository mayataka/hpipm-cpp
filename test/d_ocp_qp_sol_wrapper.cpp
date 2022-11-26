#include <gtest/gtest.h>
#include <random>

#include "hpipm-cpp/detail/d_ocp_qp_sol_wrapper.hpp"


namespace hpipm {

class d_ocp_qp_sol_wrapper_test : public ::testing::Test {
protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

bool hasNullptr(const d_ocp_qp_sol_wrapper& sol) {
  return sol.get()->dim == nullptr
      || sol.get()->ux == nullptr
      || sol.get()->pi == nullptr
      || sol.get()->lam == nullptr
      || sol.get()->t == nullptr;
}

bool hasOnlyNullptr(const d_ocp_qp_sol_wrapper& sol) {
  return sol.get()->dim == nullptr
      && sol.get()->ux == nullptr
      && sol.get()->pi == nullptr
      && sol.get()->lam == nullptr
      && sol.get()->t == nullptr;
}

bool hasSamePtr(const d_ocp_qp_sol_wrapper& sol1, 
                const d_ocp_qp_sol_wrapper& sol2) {
  return sol1.get() == sol2.get()
      // || sol1.get()->dim == sol2.get()->dim
      || sol1.get()->ux == sol2.get()->ux
      || sol1.get()->pi == sol2.get()->pi
      || sol1.get()->lam == sol2.get()->lam
      || sol1.get()->t == sol2.get()->t;
}


TEST_F(d_ocp_qp_sol_wrapper_test, copy) {
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

  d_ocp_qp_sol_wrapper sol(dim);
  EXPECT_FALSE(hasNullptr(sol));

  d_ocp_qp_sol_wrapper sol2(sol);
  EXPECT_FALSE(hasNullptr(sol2));
  EXPECT_FALSE(hasSamePtr(sol2, sol));
  EXPECT_TRUE(sol2.get()->dim == sol.get()->dim);

  d_ocp_qp_sol_wrapper sol3;
  sol3 = sol;
  EXPECT_FALSE(hasNullptr(sol3));
  EXPECT_FALSE(hasSamePtr(sol3, sol));
  EXPECT_TRUE(sol3.get()->dim == sol.get()->dim);
}


TEST_F(d_ocp_qp_sol_wrapper_test, move) {
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

  d_ocp_qp_sol_wrapper sol(dim);
  EXPECT_FALSE(hasNullptr(sol));

  d_ocp_qp_sol_wrapper sol2(sol);

  d_ocp_qp_sol_wrapper sol3(std::move(sol2));
  EXPECT_FALSE(hasNullptr(sol3));
  EXPECT_FALSE(hasSamePtr(sol3, sol));
  EXPECT_TRUE(sol3.get()->dim == sol.get()->dim);
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(sol2)), std::runtime_error);

  d_ocp_qp_sol_wrapper sol4(sol);

  d_ocp_qp_sol_wrapper sol5;
  sol5 = std::move(sol4);
  EXPECT_FALSE(hasNullptr(sol5));
  EXPECT_FALSE(hasSamePtr(sol5, sol));
  EXPECT_TRUE(sol5.get()->dim == sol.get()->dim);
  EXPECT_THROW(EXPECT_TRUE(hasOnlyNullptr(sol4)), std::runtime_error);
}


TEST_F(d_ocp_qp_sol_wrapper_test, resize) {
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

  d_ocp_qp_sol_wrapper sol(dim);

  const unsigned int N_large = N + distr(eng);
  dim->resize(N_large);
  sol.resize(dim);
  EXPECT_FALSE(hasNullptr(sol));

  const unsigned int N_small = N - distr(eng);
  dim->resize(N_small);
  sol.resize(dim);
  EXPECT_FALSE(hasNullptr(sol));
}

} // namespace hpipm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}