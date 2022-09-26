#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../misc.h"
#include "m_memento.h"
#include "matrix.h"
#include "mvpmatrix.h"
#include "polygon.h"

namespace view3d {
class Model {
 public:
  Model() = default;

  bool MakeObject(const std::string &filename);
  float GetMatrixValueAt(const size_t row, const size_t column) {
    return matrix_points_.matrix_.at(row).at(column);
  }
  float GetVerticeValueAt(const size_t position) {
    return polygons_.vertices_united_.at(position);
  }
  size_t GetCountOfVertices() { return count_of_vertices_; }
  size_t GetCountOfFacets() { return count_of_facets_; }
  MVPMatrix &GetMVPMatrix() { return mvp_matrix_; }
  Polygon &GetPolygon() { return polygons_; }
  void SetExtremums() { mvp_matrix_.SetExtremums(extremums_); }

  Memento SaveMemento() { return *new Memento(mvp_matrix_); }
  void RestoreMemento(Memento memento) { mvp_matrix_ = memento.mvp_matrix_; }
  void ResetModel();

 private:
  Matrix matrix_points_;
  Polygon polygons_;
  MVPMatrix mvp_matrix_;
  Extremums extremums_;
  size_t count_of_facets_;
  size_t count_of_vertices_;

  void ParseFile(std::ifstream *read_file);
  void FindExtremums();
  void FindXExtremums();
  void FindYExtremums();
  void FindZExtremums();
  void UnitePolygons(const std::vector<std::vector<int>> &poligons_vector);
  void TransformFacetsToVertices(const std::vector<int> &polygons_united);
  void Clear();
};
}  // namespace view3d

#endif  // SRC_MODEL_MODEL_H_
