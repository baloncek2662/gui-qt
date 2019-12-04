#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <sys/types.h>
#include <dirent.h>

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
#include <QAbstractTableModel>
#include <QStandardItem>

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
    QList<QStandardItem *> getNoteInfoByFilename(struct dirent);
    std::string getFileDate(char* fileName);

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
    QTableView *notesTable;

signals:

public slots:
    void openDialog();
    void deleteSelectedFile();

};


#endif // NOTEPAD_H
