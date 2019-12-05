#include "notepad.h"
#include "dialog.h"

#include <sys/types.h>
#include <fstream>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

#include <QPushButton>
#include <QTableView>
#include <QtDebug>
#include <QStringListModel>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QVariant>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QTreeView>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent) {
    APPLY_FILTER = false;
    createCentralWidget();
    mainLayout = new QVBoxLayout(centralWidget);
    createTopLayout();
    createMiddleLayout();
    createBottomLayout();

    this->setCentralWidget(centralWidget);
}

void Notepad::createCentralWidget() {
    centralWidget = new QWidget;
    centralWidget->setMinimumWidth(800);
    centralWidget->setMinimumHeight(600);
}

void Notepad::createTopLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    createFromWidgets();
    createToWidgets();
    createCategoriesWidgets();
    createFilteringWidgets();

    layout->addWidget(labelFrom);
    layout->addWidget(dateFrom);
    layout->addWidget(labelTo);
    layout->addWidget(dateTo);
    layout->addWidget(labelCategory);
    layout->addWidget(dropdownCategories);
    layout->addWidget(buttonFilter);
    layout->addWidget(buttonClearFilters);

    mainLayout->addLayout(layout);
}

void Notepad::createFromWidgets() {
    labelFrom = new QLabel;
    labelFrom->setText("From: ");
    dateFrom = new QDateEdit;
}

void Notepad::createToWidgets() {
    labelTo = new QLabel;
    labelTo->setText("To:");
    dateTo = new QDateEdit;
}

void Notepad::createCategoriesWidgets() {
    labelCategory = new QLabel;
    labelCategory->setText("Category: ");
    dropdownCategories = new QComboBox;
    // automate adding items
    dropdownCategories->addItem("Option 1");
    dropdownCategories->addItem("Option 2");
}

void Notepad::createFilteringWidgets() {
    buttonFilter = new QPushButton("Filter");
    buttonClearFilters = new QPushButton("Clear");

    connect(buttonFilter, SIGNAL(clicked()), this, SLOT(filter()));
    connect(buttonClearFilters, SIGNAL(clicked()), this, SLOT(clearFilters()));
}

void Notepad::createMiddleLayout() {
    tableLayout = new QHBoxLayout;

    notesTable = this->getTableView();
    tableLayout->addWidget(notesTable);

    mainLayout->addLayout(tableLayout);
}

void Notepad::createBottomLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    createBottomLayoutWidgets();

    layout->addWidget(buttonNew);
    layout->addWidget(buttonEdit);
    layout->addWidget(buttonDelete);

    mainLayout->addLayout(layout);
}

void Notepad::createBottomLayoutWidgets() {
    buttonNew = new QPushButton("New");
    buttonEdit = new QPushButton("Edit");
    buttonDelete = new QPushButton("Delete");

    connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialogNew()));
    connect(buttonEdit, SIGNAL(clicked()), this, SLOT(openDialogEdit()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(deleteSelectedFile()));
}

void Notepad::deleteSelectedFile() {
    std::string selectedFile = getSelectedFile();
    if (selectedFile == "") {
        return;
    }
    std::string filePathS = "../Notepad/notes/" + selectedFile;
    char filePath[filePathS.length() + 1];
    strcpy(filePath, filePathS.c_str());
    if(remove(filePath) != 0) {
        perror( "Error deleting file" );
    }

    refreshNotesTable();
}

std::string Notepad::getSelectedFile() {
    QModelIndexList selectedNote = notesTable->selectionModel()->selectedRows();
    if (selectedNote.count() == 0) {
        return "";
    }
    QModelIndex index = selectedNote.value(0);
    QString selectedFileQString = index.data().toString();
    std::string selectedFile = selectedFileQString.toUtf8().constData();
    return selectedFile;
}

QTableView* Notepad::getTableView() {
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, tr("Title"));
    model->setHeaderData(1, Qt::Horizontal, tr("Date"));

    DIR *notesDirectory;
    struct dirent *note;
    if (notesDirectory = opendir("../Notepad/notes")) {
        while(note = readdir(notesDirectory)){
            if(strcmp(note->d_name, ".") != 0 && strcmp(note->d_name, "..") != 0) {
                if (!APPLY_FILTER || dateIsValid(note->d_name)) {
                    QList<QStandardItem *> data = getNoteInfoByFilename(*note);
                    model->appendRow(data);
                }
            }
        }
        closedir(notesDirectory);
    }

    // table settings
    QTableView *table = new QTableView;
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnWidth(0, 200);

    return table;
}

