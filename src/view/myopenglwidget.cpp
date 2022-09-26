#include "myopenglwidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include "myopenglwidget.h"

namespace view3d {

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  settings_->ReadSettings();
}

void MyOpenGLWidget::SetSettings(Settings *settings) { settings_ = settings; }

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  shader_program_ = new QOpenGLShaderProgram(this);
  shader_program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vert");
  shader_program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/frag");
  shader_program_->link();
  vertex_atrib_ = shader_program_->attributeLocation("vertexPos");
  Q_ASSERT(vertex_atrib_ != -1);
  color_uniform_ = shader_program_->uniformLocation("color");
  Q_ASSERT(color_uniform_ != -1);
  matrix_uniform_ = shader_program_->uniformLocation("mvpMatrix");
  Q_ASSERT(matrix_uniform_ != -1);
  projection_uniform_ = shader_program_->uniformLocation("projectionMatrix");
  Q_ASSERT(projection_uniform_ != -1);
  koef_uniform_ = shader_program_->uniformLocation("koef");
  Q_ASSERT(koef_uniform_ != -1);
  translation_uniform_ = shader_program_->uniformLocation("transMatrix");
  Q_ASSERT(translation_uniform_ != -1);
}

void MyOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyOpenGLWidget::paintGL() {
  glClearColor(settings_->GetBackgroundColor().redF(),
               settings_->GetBackgroundColor().greenF(),
               settings_->GetBackgroundColor().blueF(),
               settings_->GetBackgroundColor().alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawLines();
  if (settings_->GetVerticeType() != "NONE") {
    DrawDots();
  }
  MakeGif();
}

QMatrix4x4 MyOpenGLWidget::AdapterMatrix(const matrix_4x4 &other_matrix) {
  QMatrix4x4 matrix;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix(i, j) = other_matrix[i][j];
    }
  }
  return matrix;
}

void MyOpenGLWidget::DrawLines() {
  SetUniform(settings_->GetEdgeColor());
  glEnable(GL_LINE_WIDTH);
  glLineWidth(settings_->GetEdgeThickness());
  if (settings_->GetEdgeType() == "DASHED") {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0x0f0f);
  } else if (settings_->GetEdgeType() == "SOLID") {
    glDisable(GL_LINE_STIPPLE);
  }
  glDrawArrays(GL_LINES, 0, controller_->GetVertices().size() / 3);
  glDisableVertexAttribArray(vertex_atrib_);
  shader_program_->release();
}

void MyOpenGLWidget::DrawDots() {
  SetUniform(settings_->GetVerticeColor());
  glEnable(GL_POINT_SIZE);
  if (settings_->GetVerticeType() == "CIRCLE") {
    glEnable(GL_POINT_SMOOTH);
  } else if (settings_->GetVerticeType() == "SQUARE") {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(settings_->GetVerticeSize());
  glDrawArrays(GL_POINTS, 0, controller_->GetVertices().size() / 3);
  glDisableVertexAttribArray(vertex_atrib_);
  shader_program_->release();
}

void MyOpenGLWidget::SetUniform(const QColor &color) {
  shader_program_->bind();
  QMatrix4x4 mvp = AdapterMatrix(controller_->GetMVPMatrix());
  QMatrix4x4 projection = AdapterMatrix(controller_->GetCentralProjection());
  QMatrix4x4 translation = AdapterMatrix(controller_->GetTranslationMatrix());
  if (settings_->GetProjectionType() == "PARALLEL") {
    projection.setToIdentity();
  }
  float koef_screen = 3. / 4.;
  shader_program_->setUniformValue(color_uniform_, color);
  shader_program_->setUniformValue(matrix_uniform_, mvp);
  shader_program_->setUniformValue(projection_uniform_, projection);
  shader_program_->setUniformValue(koef_uniform_, koef_screen);
  shader_program_->setUniformValue(translation_uniform_, translation);
  glVertexAttribPointer(vertex_atrib_, 3, GL_FLOAT, GL_FALSE, 0,
                        controller_->GetVertices().data());
  glEnableVertexAttribArray(vertex_atrib_);
}

void MyOpenGLWidget::MakeScreenShot() {
  QImage screen = grabFramebuffer();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath() + "/screenshoot.jpg",
      tr("JPEG (*.jpg *.jpeg);;BMP (*.bmp)"));
  if (fileName.length()) screen.save(fileName);
}

void MyOpenGLWidget::MakeGif() {
  if (is_recording_) {
    if (gif_ == nullptr) {
      gif_ = new QGifImage(QSize(640, 480));
    }
    if (gif_frame_count_ < 50) {
      QImage screen = this->grabFramebuffer();
      gif_->addFrame(screen);
      gif_frame_count_++;
    } else {
      is_recording_ = false;
      gif_->setDefaultDelay(100);
      QString fileName = QFileDialog::getSaveFileName(
          this, tr("Save File"), QDir::homePath() + "/animation.gif",
          tr("Gif (*.gif)"));
      if (fileName.length()) gif_->save(fileName);
      delete gif_;
      gif_ = nullptr;
      gif_frame_count_ = 0;
      emit Recorded();
    }
  }
}
}  //  namespace view3d
