#include "customsettings.h"
#include "ui_customsettings.h"
#include <QStringListModel>
#include <QStringList>

QStringListModel *model;
QStringList list;

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

void CustomSettings::on_btn_Cancel_clicked()
{
    mainWindowForm->show();
    this->hide();
}

/*TODO:
 * Allow Deletion from list (hint: get index of list then compare to list)
 * Return the list of items from child to Parent
 * Make those shit work
 */

void CustomSettings::on_btn_AddRegex_clicked()
{
    model = new QStringListModel(this);
    list.append(ui->txt_Regex->text());
    model->setStringList(list);
    ui->listView->setModel(model);
}
