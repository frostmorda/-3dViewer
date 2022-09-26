#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QRegularExpression>

namespace view3d {
class Settings {
 public:
  Settings();

  void SaveSettings();
  QList<QString> ReadSettings();
  void SetSettings();

  void SetProjectionType(const QString &projection_type) {
    projection_type_ = projection_type;
  }
  void SetBackgroundColor(const QColor &background_color) {
    background_color_ = background_color;
  }
  void SetEdgeType(const QString &edge_type) { edge_type_ = edge_type; }
  void SetEdgeThickness(const int edge_thickness) {
    edge_thickness_ = edge_thickness;
  }
  void SetEdgeColor(const QColor &edge_color) { edge_color_ = edge_color; }
  void SetVerticeType(const QString &vertice_type) {
    vertice_type_ = vertice_type;
  }
  void SetVerticeSize(const int vertice_size) { vertice_size_ = vertice_size; }
  void SetVerticeColor(const QColor &vertice_color) {
    vertice_color_ = vertice_color;
  }
  void DefaultSettings();

  QString &GetProjectionType() { return projection_type_; }
  QColor &GetBackgroundColor() { return background_color_; }
  QString &GetEdgeType() { return edge_type_; }
  int GetEdgeThickness() { return edge_thickness_; }
  QColor &GetEdgeColor() { return edge_color_; }
  QString &GetVerticeType() { return vertice_type_; }
  int GetVerticeSize() { return vertice_size_; }
  QColor &GetVerticeColor() { return vertice_color_; }

 private:
  QString projection_type_;
  QColor background_color_;
  QString edge_type_;
  int edge_thickness_;
  QColor edge_color_;
  QString vertice_type_;
  int vertice_size_;
  QColor vertice_color_;
};
}  // namespace view3d

#endif  // SETTINGS_H
