#include <QApplication>

#include "view/mainwindow.h"
#include "view/myopenglwidget.h"


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  view3d::Model model;
  view3d::Controller controller(&model);
  view3d::MainWindow mw(&controller);
  mw.setWindowTitle("view3diewer_v2.0");
  mw.show();
  return app.exec();

}
