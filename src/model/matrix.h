#ifndef SRC_MODEL_MATRIX_H_
#define SRC_MODEL_MATRIX_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace view3d {
class Model;

class Matrix {
  friend class Model;

 public:
  Matrix() : rows_(0), columns_(0), matrix_(0) {}
  Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns) {}
  Matrix(const Matrix &other) { *this = other; }
  Matrix(Matrix &&other) { *this = std::move(other); }
  ~Matrix() {}

  Matrix &operator=(const Matrix &other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix_ = other.matrix_;
    return *this;
  }

  Matrix &operator=(Matrix &&other) {
    std::swap(rows_, other.rows_);
    std::swap(columns_, other.columns_);
    std::swap(matrix_, other.matrix_);
    return *this;
  }

 private:
  size_t rows_;
  size_t columns_;
  std::vector<std::vector<double>> matrix_;
};

}  // namespace view3d

#endif  //  SRC_MODEL_MATRIX_H_
