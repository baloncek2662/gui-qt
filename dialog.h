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

    bool isEditMode;

private:
    Ui::Dialog *ui;

    std::string initialFileName;
    QStringList categories;

    std::string getFileTitle(std::string fileName);
    int fileIsMarkdown(std::string fileName);
    QString getFileContent(std::string fileName);
    QStringList getCategoriesList(std::string fileName);
    void createFile();
    std::string currentDate();
    std::string getFormattedCategories();
    void deleteFile();

public slots:
    void addCategory();
    void removeCategory();
    void fillCategory();
};

#endif // DIALOG_H
