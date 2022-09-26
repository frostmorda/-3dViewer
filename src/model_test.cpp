#include "./model/model.h"

#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>

TEST(model, bad_file_name) {
  std::string bad_filename = "obj/cubeek.obj";
  view3d::Model object;
  ASSERT_FALSE(object.MakeObject(bad_filename));
}

TEST(model, read_file_and_add_data_1) {
  std::string filename = "obj/cube.obj";
  view3d::Model object;
  ASSERT_TRUE(object.MakeObject(filename));
  ASSERT_FLOAT_EQ(object.GetMatrixValueAt(1, 1), -1.0);
}

TEST(model, read_file_and_add_data_2) {
  std::string filename = "obj/cube_test.obj";
  view3d::Model object;
  ASSERT_TRUE(object.MakeObject(filename));
  ASSERT_FLOAT_EQ(object.GetMatrixValueAt(1, 1), -22.0);
}

TEST(model, read_file_and_add_data_3) {
  std::string filename = "obj/empty.obj";
  view3d::Model object;
  ASSERT_FALSE(object.MakeObject(filename));
}

TEST(model, reset_model) {
  view3d::Model object;
  object.ResetModel();
  ASSERT_EQ(object.GetPolygon().GetVertices().size(), 0);
}

TEST(model, transform_polygon) {
  std::string filename = "obj/cube.obj";
  view3d::Model object;
  object.MakeObject(filename);
  ASSERT_FLOAT_EQ(object.GetVerticeValueAt(0), 1.0);
}

TEST(MVPMatrix, rotation_x) {
  view3d::MVPMatrix mat;
  mat.SetAngleX(30);
  mat.RotationX();
  ASSERT_NEAR(mat.GetMVPMatrix()[1][1], cos(30 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[2][2], cos(30 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[1][2], -sin(30 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[2][1], sin(30 / 57.2958), 1e-6);
}

TEST(MVPMatrix, rotation_y) {
  view3d::MVPMatrix mat;
  mat.SetAngleY(60);
  mat.RotationY();
  ASSERT_NEAR(mat.GetMVPMatrix()[0][0], cos(60 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[2][2], cos(60 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[0][2], sin(60 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[2][0], -sin(60 / 57.2958), 1e-6);
}

TEST(MVPMatrix, rotation_z) {
  view3d::MVPMatrix mat;
  mat.SetAngleZ(90);
  mat.RotationZ();
  ASSERT_NEAR(mat.GetMVPMatrix()[0][0], cos(90 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[0][0], cos(90 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[0][1], -sin(90 / 57.2958), 1e-6);
  ASSERT_NEAR(mat.GetMVPMatrix()[1][0], sin(90 / 57.2958), 1e-6);
}

TEST(MVPMatrix, translation_x) {
  view3d::MVPMatrix mat;
  double val = 3.45;
  mat.SetTranslationX(val);
  mat.TranslationX();
  auto x = mat.GetTranslationMatrix()[0][3];
  ASSERT_NEAR(x - val, 0, 1e-6);
}

TEST(MVPMatrix, translation_y) {
  view3d::MVPMatrix mat;
  double val = 32.2;
  mat.SetTranslationY(val);
  mat.TranslationY();
  ASSERT_NEAR(mat.GetTranslationMatrix()[1][3] - val, 0, 1e-6);
}

TEST(MVPMatrix, translation_z) {
  view3d::MVPMatrix mat;
  double val = -22.25;
  mat.SetTranslationZ(val);
  mat.TranslationZ();
  ASSERT_NEAR(mat.GetTranslationMatrix()[2][3] - val, 0, 1e-6);
}

TEST(MVPMatrix, scale) {
  view3d::MVPMatrix mat;
  mat.SetScale(5.5);
  mat.Scale();
  for (int i = 0; i < 3; i++) {
    ASSERT_NEAR(mat.GetMVPMatrix()[i][i], 5.5, 1e-6);
  }
  ASSERT_NEAR(mat.GetMVPMatrix()[3][3], 1, 1e-6);
}

TEST(MVPMatrix, get_projection_central) {
  view3d::MVPMatrix mat;
  mat.GetProjectionCentral();
  ASSERT_NEAR(mat.GetMVPMatrix()[1][1], 1, 1e-6);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
