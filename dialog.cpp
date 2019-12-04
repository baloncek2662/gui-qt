#include "dialog.h"
#include "ui_dialog.h"

#include <sys/types.h>
#include <fstream>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include<string>

#include <QtDebug>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::bindInitialData(std::string fileName) {
    initialFileName = fileName;
    // title
    std::string titleString = getFileTitle(fileName);
    QString title = QString::fromStdString(titleString);
    this->ui->txtTitle->setText(title);
    // md checkbox
    int isMarkdown = fileIsMarkdown(fileName);
    this->ui->checkboxMd->setChecked(isMarkdown);
    // content
    QString content = getFileContent(fileName);
    this->ui->txtContent->appendPlainText(content);
    // categories
    QStringList categoriesList = getCategoriesList(fileName);
    this->ui->categoriesList->addItems(categoriesList);

    categories = categoriesList;
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
        int i = 0;
        while ((pos = categoriesStringList.find(delimiter)) != std::string::npos) {
            token = categoriesStringList.substr(0, pos);
            categoriesList->append(QString::fromStdString(token));
            categoriesStringList.erase(0, pos + delimiter.length());
            i++;
        }
        if (i > 0) {
            token = categoriesStringList.substr(0, pos);
            categoriesList->append(QString::fromStdString(token));
            categoriesStringList.erase(0, pos + delimiter.length());
        }

        myfile.close();
    }
    return *categoriesList;
}

int Dialog::fileIsMarkdown(std::string fileName) {
    return fileName.compare(fileName.length() - 3, 3, ".md") == 0 ? 1 : 0;
}

void Dialog::saveNote() {
    if (isEditMode) {
        deleteFile();
    }
    createFile();
}

void Dialog::createFile() {
    QString title = this->ui->txtTitle->text();
    if (title.isNull() || title.isEmpty()) {
        // TODO optionally display error message
        return;
    }
    // TODO check for files with the same name
    bool isMarkdown = this->ui->checkboxMd->isChecked();
    std::string extension = isMarkdown ? ".md" : ".txt";
    std::string filePathS = "../Notepad/notes/" + title.toStdString() + extension;
    std::ofstream outfile (filePathS);

    // insert categoriess
    outfile << "category: " << getFormattedCategories() << std::endl;
    // insert date
    std::string date = currentDate();
    outfile << "date: " << date << std::endl;
    // insert content
    QString content = this->ui->txtContent->toPlainText();
    outfile << content.toStdString() << std::endl;

    outfile.close();
}

std::string Dialog::currentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "/" + std::to_string(1 + ltm->tm_mon)
            + "/" + std::to_string(ltm->tm_mday);
}

void Dialog::addCategory() {
    QString category = this->ui->txtCategory->text();
    if (categories.indexOf(category) == -1) {
        categories.append(category);
    }
    this->ui->categoriesList->clear();
    this->ui->categoriesList->addItems(categories);
}

void Dialog::removeCategory() {
    QString category = this->ui->txtCategory->text();
    int categoryRowIndex = categories.indexOf(category);
    if (categoryRowIndex > -1) {
        categories.takeAt(categoryRowIndex);
    }
    this->ui->categoriesList->clear();
    this->ui->categoriesList->addItems(categories);
}

void Dialog::fillCategory() {
    QList<QListWidgetItem *> selectedCategories = this->ui->categoriesList->selectedItems();
    QString selectedCategory = selectedCategories[0]->text();
    this->ui->txtCategory->setText(selectedCategory);
}

std::string Dialog::getFormattedCategories() {
    std::string formattedCategories = "";
    for (const auto& categ : categories  ) {
        formattedCategories += categ.toStdString() + ", ";
    }
    // remove last ", "
    formattedCategories = formattedCategories.substr(0, formattedCategories.length() - 2);

    return formattedCategories;
}

void Dialog::deleteFile() {
    std::string filePathS = "../Notepad/notes/" + initialFileName;
    char filePath[filePathS.length() + 1];
    strcpy(filePath, filePathS.c_str());
    if(remove(filePath) != 0) {
        perror( "Error deleting file" );
    }
}

