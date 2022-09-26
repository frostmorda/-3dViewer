#include "mvpmatrix.h"

#include <cmath>

namespace view3d {
MVPMatrix::MVPMatrix()
    : mvp_matrix_({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}),
      translation_matrix_(
          {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}),
      extremums_({0}),
      angle_x_(0),
      angle_y_(0),
      angle_z_(0),
      step_x_(0),
      step_y_(0),
      step_z_(0),
      scale_(1) {}

void MVPMatrix::RotationX() {
  double x = angle_x_ / to_radian_;
  matrix_4x4 rot_x{{1, 0, 0, 0},
                   {0, cos(x), -sin(x), 0},
                   {0, sin(x), cos(x), 0},
                   {0, 0, 0, 1}};
  MultiplyMatrix(mvp_matrix_, rot_x);
}

void MVPMatrix::RotationY() {
  double y = angle_y_ / to_radian_;
  matrix_4x4 rot_y{{cos(y), 0, sin(y), 0},
                   {0, 1, 0, 0},
                   {-sin(y), 0, cos(y), 0},
                   {0, 0, 0, 1}};
  MultiplyMatrix(mvp_matrix_, rot_y);
}

void MVPMatrix::RotationZ() {
  double z = angle_z_ / to_radian_;
  matrix_4x4 rot_z{{cos(z), -sin(z), 0, 0},
                   {sin(z), cos(z), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}};
  MultiplyMatrix(mvp_matrix_, rot_z);
}

void MVPMatrix::TranslationX() {
  matrix_4x4 transl_x{
      {1, 0, 0, step_x_}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  MultiplyMatrix(translation_matrix_, transl_x);
}

void MVPMatrix::TranslationY() {
  matrix_4x4 transl_y{
      {1, 0, 0, 0}, {0, 1, 0, step_y_}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  MultiplyMatrix(translation_matrix_, transl_y);
}

void MVPMatrix::TranslationZ() {
  matrix_4x4 transl_z{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, step_z_}, {0, 0, 0, 1}};
  MultiplyMatrix(translation_matrix_, transl_z);
}

void MVPMatrix::Scale() {
  matrix_4x4 temp = ScaleMatrix(scale_);
  MultiplyMatrix(mvp_matrix_, temp);
}

typename MVPMatrix::matrix_4x4 MVPMatrix::GetProjectionCentral() {
  matrix_4x4 projection{
      {1.0 / tan(30.0 / to_radian_), 0, 0, 0},
      {0, 1.0 / tan(30.0 / to_radian_), 0, 0},
      {0, 0, 1000.0 / (1000.0 - 0.1), -1000.0 * 0.1 / (1000.0 - 0.1)},
      {0, 0, 1, 0}};
  matrix_4x4 temp{
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, (extremums_.max_z - extremums_.min_z) * NormScale()},
      {0, 0, 0, 1}};
  MultiplyMatrix(projection, temp);
  return projection;
}

void MVPMatrix::MultiplyMatrix(matrix_4x4 &matrix1, const matrix_4x4 &matrix2) {
  matrix_4x4 temp{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        temp[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  matrix1 = temp;
}

void MVPMatrix::MultiplyNumber(matrix_4x4 &mat, const double num) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat[i][j] *= num;
    }
  }
}

void MVPMatrix::NormalizeModel() {
  matrix_4x4 temp = ScaleMatrix(NormScale());
  MultiplyMatrix(mvp_matrix_, temp);
}

void MVPMatrix::Clear() {
  mvp_matrix_.clear();
  translation_matrix_.clear();
  mvp_matrix_ = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  translation_matrix_ = {
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  extremums_ = {0};
  angle_x_ = 0;
  angle_y_ = 0;
  angle_z_ = 0;
  step_x_ = 0;
  step_y_ = 0;
  step_z_ = 0;
  scale_ = 1;
}

double MVPMatrix::NormScale() {
  double len_x = extremums_.max_x - extremums_.min_x;
  double len_y = extremums_.max_y - extremums_.min_y;
  double len_z = extremums_.max_z - extremums_.min_z;
  double result = fmax(len_x, fmax(len_y, len_z));
  return 1 / result;
}

typename MVPMatrix::matrix_4x4 MVPMatrix::ScaleMatrix(double scale) {
  matrix_4x4 temp{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  MultiplyNumber(temp, scale);
  temp[3][3] = 1;
  return temp;
}
}  // namespace view3d
