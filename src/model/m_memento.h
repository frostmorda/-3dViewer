#ifndef SRC_MODEL_M_MEMENTO_H_
#define SRC_MODEL_M_MEMENTO_H_

#include <iostream>

#include "../misc.h"
#include "matrix.h"
#include "mvpmatrix.h"
#include "polygon.h"

namespace view3d {
class Memento {
  friend class Model;

 public:
  Memento() = default;
  explicit Memento(const MVPMatrix &mvp_matrix) : mvp_matrix_(mvp_matrix) {}
  Memento(const Memento &other) { *this = other; }
  Memento(Memento &&other) { *this = std::move(other); }
  ~Memento() {}

  Memento &operator=(const Memento &other) {
    mvp_matrix_ = other.mvp_matrix_;
    return *this;
  }
  Memento &operator=(Memento &&other) {
    std::swap(mvp_matrix_, other.mvp_matrix_);
    return *this;
  }

 private:
  MVPMatrix mvp_matrix_;
};
}  // namespace view3d

#endif  // SRC_MODEL_M_MEMENTO_H_
