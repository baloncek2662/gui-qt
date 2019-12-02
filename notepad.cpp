#include "notepad.h"
#include "dialog.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTreeView>
#include <QSpinBox>
#include <QtDebug>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent) {
    QWidget *widget = new QWidget;

    auto *l = new QVBoxLayout(widget);
    auto *gb = new QGroupBox;
    auto *tv = new QTreeView;

    l->addWidget(gb);
    l->addWidget(tv);

    QPushButton *pb = new QPushButton("Add Button");

    connect(pb, SIGNAL(clicked()), this, SLOT(openDialog()));

    l->addWidget(pb);
    this->setCentralWidget(widget);
}

void Notepad::openDialog() {
    Dialog dialog;
    if (dialog.exec()) {
        qDebug() << "Action if saved changes";
    } else {
        qDebug() << "Action if cancelled changes";
    }
}
