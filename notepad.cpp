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
    QWidget *widget = new QWidget;
    widget->setMinimumWidth(800);
    widget->setMinimumHeight(600);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addLayout(this->getTopLayout());
    mainLayout->addLayout(this->getMiddleLayout());
    mainLayout->addLayout(this->getBottomLayout());

    this->setCentralWidget(widget);
}

QHBoxLayout* Notepad::getTopLayout() {
    QHBoxLayout *layout = new QHBoxLayout;

    QLabel *labelFrom = new QLabel;
    labelFrom->setText("From: ");
    layout->addWidget(labelFrom);
    QDateEdit *dateFrom = new QDateEdit;
    layout->addWidget(dateFrom);
    QLabel *labelTo = new QLabel;
    labelTo->setText("To:");
    layout->addWidget(labelTo);
    QDateEdit *dateTo = new QDateEdit;
    layout->addWidget(dateTo);
    QLabel *labelCategory = new QLabel;
    labelCategory->setText("Category: ");
    layout->addWidget(labelCategory);
    QComboBox *dropdownCategories = new QComboBox;
    // automate adding items
    dropdownCategories->addItem("Option 1");
    dropdownCategories->addItem("Option 2");
    layout->addWidget(dropdownCategories);
    QPushButton *buttonFilter = new QPushButton("Filter");
    layout->addWidget(buttonFilter);
    QPushButton *buttonClearFilters = new QPushButton("Clear");
    layout->addWidget(buttonClearFilters);

    return layout;
}

QHBoxLayout* Notepad::getMiddleLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    QTableView *table = this->getTableView();
    layout->addWidget(table);
    //move to "new", "edit" buttons
    //connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialog()));
    return layout;
}

QHBoxLayout* Notepad::getBottomLayout() {
    QHBoxLayout *layout = new QHBoxLayout;

    QPushButton *buttonNew = new QPushButton("New");
    layout->addWidget(buttonNew);
    QPushButton *buttonEdit = new QPushButton("Edit");
    layout->addWidget(buttonEdit);
    QPushButton *buttonDelete = new QPushButton("Delete");
    layout->addWidget(buttonDelete);
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialog()));
    return layout;
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
