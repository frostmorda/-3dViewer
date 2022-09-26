#ifndef SRC_MODEL_MVPMATRIX_H_
#define SRC_MODEL_MVPMATRIX_H_

#include <vector>

#include "../misc.h"

namespace view3d {
class MVPMatrix {
 public:
  using matrix_4x4 = std::vector<std::vector<double>>;
  MVPMatrix();

  MVPMatrix(const MVPMatrix &other) { *this = other; }

  MVPMatrix(MVPMatrix &&other) { *this = std::move(other); }

  ~MVPMatrix() {}

  MVPMatrix &operator=(const MVPMatrix &other) {
    mvp_matrix_ = other.mvp_matrix_;
    translation_matrix_ = other.translation_matrix_;
    extremums_ = other.extremums_;
    angle_x_ = other.angle_x_;
    angle_y_ = other.angle_y_;
    angle_z_ = other.angle_z_;
    step_x_ = other.step_x_;
    step_y_ = other.step_y_;
    step_z_ = other.step_z_;
    scale_ = other.scale_;
    return *this;
  }

  MVPMatrix &operator=(MVPMatrix &&other) {
    std::swap(mvp_matrix_, other.mvp_matrix_);
    std::swap(translation_matrix_, other.translation_matrix_);
    std::swap(extremums_, other.extremums_);
    std::swap(angle_x_, other.angle_x_);
    std::swap(angle_y_, other.angle_y_);
    std::swap(angle_z_, other.angle_z_);
    std::swap(step_x_, other.step_x_);
    std::swap(step_y_, other.step_y_);
    std::swap(step_z_, other.step_z_);
    std::swap(scale_, other.scale_);
    return *this;
  }

  matrix_4x4 &GetMVPMatrix() { return mvp_matrix_; }
  matrix_4x4 &GetTranslationMatrix() { return translation_matrix_; }
  matrix_4x4 GetProjectionCentral();
  void SetAngleX(const double x) { angle_x_ = x; }
  void SetAngleY(const double y) { angle_y_ = y; }
  void SetAngleZ(const double z) { angle_z_ = z; }
  void SetTranslationX(const double x) { step_x_ = x; }
  void SetTranslationY(const double y) { step_y_ = y; }
  void SetTranslationZ(const double z) { step_z_ = z; }
  void SetScale(const double scale) { scale_ = scale; }
  void RotationX();
  void RotationY();
  void RotationZ();
  void TranslationX();
  void TranslationY();
  void TranslationZ();
  void Scale();
  void NormalizeModel();
  void SetExtremums(const Extremums &extremums) { extremums_ = extremums; }
  void Clear();

 private:
  matrix_4x4 mvp_matrix_;
  matrix_4x4 translation_matrix_;
  Extremums extremums_;
  double angle_x_;
  double angle_y_;
  double angle_z_;
  double step_x_;
  double step_y_;
  double step_z_;
  double scale_;
  const double to_radian_ = 57.2958;

  void MultiplyMatrix(matrix_4x4 &matrix1, const matrix_4x4 &matrix2);
  void MultiplyNumber(matrix_4x4 &mat, const double num);
  double NormScale();
  matrix_4x4 ScaleMatrix(double scale);
};
}  // namespace view3d
#endif  // SRC_MODEL_MVPMATRIX_H_
