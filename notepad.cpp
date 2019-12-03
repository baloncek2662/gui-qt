#include "notepad.h"
#include "dialog.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTableView>
#include <QSpinBox>
#include <QtDebug>
#include <QStringListModel>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent) {
    QWidget *widget = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    QVBoxLayout** layoutRows = getLayoutRows();
    mainLayout->addLayout(layoutRows[0]);
    mainLayout->addLayout(layoutRows[1]);
    mainLayout->addLayout(layoutRows[2]);

    this->setCentralWidget(widget);
}

QVBoxLayout** Notepad::getLayoutRows() {
    QVBoxLayout** layouts = (QVBoxLayout**)malloc(1 * sizeof(QVBoxLayout*));

    layouts[0] = this->getTopLayout();
    layouts[1] = this->getMiddleLayout();
    layouts[2] = this->getBottomLayout();

    return layouts;
}

QVBoxLayout* Notepad::getTopLayout() {
    QVBoxLayout *layout = new QVBoxLayout;
    QTableView *table = this->getTableView();
    layout->addWidget(table);
    QPushButton *buttonNew = new QPushButton("New");
    layout->addWidget(buttonNew);
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialog()));
    return layout;
}

QVBoxLayout* Notepad::getMiddleLayout() {
    QVBoxLayout *layout = new QVBoxLayout;
    QTableView *table = this->getTableView();
    layout->addWidget(table);
    QPushButton *buttonNew = new QPushButton("Bew");
    layout->addWidget(buttonNew);
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(openDialog()));
    return layout;
}

QVBoxLayout* Notepad::getBottomLayout() {
    QVBoxLayout *layout = new QVBoxLayout;
    QTableView *table = this->getTableView();
    layout->addWidget(table);
    QPushButton *buttonNew = new QPushButton("Stew");
    layout->addWidget(buttonNew);
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
