#ifndef LIBRARY_MANAGEMENT_BORROW_H
#define LIBRARY_MANAGEMENT_BORROW_H

#include <QtWidgets>
#include <QtSql>

#include <QtWidgets/QWidget>

class Borrow : public QWidget {
Q_OBJECT
public:
    explicit Borrow(QWidget *parent = nullptr);

    ~Borrow() {}

    void slotUpdate();

signals:

public slots:
    void slotUserChanged(const QModelIndex &current, const QModelIndex &previous);
    void slotBookChanged(const QModelIndex &current, const QModelIndex &previous);
    void slotBorrow();

private:
    QTableView *UserView;
    QTableView *BookView;
    QSqlRelationalTableModel *UserModel;
    QSqlRelationalTableModel *BookModel;
    QLabel *UserID;
    QLabel *BookID;
    QLineEdit *UserLineEdit;
    QLineEdit *BookLineEdit;
    QPushButton *Button;
};


#endif //LIBRARY_MANAGEMENT_BORROW_H
