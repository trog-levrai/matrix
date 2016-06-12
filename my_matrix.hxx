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
    for (size_t j = 0; j < N; ++j)
      (*ans)[i] += (*values_)[i * N + j] * other.get_values()[j];
  }
  return *(new MyVector<M>(*ans, true));
}

static inline
size_t get_pos(size_t i, size_t j, size_t M)
{
  return i + j * M;
}

template <unsigned int M, unsigned int N>
MyMatrix<M, M> MyMatrix<M, N>::operator*(MyMatrix<N, M>& other)
{
  auto ans = MyMatrix<M, M>();
  for (size_t i = 0; i < M; ++i)
  {
    #pragma omp parallel for
    for (size_t j = 0; j < M; ++j)
    {
      for (size_t k = 0; k < N; ++k)
        (*ans.values_)[get_pos((i + j) % M, j, M)] +=
          (*values_)[get_pos(k, j, N)]
          * (*other.values_)[get_pos((i + j) % M, k, M)];
    }
  }
  return ans;
}

template <unsigned int M, unsigned int N>
bool MyMatrix<M, N>::operator==(const MyMatrix<N, M>& other) const
{
  for (size_t i = 0; i < M * N; ++i)
  {
    if (values_[i] != other.values_[i])
      return false;
  }
  return true;
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
      auto str = ostr.str().length();
      if (ans < str) {
        #pragma omp atomic write
        ans = str;
      }
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
