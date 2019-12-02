#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

signals:

public slots:
    void openDialog();

};
#endif // NOTEPAD_H
