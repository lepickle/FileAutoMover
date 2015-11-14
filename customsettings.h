#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include <QDialog>

namespace Ui {
class CustomSettings;
}

class CustomSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CustomSettings(QWidget *parent = 0);
    ~CustomSettings();

private:
    Ui::CustomSettings *ui;
};

#endif // CUSTOMSETTINGS_H
