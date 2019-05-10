#ifndef LIBRARY_MANAGEMENT_BOOKQUERY_H
#define LIBRARY_MANAGEMENT_BOOKQUERY_H

#include <QtWidgets>
#include <QtSql>


class BookQuery : public QWidget {
Q_OBJECT
public:
    explicit BookQuery(QWidget *parent = nullptr);

    ~BookQuery() {}

signals:

public slots:
    void slotClear();
    void slotQuery();

private:
    QLabel *BookTypeLabel;
    QLabel *BookNameLabel;
    QLabel *PublisherLabel;
    QLabel *YearLabel;
    QLabel *AuthorLabel;
    QLabel *PriceLabel;

    QLineEdit *BookTypeLineEdit;
    QLineEdit *BookNameLineEdit;
    QLineEdit *PublisherLineEdit;
    QLineEdit *YearLineEditL;
    QLineEdit *YearLineEditH;
    QLineEdit *AuthorLineEdit;
    QLineEdit *PriceLineEditL;
    QLineEdit *PriceLineEditH;

    QTableView *BookView;
    QSqlTableModel *BookModel;

    QDialogButtonBox *Buttons;

};


#endif //LIBRARY_MANAGEMENT_BOOKQUERY_H
