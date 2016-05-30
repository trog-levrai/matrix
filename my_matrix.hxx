#include "my_matrix.hh"

template <unsigned int M, unsigned int N>
MyMatrix<M, N>::~MyMatrix()
{
  if (allocated_)
    delete values_;
}

template <unsigned int M, unsigned int N>
MyVector<M> MyMatrix<M, N>::operator*(MyVector<M>& other)
{
  auto ans = new std::vector<double>(M);
  #pragma omp parallel for
  for (size_t i = 0; i < M; ++i) {
    //#pragma parallel for reduction(+:ans[i])
    for (size_t j = 0; j < N; ++j)
      (*ans)[i] += (*values_)[i * N + j] * other.get_values()[j];
  }
  return *(new MyVector<M>(*ans, true));
}

template <unsigned int M, unsigned int N>
size_t MyMatrix<M, N>::max_width() const
{
  size_t ans = 0;
  #pragma omp parallel for
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::ostringstream ostr;
      ostr << values_->at(i * N + j);
      auto str = ostr.str();
      if (ans < str.length())
        ans = str.length();
    }
  }
  return ans;
}

template <unsigned int M, unsigned int N>
void MyMatrix<M, N>::print() const
{
  size_t size = max_width();
  for (size_t i = 0; i < 1 + N * (size + 1); ++i)
    std::cout << "-";
  std::cout << std::endl;
  for (size_t i = 0; i < M; ++i) {
    std::cout << "|";
    for (size_t j = 0; j < N; ++j)
      std::cout << std::setw(size) << values_->at(i * N + j) << "|";
    std::cout << std::endl;
  }
  for (size_t i = 0; i < 1 + N * (size + 1); ++i)
    std::cout << "-";
  std::cout << std::endl;
}
