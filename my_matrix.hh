#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "my_vector.hh"

template <unsigned int M, unsigned int N>
class MyMatrix {
  public:
    MyMatrix(std::vector<double>& values)
    : values_(std::vector<double>(values))
    { }

    ~MyMatrix() = default;

    //MyMatrix operator*(MyMatrix& other);

    MyVector<M> operator*(MyVector<M>& other);

    void print() const;

  private:
    MyMatrix()
    : values_(std::vector<std::vector<double>>())
    { }

    size_t max_width() const;

    std::vector<double> values_;
};

#include "my_matrix.hxx"
