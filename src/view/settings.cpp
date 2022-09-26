#include "settings.h"

#include <QApplication>

namespace view3d {
Settings::Settings() {}

void Settings::SaveSettings() {
  QString path = qApp->applicationDirPath() + "/settings.ini";
  QFile settings_file(path);
  if (settings_file.open(QIODevice::ReadWrite | QIODevice::Text |
                         QFile::Truncate)) {
    QTextStream writeSettings;
    writeSettings.setDevice(&settings_file);
    writeSettings << projection_type_ << "\n";
    writeSettings << background_color_.name(QColor::HexArgb) << "\n";
    writeSettings << edge_type_ << "\n";
    writeSettings << edge_thickness_ << "\n";
    writeSettings << edge_color_.name(QColor::HexArgb) << "\n";
    writeSettings << vertice_type_ << "\n";
    writeSettings << vertice_size_ << "\n";
    writeSettings << vertice_color_.name(QColor::HexArgb) << "\n";
    settings_file.close();
  }
}

QList<QString> Settings::ReadSettings() {
  QList<QString> list = {};
  QString path = qApp->applicationDirPath() + "/settings.ini";
  QFile settings_file(path);
  if (settings_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    while (!settings_file.atEnd()) {
      QString str = settings_file.readLine();
      QStringList lst = str.split("\n");
      list << lst.at(0);
    }
  } else {
    DefaultSettings();
  }
  settings_file.close();
  return list;
}

void Settings::SetSettings() {
  QList<QString> settings_list = ReadSettings();
  projection_type_ = settings_list.at(0);
  background_color_ = settings_list.at(1);
  edge_type_ = settings_list.at(2);
  edge_thickness_ = settings_list.at(3).toInt();
  edge_color_ = settings_list.at(4);
  vertice_type_ = settings_list.at(5);
  vertice_size_ = settings_list.at(6).toInt();
  vertice_color_ = settings_list.at(7);
}

void Settings::DefaultSettings() {
  QString path = qApp->applicationDirPath() + "/settings.ini";
  QFile settings_file(path);
  if (settings_file.open(QIODevice::ReadWrite | QIODevice::Text |
                         QFile::Truncate)) {
    QTextStream writeSettings;
    writeSettings.setDevice(&settings_file);
    writeSettings << "PARALLEL"
                  << "\n";
    writeSettings << "#ffffffff"
                  << "\n";
    writeSettings << "SOLID"
                  << "\n";
    writeSettings << 1 << "\n";
    writeSettings << "#00000000"
                  << "\n";
    writeSettings << "NONE"
                  << "\n";
    writeSettings << 1 << "\n";
    writeSettings << "#ff00ffff"
                  << "\n";
    settings_file.close();
  }
}
}  //  namespace view3d
