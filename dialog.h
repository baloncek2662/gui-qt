#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void bindInitialData(std::string fileName);
    void saveNote();

private:
    Ui::Dialog *ui;

    std::string getFileTitle(std::string fileName);
    int fileIsMarkdown(std::string fileName);
    QString getFileContent(std::string fileName);
    QStringList getCategoriesList(std::string fileName);


    QString title;
    QString content;
    int isMarkdown;
    QStringList categoriesList;
};

#endif // DIALOG_H
