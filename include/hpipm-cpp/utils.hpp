#ifndef HPIPM_CPP_UTILS_HPP_
#define HPIPM_CPP_UTILS_HPP_

#include <vector>
#include <algorithm>


namespace hpipm {

template <typename T>
void fill_vector(std::vector<T>& vec, const T& value) {
  std::fill(vec.begin(), vec.end(), value);
}

} // namespace hpipm

#endif // HPIPM_CPP_UTILS_HPP_