#include "dialog.h"
#include "ui_dialog.h"

#include <sys/types.h>
#include <fstream>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

#include <QtDebug>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::bindInitialData(std::string fileName) {
    // title
    std::string titleString = getFileTitle(fileName);
    title = QString::fromStdString(titleString);
    this->ui->txtTitle->setText(title);
    // md checkbox
    isMarkdown = fileIsMarkdown(fileName);
    this->ui->checkboxMd->setChecked(isMarkdown);
    // content
    content = getFileContent(fileName);
    this->ui->txtContent->appendPlainText(content);
    // categories
    categoriesList = getCategoriesList(fileName);
    this->ui->categoriesList->addItems(categoriesList);
}

std::string Dialog::getFileTitle(std::string fileName) {
    std::string fileTitle;
    if (fileIsMarkdown(fileName)) {
        fileTitle = fileName.substr(0, fileName.length() - 3);
    } else {
        fileTitle = fileName.substr(0, fileName.length() - 4);
    }
    return fileTitle;
}

QString Dialog::getFileContent(std::string fileName) {
    std::string content = "";
    std::string line;
    std::string filePath = "../Notepad/notes/" + fileName;
    std::ifstream myfile (filePath);
    if (myfile.is_open()) {
        getline(myfile, line); getline(myfile, line); // discard date and category lines
        while (getline(myfile, line)) {
            content += line + "\n";
        }
        myfile.close();
    }
    QString contentQString = QString::fromStdString(content);
    return contentQString;
}

QStringList Dialog::getCategoriesList(std::string fileName) {
    QStringList* categoriesList = new QStringList;
    std::string categoriesStringList;
    std::string line;
    std::string filePath = "../Notepad/notes/" + fileName;
    std::ifstream myfile (filePath);
    if (myfile.is_open()) {
        getline(myfile, line);
        categoriesStringList = line;
        categoriesStringList = categoriesStringList.substr(10); // we omit the "categories" identifier at the start
        std::string delimiter = ", ";
        size_t pos = 0;
        std::string token;
        while ((pos = categoriesStringList.find(delimiter)) != std::string::npos) {
            token = categoriesStringList.substr(0, pos);
            categoriesList->append(QString::fromStdString(token));
            categoriesStringList.erase(0, pos + delimiter.length());
        }
        token = categoriesStringList.substr(0, pos);
        categoriesList->append(QString::fromStdString(token));
        categoriesStringList.erase(0, pos + delimiter.length());

        myfile.close();
    }
    return *categoriesList;
}

int Dialog::fileIsMarkdown(std::string fileName) {
    return fileName.compare(fileName.length() - 3, 3, ".md") == 0 ? 1 : 0;
}

void Dialog::saveNote() {

}