QList<QStandardItem *> Notepad::getNoteInfoByFilename(struct dirent note) {
    QList<QStandardItem *> notesInfo;
    std::string dateString = getFileDate(note.d_name);
    char dateChar[dateString.length() + 1];
    strcpy(dateChar, dateString.c_str());
    notesInfo.append(new QStandardItem(note.d_name));
    notesInfo.append(new QStandardItem(dateChar));
    return notesInfo;
}

std::string Notepad::getFileDate(char* fileName) {
    int i;
    std::string fileNameString = "";
    for (i = 0; i < strlen(fileName); i++) {
        fileNameString = fileNameString + fileName[i];
    }
    std::string filePath = "../Notepad/notes/" + fileNameString;
    std::string line;
    std::string date;
    std::ifstream myfile (filePath);
    if (myfile.is_open()) {
        getline (myfile,line);
        getline (myfile,line); // date is in the second line of each file
        std::string dateLine = line;
        date = dateLine.substr(6);
        myfile.close();
    }
    std::string formatted = "";
    formatted = date = date.substr(8,2)+"/"+date.substr(5,2)+"/"+date.substr(0,4);
    return formatted;
}

void Notepad::openDialogNew() {
    Dialog dialog;
    dialog.isEditMode = false;
    if (dialog.exec()) {
        dialog.saveNote();
        refreshNotesTable();
    }
}

void Notepad::openDialogEdit() {
    Dialog dialog;
    dialog.isEditMode = true;
    std::string selectedFile = getSelectedFile();
    if (selectedFile == "") {
        return;
    }
    dialog.bindInitialData(selectedFile);
    if (dialog.exec()) {
        dialog.saveNote();
        refreshNotesTable();
    }
}

void Notepad::refreshNotesTable() {
    delete notesTable;
    notesTable = this->getTableView();
    tableLayout->addWidget(notesTable);
}

bool Notepad::dateIsValid(std::string fileName) {
    int year, month, day, fromYear, fromMonth, fromDay, toYear, toMonth, toDay;
    std::string y, m, d, fy, fm, fd, ty, tm, td;
    std::string line;
    std::string filePath = "../Notepad/notes/" + fileName;
    std::ifstream myfile (filePath);
    if (myfile.is_open()) {
        getline(myfile, line); // discard category line
        getline(myfile, line);
        y = line.substr(6 + 0, 4);  year = std::stoi(y);
        m = line.substr(6 + 5, 2);  month = std::stoi(m);
        d = line.substr(6 + 8, line.length() - 14); day = std::stoi(d);
        myfile.close();
    }
    std::string from = dateFrom->text().toStdString();
    fy = from.substr(6, 4);  fromYear = std::stoi(fy);
    fm = from.substr(3, 2);  fromMonth = std::stoi(fm);
    fd = from.substr(0, 2); fromDay = std::stoi(fd);
    std::string to = dateTo->text().toStdString();
    ty = to.substr(6, 4);  toYear = std::stoi(ty);
    tm = to.substr(3, 2);  toMonth = std::stoi(tm);
    td = to.substr(0, 2); toDay = std::stoi(td);

    bool fromDateValid = dateIsLarger(year, month, day, fromYear, fromMonth, fromDay);
    bool toDateValid = dateIsLarger(toYear, toMonth, toDay, year, month, day);

    if (fromDateValid && toDateValid) {
        return true;
    }


    return false;
}

bool Notepad::dateIsLarger(int y1, int m1, int d1, int y2, int m2, int d2) {
    if (y1 > y2) return true;
    else if (y1 < y2) return false;

    if (m1 > m2) return true;
    else if (m1 < m2) return false;

    if (d1 >= d2) return true;
    return false;
}

void Notepad::filter() {
    APPLY_FILTER = true;
    refreshNotesTable();
}

void Notepad::clearFilters() {
    APPLY_FILTER = false;
    refreshNotesTable();
}
Notepad::~Notepad() {
}
