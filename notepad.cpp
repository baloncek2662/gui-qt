#include "notepad.h"
#include "dialog.h"

#include <QPushButton>
#include <QTableView>
#include <QtDebug>
#include <QStringListModel>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QVariant>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent) {
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
}

void Notepad::createMiddleLayout() {
    // TODO
    QHBoxLayout *layout = new QHBoxLayout;
    QTableView *table = this->getTableView();
    layout->addWidget(table);

    mainLayout->addLayout(layout);
}

void Notepad::createBottomLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    createBottomLayoutWidgets();

    layout->addWidget(buttonNew);
    layout->addWidget(buttonEdit);
    layout->addWidget(buttonDelete);
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(buttonEdit, SIGNAL(clicked()), this, SLOT(openDialog()));

    mainLayout->addLayout(layout);
}

void Notepad::createBottomLayoutWidgets() {
    buttonNew = new QPushButton("New");
    buttonEdit = new QPushButton("Edit");
    buttonDelete = new QPushButton("Delete");
}

QTableView* Notepad::getTableView() {
    QTableView *table = new QTableView;

    QStringListModel *np = new QStringListModel();
    QStringList list;
    list << "a" << "b" << "c";
    np->setStringList(list);
    table->setModel(np);

    return table;
}

void Notepad::openDialog() {
    Dialog dialog;
    if (dialog.exec()) {
        qDebug() << "Action if saved changes";
    } else {
        qDebug() << "Action if cancelled changes";
    }
}

Notepad::~Notepad() {
}
