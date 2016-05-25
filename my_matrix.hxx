#include "my_matrix.hh"

template <unsigned int M, unsigned int N>
MyVector<M> MyMatrix<M, N>::operator*(MyVector<M>& other) {
  auto ans = std::vector<double>(M, 0);
  #pragma omp parallel for
  for (size_t i = 0; i < M; ++i) {
    #pragma parallel for reduction(+:ans[i])
    for (size_t j = 0; j < N; ++j)
      ans[i] += values_[i][j] * other.get_values()[j];
  }
  #pragma barrier
  return MyVector<M>(ans);
}

template <unsigned int M, unsigned int N>
size_t MyMatrix<M, N>::max_width() const {
  size_t ans = 0;
  #pragma omp parallel for
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::ostringstream ostr;
      ostr << values_[i][j];
      auto str = ostr.str();
      if (ans < str.length())
        ans = str.length();
    }
  }
  #pragma omp barrier
  return ans;
}

template <unsigned int M, unsigned int N>
void MyMatrix<M, N>::print() const {
  size_t size = max_width();
  for (size_t i = 0; i < 1 + N * (size + 1); ++i)
    std::cout << "-";
  std::cout << std::endl;
  for (size_t i = 0; i < M; ++i) {
    std::cout << "|";
    for (size_t j = 0; j < N; ++j)
      std::cout << std::setw(size) << values_[i][j] << "|";
    std::cout << std::endl;
  }
  for (size_t i = 0; i < 1 + N * (size + 1); ++i)
    std::cout << "-";
  std::cout << std::endl;
}
