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
    : values_(&values)
    , allocated_(false)
    { }

    ~MyMatrix();

    //MyMatrix operator*(MyMatrix& other);

    MyVector<M> operator*(MyVector<M>& other);

    void print() const;

  private:
    MyMatrix()
    : values_(new std::vector<double>(M * N))
    , allocated_(true)
    { }

    size_t max_width() const;

    bool allocated_;
    std::vector<double>* values_;
};

#include "my_matrix.hxx"
