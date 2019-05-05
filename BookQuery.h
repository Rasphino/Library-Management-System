#ifndef LIBRARY_MANAGEMENT_BOOKQUERY_H
#define LIBRARY_MANAGEMENT_BOOKQUERY_H

#include <QtWidgets>

class BookQuery : public QWidget {
Q_OBJECT
public:
    explicit BookQuery(QWidget *parent = nullptr);

    ~BookQuery() {}

signals:

public slots:
//    void slotClear();

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

    QDialogButtonBox *Buttons;

};


#endif //LIBRARY_MANAGEMENT_BOOKQUERY_H
