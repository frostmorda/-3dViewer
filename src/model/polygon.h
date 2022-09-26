#ifndef SRC_MODEL_POLYGON_H_
#define SRC_MODEL_POLYGON_H_

#include <vector>

namespace view3d {
class Model;
class Polygon {
  friend class Model;

 public:
  using vertices = std::vector<float>;
  vertices &GetVertices() { return vertices_united_; }

 private:
  vertices vertices_united_;
};
}  // namespace view3d

#endif  //  SRC_MODEL_POLYGON_H_
