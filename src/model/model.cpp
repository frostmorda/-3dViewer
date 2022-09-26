#include "model.h"

namespace view3d {
bool Model::MakeObject(const std::string &filename) {
  Clear();
  std::ifstream read_file;
  read_file.open(filename);
  if (read_file.is_open()) {
    ParseFile(&read_file);
    if (!matrix_points_.matrix_.empty()) {
      FindExtremums();
      SetExtremums();
      mvp_matrix_.NormalizeModel();
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void Model::ResetModel() {
  matrix_points_.matrix_.clear();
  polygons_.vertices_united_.clear();
}

void Model::ParseFile(std::ifstream *read_file) {
  std::string temp_string;
  std::vector<std::vector<int>> polygons_vector;
  while (getline(*read_file, temp_string)) {
    if ((temp_string[0] == 'v' && temp_string[1] == ' ') ||
        (temp_string[0] == 'f')) {
      std::istringstream stream(temp_string);
      std::string token;
      if (temp_string[0] == 'v') {
        matrix_points_.rows_++;
        matrix_points_.columns_ = 3;
        std::vector<double> temp;
        while (getline(stream, token, ' ')) {
          if (token != "v" && token != "") {
            temp.push_back(std::stof(token));
          }
        }
        matrix_points_.matrix_.push_back(temp);
        count_of_vertices_++;
      } else if (temp_string[0] == 'f') {
        std::vector<int> temp;
        while (getline(stream, token, ' ')) {
          if (token != "f" && token != "" && token != "\r") {
            temp.push_back(stoi(token));
          }
        }
        polygons_vector.push_back(temp);
        count_of_facets_++;
      }
    }
  }
  UnitePolygons(polygons_vector);
}

void Model::FindExtremums() {
  FindXExtremums();
  FindYExtremums();
  FindZExtremums();
}

void Model::FindXExtremums() {
  extremums_.min_x = matrix_points_.matrix_.at(0).at(0);
  extremums_.max_x = matrix_points_.matrix_.at(0).at(0);
  for (size_t row = 1; row < matrix_points_.rows_; row++) {
    if (matrix_points_.matrix_.at(row).at(0) >= extremums_.max_x) {
      extremums_.max_x = matrix_points_.matrix_.at(row).at(0);
    } else if (matrix_points_.matrix_.at(row).at(0) <= extremums_.min_x) {
      extremums_.min_x = matrix_points_.matrix_.at(row).at(0);
    }
  }
}

void Model::FindYExtremums() {
  extremums_.min_y = matrix_points_.matrix_.at(0).at(1);
  extremums_.max_y = matrix_points_.matrix_.at(0).at(1);
  for (size_t row = 1; row < matrix_points_.rows_; row++) {
    if (matrix_points_.matrix_.at(row).at(1) >= extremums_.max_y) {
      extremums_.max_y = matrix_points_.matrix_.at(row).at(1);
    } else if (matrix_points_.matrix_.at(row).at(1) <= extremums_.min_y) {
      extremums_.min_y = matrix_points_.matrix_.at(row).at(1);
    }
  }
}

void Model::FindZExtremums() {
  extremums_.min_z = matrix_points_.matrix_.at(0).at(2);
  extremums_.max_z = matrix_points_.matrix_.at(0).at(2);
  for (size_t row = 1; row < matrix_points_.rows_; row++) {
    if (matrix_points_.matrix_.at(row).at(2) >= extremums_.max_z) {
      extremums_.max_z = matrix_points_.matrix_.at(row).at(2);
    } else if (matrix_points_.matrix_.at(row).at(2) <= extremums_.min_z) {
      extremums_.min_z = matrix_points_.matrix_.at(row).at(2);
    }
  }
}

void Model::UnitePolygons(
    const std::vector<std::vector<int>> &polygons_vector) {
  std::vector<int> polygons_united;
  for (size_t row = 0; row < polygons_vector.size(); row++) {
    for (size_t column = 0; column < polygons_vector.at(row).size(); column++) {
      polygons_united.push_back(polygons_vector.at(row).at(column));
      if (column != 0) {
        polygons_united.push_back(polygons_vector.at(row).at(column));
      }
    }
    polygons_united.push_back(polygons_vector.at(row).at(0));
  }
  TransformFacetsToVertices(polygons_united);
}

void Model::TransformFacetsToVertices(const std::vector<int> &polygons_united) {
  for (size_t i = 0; i < polygons_united.size(); i++) {
    for (size_t j = 0; j < matrix_points_.columns_; j++) {
      polygons_.vertices_united_.push_back(
          matrix_points_.matrix_.at(polygons_united.at(i) - 1).at(j));
    }
  }
}

void Model::Clear() {
  polygons_.vertices_united_.clear();
  matrix_points_.matrix_.clear();
  matrix_points_.columns_ = 0;
  matrix_points_.rows_ = 0;
  mvp_matrix_.Clear();
  extremums_ = {0};
  count_of_facets_ = 0;
  count_of_vertices_ = 0;
}
}  // namespace view3d
