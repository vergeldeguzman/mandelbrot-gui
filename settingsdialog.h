#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(int maxIterations, double scaleFactor, QWidget *parent = 0);
    ~SettingsDialog();

    int getMaxIterations();
    double getScaleFactor();

private slots:

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
