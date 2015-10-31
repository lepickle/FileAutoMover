#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QFileDialog>
#include <QDir>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QMessageLogger>
#include <QtDebug>
#include <QFileInfo>

class CoreService
{
private:
    QWidget *parent;
    QStringList extensionNameList;
    QString path;
    QString get_filename_extension_only(QString text);
    QString get_filename_firstletter_only(QString text);
    int get_filename_filesize_only(QString path);
    void create_folders_extension_names();
    void create_folders_file_firstletter();
    void create_folders_file_size();
    void move_files_extension_names();
    void move_files_first_letter();
    void move_files_file_size();
public:
    enum Setting {
        MoveByExtension,
        MoveByFirstLetter,
        MoveByDateModification,
        MoveByFileSize,
        MoveByUserSettings
    };
    CoreService(QWidget *root);
    Setting MoveMode;
    QString GetFilePathBrowse();
    void sortFiles();
    QStringList list_files();
    QStringList GetExtensionFileList(QStringList filesList);
    void SetExtensionFileList();
    void ShowMessageBox(QString message);
    void FilePath(QString s);
    QString FilePath();
};

CoreService::CoreService(QWidget * root)
{
    parent = root;
}

void CoreService::FilePath(QString s)
{
    path = s;
}

QString CoreService::FilePath()
{
    return path;
}

QString CoreService::get_filename_extension_only(QString text)//filters the filename and returns only the extension name
{
    QString temp = "";
    for (int i = text.size() - 1; i >= 0; i--)
    {
      if (text[i] == '.')
        break;
      else if (i == 0)
        temp = "txEoN";//(NoExt in reverse) It's like this because of the string reversal function after this code
      else
        temp += text[i];
    }
    //reverse string to correctly get the filename extension
    QString temp2 = "";
    for (int i = temp.size() - 1; i >= 0; i--)
      temp2 += temp[i];
    return temp2;
}

QString CoreService::get_filename_firstletter_only(QString text)
{
    return text[0].toUpper();
}

int CoreService::get_filename_filesize_only(QString path)
{
    QFileInfo file(path);
    return file.size();
}

void CoreService::ShowMessageBox(QString message)
{
    QMessageBox qMsg;
    qMsg.setIcon(QMessageBox::Information);
    qMsg.setText(message);
    qMsg.exec();
}

QString CoreService::GetFilePathBrowse()
{
    QString filePath = QFileDialog::getExistingDirectory(parent,
                                                         "Open Directory",
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    return filePath;

}

//TODO:
//Need to get list of extension types to move them into each of their folders

void CoreService::SetExtensionFileList()
{
    QStringList tempENL;//this is to prevent from appending to the previous list of the extensionNameList
    foreach (QString file, list_files())
    {
        QString fileExtensionNameTemp = get_filename_extension_only(file);
        if(!tempENL.contains(fileExtensionNameTemp))
            tempENL.append(fileExtensionNameTemp);
    }
    extensionNameList = tempENL;
}

QStringList CoreService::list_files()
{
    QDir myDir(path);
    QStringList fileList = myDir.entryList(QDir::Files);
    return fileList;
}

void CoreService::create_folders_extension_names()
{
    foreach(QString fileExt, extensionNameList)
    {
        QDir dir(path+"/"+fileExt);
        if (!dir.exists())
        {
            dir.mkpath(path+"/"+fileExt);
        }
    }
    qDebug()<<"finished create_folders()";
}

void CoreService::create_folders_file_firstletter()
{
    foreach(QString fileFirstLetter, list_files())
    {
        QDir dir(path+"/"+get_filename_firstletter_only(fileFirstLetter));
        if (!dir.exists())
        {
            dir.mkpath(path+"/"+get_filename_firstletter_only(fileFirstLetter));
        }
    }
}

void CoreService::create_folders_file_size()//to add more size functions
{
    foreach (QString fileSize, list_files())
    {
        int totalSize = get_filename_filesize_only(path+"/"+fileSize);
        if (totalSize >= 1 && totalSize < 1000)
        {
            QDir dir(path+"/"+"LessThan1KB");
            if (!dir.exists())
            {
                dir.mkpath(path+"/"+"LessThan1KB");
            }
        }
        else
        {
            QDir dir(path+"/"+"MoreThan1GB");
            if (!dir.exists())
            {
                dir.mkpath(path+"/"+"MoreThan1GB");
            }
        }
    }
}

void CoreService::move_files_extension_names()
{
    foreach(QString file, list_files())
    {
        QString extTemp = get_filename_extension_only(file);
        QFile::copy(path+"/"+file, path+"/"+extTemp+"/"+file);
    }
    //implement remove
}

void CoreService::move_files_first_letter()
{
    foreach(QString file, list_files())
    {
        QString firstnameTemp = get_filename_firstletter_only(file);
        QFile::copy(path+"/"+file, path+"/"+firstnameTemp+"/"+file);
    }
    //implement remove
}

void CoreService::move_files_file_size()//to add more size functions
{
    foreach(QString file, list_files())
    {
        int totalSize = get_filename_filesize_only(path+"/"+file);
        if (totalSize >= 1000 && totalSize < 2000)
        {
            QFile::copy(path+"/"+file, path+"/"+"LessThan1KB/"+file);
        }
        else
        {
            QFile::copy(path+"/"+file, path+"/"+"MoreThan1GB/"+file);
        }
    }
}

void CoreService::sortFiles()
{
    switch(MoveMode)
    {
        case CoreService::MoveByExtension:
            SetExtensionFileList();
            create_folders_extension_names();
            move_files_extension_names();
            ShowMessageBox("Files have now been moved by Extension");
            break;
        case CoreService::MoveByFirstLetter:
            create_folders_file_firstletter();
            move_files_first_letter();
            ShowMessageBox("Files have now been moved by FirstLetter");
            break;
        case CoreService::MoveByFileSize:
            create_folders_file_size();
            move_files_file_size();
            ShowMessageBox("Files have now been moved by File Size");
            break;
        default:
            ShowMessageBox("Invalid Command, Will move using First Letter Folders");
            create_folders_file_firstletter();
            move_files_first_letter();
            break;
    }
    qDebug()<<"sortFile();";
}

#endif // CORESERVICE_H
