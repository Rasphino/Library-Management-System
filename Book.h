#ifndef LIBRARY_MANAGEMENT_BOOK_H
#define LIBRARY_MANAGEMENT_BOOK_H

#include <QtWidgets>
#include <QtSql>
#include "DBOperation.h"

class Book : public QWidget {
Q_OBJECT
public:
    explicit Book(QWidget *parent = nullptr);

    ~Book() {}

signals:
public slots:
    void slotDeleteEntry();
    void slotAddEntry();
    void slotCommit();
    void slotUpdate();
    void slotAddFromFile();

private:
    QLineEdit *SearchLineEdit;
    QTableView *BookView;
    QSqlTableModel *BookModel;
    QDialogButtonBox *Buttons;
    QDialogButtonBox *CommitButtons;
    QPushButton *AddFromFileButton;
};

class NewBookDialog : public QDialog {
Q_OBJECT
public:
    NewBookDialog();

    ~NewBookDialog();

public slots:
    void slotAddEntry();
    void slotCancel();


private:
    QLabel *BookTypeLabel;
    QLabel *BookNameLabel;
    QLabel *PublisherLabel;
    QLabel *YearLabel;
    QLabel *AuthorLabel;
    QLabel *PriceLabel;
    QLabel *TotalLabel;
    QLabel *StorageLabel;
    QLineEdit *BookTypeLineEdit;
    QLineEdit *BookNameLineEdit;
    QLineEdit *PublisherLineEdit;
    QLineEdit *YearLineEdit;
    QLineEdit *AuthorLineEdit;
    QLineEdit *PriceLineEdit;
    QLineEdit *TotalLineEdit;
    QLineEdit *StorageLineEdit;
    QDialogButtonBox *Buttons;
    QGridLayout *mainLayout;
};


#endif //LIBRARY_MANAGEMENT_BOOK_H
