#include "mainwindow.h"

#include "ui_mainwindow.h"
namespace view3d {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (ui->comboBox_verticeType->currentText() == "отсутствует") {
    ui->pushBotton_verticeColor->setDisabled(true);
    ui->spinBox_verticeSize->setDisabled(true);
  }

  settings_ = new Settings;
  filepath_ = NULL;
  filename_ = NULL;

  settings_->SetSettings();
  SetButtons();
  connect(ui->glWidget, &MyOpenGLWidget::Recorded, this, [this]() {
    ui->pushButton_makeGIF->setText("Записать GIF");
    ui->pushButton_makeGIF->setEnabled(true);
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_clean->setEnabled(true);
    ui->pushButton_saveImage->setEnabled(true);
  });
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

MainWindow::MainWindow(view3d::Controller *controller) : MainWindow() {
  controller_ = controller;
  ui->glWidget->SetController(controller_);
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings_;
}

void MainWindow::on_pushButton_open_clicked() {
  controller_->BackupModel();
  controller_->BackupState();
  controller_->SaveBackupState();
  filepath_ = QFileDialog::getOpenFileName(0, "", QDir::homePath(), "*.obj");
  filename_ =
      filepath_.right(filepath_.length() - filepath_.lastIndexOf("/") - 1);
  if (!filename_.isEmpty() && !filename_.isNull()) {
    if (controller_->MakeObject(filepath_.toStdString())) {
      controller_->SaveState();
      ResetScrollBarValue();
      controller_->RestoreState();
      ui->lineEdit_filename->setText(filename_);
      ui->label_verticesValue->setText(
          QString::number(controller_->GetCountOfVertices()));
      ui->label_edgesValue->setText(
          QString::number(controller_->GetCountOfFacets()));
      controller_->SaveState();
    } else {
      controller_->RestoreBackupModele();
      controller_->RestoreBackupState();
      QMessageBox msgBox;
      msgBox.setText("Ошибка файла!\t");
      msgBox.exec();
    }
  }
}

void MainWindow::on_comboBox_projectionType_currentTextChanged(
    const QString &projectionType) {
  if (projectionType == "центральная") {
    settings_->SetProjectionType("CENTRAL");
  } else {
    settings_->SetProjectionType("PARALLEL");
  }
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_pushButton_backgroundColor_clicked() {
  QColor background_color = QColorDialog::getColor(Qt::white, this);
  if (background_color.isValid()) {
    settings_->SetBackgroundColor(background_color);
    ui->glWidget->SetSettings(settings_);
    ui->glWidget->update();
  }
}

void MainWindow::on_comboBox_edgeType_currentTextChanged(
    const QString &edgeType) {
  if (edgeType == "сплошная") {
    settings_->SetEdgeType("SOLID");
  } else {
    settings_->SetEdgeType("DASHED");
  }
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_spinBox_edgeThickness_valueChanged(int edgeThickness) {
  settings_->SetEdgeThickness(edgeThickness);
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_pushButton_edgeColor_clicked() {
  QColor edges_color = QColorDialog::getColor(Qt::white, this);
  settings_->SetEdgeColor(edges_color);
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_comboBox_verticeType_currentTextChanged(
    const QString &verticeType) {
  if (verticeType != "отсутствует") {
    ui->pushBotton_verticeColor->setEnabled(true);
    ui->spinBox_verticeSize->setEnabled(true);
    if (verticeType == "круг") {
      settings_->SetVerticeType("CIRCLE");
    } else {
      settings_->SetVerticeType("SQUARE");
    }
  } else {
    ui->pushBotton_verticeColor->setDisabled(true);
    ui->spinBox_verticeSize->setDisabled(true);
    settings_->SetVerticeType("NONE");
  }
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_spinBox_verticeSize_valueChanged(int verticeSize) {
  settings_->SetVerticeSize(verticeSize);
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::on_pushBotton_verticeColor_clicked() {
  QColor vertices_color = QColorDialog::getColor(Qt::white, this);
  if (vertices_color.isValid()) {
    settings_->SetVerticeColor(vertices_color);
  }
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
}

void MainWindow::SetProjectionValue() {
  if (settings_->GetProjectionType() == "PARALLEL") {
    ui->comboBox_projectionType->setCurrentText("параллельная");
  } else {
    ui->comboBox_projectionType->setCurrentText("центральная");
  }
}

void MainWindow::SetEdgeValue() {
  if (settings_->GetEdgeType() == "SOLID") {
    ui->comboBox_edgeType->setCurrentText("сплошная");
  } else {
    ui->comboBox_edgeType->setCurrentText("пунктирная");
  }
  ui->spinBox_edgeThickness->setValue(settings_->GetEdgeThickness());
}

void MainWindow::SetVerticeValue() {
  if (settings_->GetVerticeType() == "NONE") {
    ui->comboBox_verticeType->setCurrentText("отсутствует");
  } else if (settings_->GetVerticeType() == "CIRCLE") {
    ui->comboBox_verticeType->setCurrentText("круг");
  } else {
    ui->comboBox_verticeType->setCurrentText("квадрат");
  }
  ui->spinBox_verticeSize->setValue(settings_->GetVerticeSize());
}

void MainWindow::SetButtons() {
  SetProjectionValue();
  SetEdgeValue();
  SetVerticeValue();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  settings_->SaveSettings();
  event->accept();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  int scale = ui->scale_slider->value();
  scale += event->pixelDelta().ry();
  if (scale < 1) {
    scale = min_scale_;
  }
  ui->scale_slider->setValue(scale);
}

void MainWindow::on_horizontalScrollBar_xRotate_valueChanged(int value) {
  ui->spinBox_xRotate->setValue(value);
  double temp = value;
  value -= last_stand_.x_angle;
  controller_->RotationX(value);
  last_stand_.x_angle = temp;
  ui->glWidget->update();
}

void MainWindow::on_horizontalScrollBar_yRotate_valueChanged(int value) {
  ui->spinBox_yRotate->setValue(value);
  double temp = value;
  value -= last_stand_.y_angle;
  controller_->RotationY(value);
  last_stand_.y_angle = temp;
  ui->glWidget->update();
}

void MainWindow::on_horizontalScrollBar_zRotate_valueChanged(int value) {
  ui->spinBox_zRotate->setValue(value);
  double temp = value;
  value -= last_stand_.z_angle;
  controller_->RotationZ(value);
  last_stand_.z_angle = temp;
  ui->glWidget->update();
}

void MainWindow::on_horizontalScrollBar_xTranslate_valueChanged(int value) {
  ui->spinBox_xTranslate->setValue(value);
  double temp = value;
  value -= last_stand_.x_step;
  controller_->TranslationX(value / 100.0);
  last_stand_.x_step = temp;
  ui->glWidget->update();
}

void MainWindow::on_horizontalScrollBar_yTranslate_valueChanged(int value) {
  ui->spinBox_yTranslate->setValue(value);
  double temp = value;
  value -= last_stand_.y_step;
  controller_->TranslationY(value / 100.0);
  last_stand_.y_step = temp;
  ui->glWidget->update();
}

void MainWindow::on_horizontalScrollBar_zTranslate_valueChanged(int value) {
  ui->spinBox_zTranslate->setValue(value);
  double temp = value;
  value -= last_stand_.z_step;
  controller_->TranslationZ(value / 100.0);
  last_stand_.z_step = temp;
  ui->glWidget->update();
}

void MainWindow::on_scale_slider_valueChanged(int value) {
  double temp = value;
  temp /= last_stand_.scale;
  controller_->Scale(temp);
  last_stand_.scale = value;
  ui->glWidget->update();
}

void MainWindow::on_pushButton_resetPosition_clicked() {
  ResetScrollBarValue();
  controller_->RestoreState();
  ui->glWidget->update();
}

void MainWindow::ResetScrollBarValue() {
  ui->horizontalScrollBar_xRotate->setValue(0);
  ui->horizontalScrollBar_yRotate->setValue(0);
  ui->horizontalScrollBar_zRotate->setValue(0);
  ui->horizontalScrollBar_xTranslate->setValue(0);
  ui->horizontalScrollBar_yTranslate->setValue(0);
  ui->horizontalScrollBar_zTranslate->setValue(0);
  ui->scale_slider->setValue(100);
}

void MainWindow::on_pushButton_saveImage_clicked() {
  ui->glWidget->MakeScreenShot();
}

void MainWindow::on_pushButton_makeGIF_clicked() {
  if (!controller_->GetVertices().empty()) {
    ui->pushButton_makeGIF->setText("🔴 Recording...");
    ui->pushButton_makeGIF->setDisabled(true);
    ui->pushButton_open->setDisabled(true);
    ui->pushButton_clean->setDisabled(true);
    ui->pushButton_saveImage->setDisabled(true);
    ui->glWidget->Recording();
  }
}

void MainWindow::on_spinBox_xRotate_valueChanged(int value) {
  ui->horizontalScrollBar_xRotate->setValue(value);
}

void MainWindow::on_spinBox_yRotate_valueChanged(int value) {
  ui->horizontalScrollBar_yRotate->setValue(value);
}

void MainWindow::on_spinBox_zRotate_valueChanged(int value) {
  ui->horizontalScrollBar_zRotate->setValue(value);
}

void MainWindow::on_spinBox_xTranslate_valueChanged(int value) {
  ui->horizontalScrollBar_xTranslate->setValue(value);
}

void MainWindow::on_spinBox_yTranslate_valueChanged(int value) {
  ui->horizontalScrollBar_yTranslate->setValue(value);
}

void MainWindow::on_spinBox_zTranslate_valueChanged(int value) {
  ui->horizontalScrollBar_zTranslate->setValue(value);
}

void MainWindow::on_pushButton_resetSettings_clicked() {
  settings_->DefaultSettings();
  settings_->SetSettings();
  ui->glWidget->SetSettings(settings_);
  ui->glWidget->update();
  SetButtons();
}

void MainWindow::on_pushButton_clean_clicked() { ResetMainWindow(); }

void MainWindow::ResetMainWindow() {
  ui->lineEdit_filename->clear();
  ui->label_verticesValue->clear();
  ui->label_edgesValue->clear();
  controller_->ResetModel();
  ui->glWidget->update();
}
}  //  namespace view3d
