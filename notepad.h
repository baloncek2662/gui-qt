#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();
    QTableView* getTableView();
    QHBoxLayout* getTopLayout();
    QHBoxLayout* getMiddleLayout();
    QHBoxLayout* getBottomLayout();

private:
    QString title;
    QString text;

signals:

public slots:
    void openDialog();

};
#endif // NOTEPAD_H
