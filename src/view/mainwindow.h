#ifndef SRC_VIEW_MAINWINDOW_H_
#define SRC_VIEW_MAINWINDOW_H_

#define GL_SILENCE_DEPRECATION

#include <QCloseEvent>
#include <QFileDialog>
#include <QImage>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>

#include "../controller/controller.h"
#include "../misc.h"
#include "myopenglwidget.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace view3d {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  explicit MainWindow(view3d::Controller *controller);
  ~MainWindow();

 protected:
  void wheelEvent(QWheelEvent *event) override;

 private:
  view3d::Controller *controller_;
  Ui::MainWindow *ui;
  QString filepath_;
  QString filename_;
  view3d::Settings *settings_;
  LastStand last_stand_;
  const int min_scale_ = 1;

 signals:
  void Clicked();

 private slots:
  void on_pushButton_open_clicked();

  void on_comboBox_projectionType_currentTextChanged(
      const QString &projectionType);
  void on_pushButton_backgroundColor_clicked();

  void on_comboBox_edgeType_currentTextChanged(const QString &edgeType);
  void on_spinBox_edgeThickness_valueChanged(int edgeThickness);
  void on_pushButton_edgeColor_clicked();

  void on_comboBox_verticeType_currentTextChanged(const QString &verticeType);
  void on_spinBox_verticeSize_valueChanged(int verticeSize);
  void on_pushBotton_verticeColor_clicked();

  void SetProjectionValue();
  void SetEdgeValue();
  void SetVerticeValue();
  void SetButtons();
  void closeEvent(QCloseEvent *event) override;

  void on_horizontalScrollBar_xRotate_valueChanged(int value);
  void on_horizontalScrollBar_yRotate_valueChanged(int value);
  void on_horizontalScrollBar_zRotate_valueChanged(int value);
  void on_horizontalScrollBar_xTranslate_valueChanged(int value);
  void on_horizontalScrollBar_yTranslate_valueChanged(int value);
  void on_horizontalScrollBar_zTranslate_valueChanged(int value);
  void on_scale_slider_valueChanged(int value);
  void on_pushButton_resetPosition_clicked();
  void ResetScrollBarValue();
  void on_pushButton_saveImage_clicked();
  void on_pushButton_makeGIF_clicked();
  void on_spinBox_xRotate_valueChanged(int value);
  void on_spinBox_yRotate_valueChanged(int value);
  void on_spinBox_zRotate_valueChanged(int value);
  void on_spinBox_xTranslate_valueChanged(int value);
  void on_spinBox_yTranslate_valueChanged(int value);
  void on_spinBox_zTranslate_valueChanged(int value);
  void on_pushButton_resetSettings_clicked();
  void on_pushButton_clean_clicked();
  void ResetMainWindow();
};
}  //  namespace view3d
#endif  // SRC_VIEW_MAINWINDOW_H_
