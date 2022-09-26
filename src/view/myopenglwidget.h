#ifndef SRC_VIEW_MYOPENGLWIDGET_H_
#define SRC_VIEW_MYOPENGLWIDGET_H_
#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <memory>

#include "../controller/controller.h"
#include "../gif_src/gifimage/qgifimage.h"
#include "../misc.h"
#include "settings.h"

namespace view3d {
class MainWindow;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  using matrix_4x4 = std::vector<std::vector<double>>;
  explicit MyOpenGLWidget(QWidget *parent = nullptr);
  void SetSettings(Settings *settings);
  void SetController(view3d::Controller *ctr) { controller_ = ctr; }
  void MakeScreenShot();
  void Recording() { is_recording_ = true; }

 signals:
  void Recorded();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  view3d::Controller *controller_ = nullptr;
  Settings *settings_;
  QOpenGLShaderProgram *shader_program_ = nullptr;
  QString filepath_ = nullptr;
  QMatrix4x4 AdapterMatrix(const matrix_4x4 &other_matrix);

  GLint vertex_atrib_ = {0};
  GLint color_uniform_ = {0};
  GLint matrix_uniform_ = {0};
  GLint projection_uniform_ = {0};
  GLint koef_uniform_ = {0};
  GLint translation_uniform_ = {0};

  QGifImage *gif_ = {nullptr};
  int gif_frame_count_ = {0};
  bool is_recording_ = {false};

  void DrawLines();
  void DrawDots();
  void SetUniform(const QColor &color);
  void MakeGif();
};
}  //  namespace view3d
#endif  // SRC_VIEW_MYOPENGLWIDGET_H_
