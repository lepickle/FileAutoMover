#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <CoreService.h>
#include <QStandardItemModel>
#include "customsettings.h"

CoreService *cs;
QStringList extension_name_list;
QString filePath;
CustomSettings *customSettingsForm;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cs = new CoreService(this);
    ui->folderDir->setText(cs->GetFilePathBrowse());
}

void MainWindow::on_btn_ListFiles_clicked()
{
    cs = new CoreService(this);
    filePath = ui->folderDir->text();
    cs->FilePath(filePath);//set file path
    QStringList fileList = cs->list_files();

    QStandardItemModel* model = new QStandardItemModel(0, 1);
    QString header1 = "File Names";
    QStandardItem* item = new QStandardItem(header1);
    model->setHorizontalHeaderItem(0, item);
    for (int i = 0; i < fileList.length(); i++)
    {
        QStandardItem* rowItem =new QStandardItem(fileList[i]);
        model->insertRow(i, rowItem);
    }
    ui->tbl_FileList->setModel(model);
}

void MainWindow::on_btn_SortFiles_clicked()
{
    if (!ui->folderDir->text().isEmpty())
    {
        filePath = ui->folderDir->text();
        cs = new CoreService(this);
        cs->FilePath(filePath);
        if (ui->rdBtn_MoveByExtension->isChecked())
        {
            cs->MoveMode = cs->CoreService::MoveByExtension;
        }
        else if (ui->rdBtn_MoveByFirstLetter->isChecked())
        {
            cs->MoveMode = cs->CoreService::MoveByFirstLetter;
        }
        cs->sortFiles();
        qDebug()<<"sortFiles()";
    }
    else
        cs->ShowMessageBox("No Directory selected");
}

void MainWindow::on_btn_CreateCustomSetting_clicked()
{
    if (!customSettingsForm)
    {
        customSettingsForm = new CustomSettings();
    }
    if (customSettingsForm)
    {
        customSettingsForm->mainWindowForm = this;
        customSettingsForm->show();
//        this->hide();
    }
}
