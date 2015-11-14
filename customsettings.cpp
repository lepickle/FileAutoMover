#include "customsettings.h"
#include "ui_customsettings.h"

CustomSettings::CustomSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomSettings)
{
    ui->setupUi(this);
}

CustomSettings::~CustomSettings()
{
    delete ui;
}
