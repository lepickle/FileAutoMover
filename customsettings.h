#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class CustomSettings;
}

class CustomSettings : public QDialog
{
    Q_OBJECT

public:
    MainWindow *mainWindowForm;
    explicit CustomSettings(QWidget *parent = 0);
    ~CustomSettings();

private slots:
    void on_btn_Cancel_clicked();

    void on_btn_AddRegex_clicked();

private:
    Ui::CustomSettings *ui;
};

#endif // CUSTOMSETTINGS_H
