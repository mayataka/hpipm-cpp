#ifndef HPIPM_CPP_UTILS_HPP_
#define HPIPM_CPP_UTILS_HPP_

#include <vector>
#include <algorithm>


namespace hpipm {

template <typename T1, typename T2>
void fill_vector(std::vector<T1>& vec, const T2& value) {
  std::fill(vec.begin(), vec.end(), value);
}

} // namespace hpipm

#endif // HPIPM_CPP_UTILS_HPP_