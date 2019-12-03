#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QtDebug>
#include <QStringListModel>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private:
    QString title;
    QString text;

    void createCentralWidget();
    void createTopLayout();
    void createMiddleLayout();
    void createBottomLayout();
    void createFromWidgets();
    void createToWidgets();
    void createCategoriesWidgets();
    void createFilteringWidgets();
    void createBottomLayoutWidgets();

    QTableView* getTableView();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *labelFrom;
    QDateEdit *dateFrom;
    QLabel *labelTo;
    QDateEdit *dateTo;
    QLabel *labelCategory;
    QComboBox *dropdownCategories;
    QPushButton *buttonFilter;
    QPushButton *buttonClearFilters;
    QPushButton *buttonNew;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;

signals:

public slots:
    void openDialog();

};
#endif // NOTEPAD_H
