#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QMessageBox>


SettingsDialog::SettingsDialog(int maxIterations, double scaleFactor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->maxIterations->setValue(maxIterations);
    ui->scaleFactor->setValue(scaleFactor);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::getMaxIterations() {
    return ui->maxIterations->text().toInt();
}

double SettingsDialog::getScaleFactor() {
    return ui->scaleFactor->text().toDouble();
}
