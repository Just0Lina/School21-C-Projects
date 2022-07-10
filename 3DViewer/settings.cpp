#include "settings.h"

#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QStringList>

#include "ui_settings.h"

Settings::Settings(QWidget* parent, saveSettings* settings)
    : QDialog(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  sett = settings;
  connect(ui->parallelRadio, &QRadioButton::clicked, this,
          &Settings::parallelRadio_clicked);
  connect(ui->centralRadio, &QRadioButton::clicked, this,
          &Settings::centrallRadio_clicked);
  connect(ui->solidRadio, &QRadioButton::clicked, this,
          &Settings::solidRadio_clicked);
  connect(ui->dashedRadio, &QRadioButton::clicked, this,
          &Settings::dashedRadio_clicked);
  connect(ui->noneRadio, &QRadioButton::clicked, this,
          &Settings::noneRadio_clicked);
  connect(ui->circleRadio, &QRadioButton::clicked, this,
          &Settings::circleRadio_clicked);
  connect(ui->squareRadio, &QRadioButton::clicked, this,
          &Settings::squareRadio_clicked);
  ui->thickness->setSuffix("  px");
  ui->verticesSize->setSuffix("  px");
  s21::Shadow(70, 0, 10, ui->saveButton);
}

Settings::~Settings() { delete ui; }

void Settings::applyOldSettings() {
  this->edgesColor =
      QColor(this->sett->colorEdges.red, this->sett->colorEdges.green,
             this->sett->colorEdges.blue);
  this->backgroundColor =
      QColor(this->sett->colorBack.red, this->sett->colorBack.green,
             this->sett->colorBack.blue);
  this->verticesColor =
      QColor(this->sett->colorVert.red, this->sett->colorVert.green,
             this->sett->colorVert.blue);
  s21::Color(ui->backgroundColor, this->backgroundColor.name(),
             "background-color: ");
  s21::Color(ui->verticesColor, this->verticesColor.name(),
             "background-color: ");
  s21::Color(ui->edgesColor, this->edgesColor.name(), "background-color: ");
  if (!this->sett->projection)
    ui->centralRadio->setChecked(true);
  else
    ui->parallelRadio->setChecked(true);
  if (this->sett->edgesMethod)
    ui->dashedRadio->setChecked(true);
  else
    ui->solidRadio->setChecked(true);
  if (!this->sett->vertType)
    ui->noneRadio->setChecked(true);
  else if (this->sett->vertType == 1)
    ui->circleRadio->setChecked(true);
  else
    ui->squareRadio->setChecked(true);
  ui->verticesSize->setValue(this->sett->sizeVert);
  ui->thickness->setValue(this->sett->edgesThickness);
}

void Settings::parallelRadio_clicked() { this->sett->projection = 0; }

void Settings::centrallRadio_clicked() { this->sett->projection = 1; }

void Settings::solidRadio_clicked() { this->sett->edgesMethod = 0; }

void Settings::dashedRadio_clicked() { this->sett->edgesMethod = 1; }

void Settings::noneRadio_clicked() { this->sett->vertType = 0; }

void Settings::circleRadio_clicked() { this->sett->vertType = 1; }

void Settings::squareRadio_clicked() { this->sett->vertType = 2; }

void s21::Shadow(int blurSize, int offsetx, int offsety, QObject* parent) {
  QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(parent);
  shadow->setBlurRadius(blurSize);
  shadow->setOffset(offsetx, offsety);
  qobject_cast<QWidget*>(parent)->setGraphicsEffect(shadow);
}

void s21::Color(QWidget* sender, QString color, QString prop) {
  QString style = sender->styleSheet();
  int count = 0;
  while (count != 2) {
    if (style[style.length() - 1] == ';') count++;
    if (count == 2) break;
    style.chop(1);
  }
  sender->setStyleSheet(style + prop + color + ";}");
}

void Settings::on_edgesColor_clicked() {
  this->edgesColor = QColorDialog::getColor();
  s21::Color(ui->edgesColor, this->edgesColor.name(), "background-color: ");
}

void Settings::on_backgroundColor_clicked() {
  this->backgroundColor = QColorDialog::getColor();
  s21::Color(ui->backgroundColor, this->backgroundColor.name(),
             "background-color: ");
}

void Settings::on_verticesColor_clicked() {
  this->verticesColor = QColorDialog::getColor();
  s21::Color(ui->verticesColor, this->verticesColor.name(),
             "background-color: ");
}

void Settings::on_saveButton_clicked() {
  if (ui->centralRadio->isChecked())
    this->sett->projection = 0;
  else
    this->sett->projection = 1;
  if (ui->noneRadio->isChecked())
    this->sett->vertType = 0;
  else if (ui->circleRadio->isChecked())
    this->sett->vertType = 1;
  else
    this->sett->vertType = 2;
  if (ui->solidRadio->isChecked())
    this->sett->edgesMethod = 0;
  else
    this->sett->edgesMethod = 1;

  this->sett->edgesThickness = ui->thickness->value();
  this->sett->sizeVert = ui->verticesSize->value();
  this->sett->colorVert.red = this->verticesColor.red();
  this->sett->colorVert.green = this->verticesColor.green();
  this->sett->colorVert.blue = this->verticesColor.blue();
  this->sett->colorEdges.red = this->edgesColor.red();
  this->sett->colorEdges.green = this->edgesColor.green();
  this->sett->colorEdges.blue = this->edgesColor.blue();
  this->sett->colorBack.red = this->backgroundColor.red();
  this->sett->colorBack.green = this->backgroundColor.green();
  this->sett->colorBack.blue = this->backgroundColor.blue();
  this->hide();
  FILE* setFile;
  setFile = fopen(SETTINGSNAME, "w+");
  writingToFile(sett, setFile);
  fclose(setFile);
  emit updateSettings();
}
