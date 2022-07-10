#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

extern "C" {
#include "parsSavedSettings.h"
}

namespace s21 {
void Shadow(int blurSize, int offsetx, int offsety, QObject* parent);
void Color(QWidget* sender, QString color, QString prop);
}  // namespace s21

namespace Ui {
class Settings;
}

class Settings : public QDialog {
  Q_OBJECT

 public:
  explicit Settings(QWidget* parent = nullptr,
                    saveSettings* settings = nullptr);
  ~Settings();  //

 public slots:
  void applyOldSettings();

 signals:
  void updateSettings();

 private slots:
  void on_edgesColor_clicked();
  void on_backgroundColor_clicked();
  void on_verticesColor_clicked();

  void parallelRadio_clicked();
  void centrallRadio_clicked();

  void solidRadio_clicked();
  void dashedRadio_clicked();

  void noneRadio_clicked();
  void circleRadio_clicked();
  void squareRadio_clicked();
  void on_saveButton_clicked();

 private:
  Ui::Settings* ui;
  saveSettings* sett;
  QColor edgesColor;
  QColor verticesColor;
  QColor backgroundColor;
  int thickness, verticesSize, edgesMethod, vertType;
  FILE* settFile = NULL;
};

#endif  // SETTINGS_H
