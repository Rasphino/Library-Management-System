//
// Created by rasp on 19-5-14.
//

#include "Borrow.h"
#include "login.h"

Borrow::Borrow(QWidget *parent) : QWidget(parent) {

    UserModel = new QSqlRelationalTableModel;
    UserModel->setTable("librarycard");
    BookModel = new QSqlRelationalTableModel;
    BookModel->setTable("books");

    UserView = new QTableView;
    UserView->setModel(UserModel);
    UserView->setSortingEnabled(true);
    UserView->verticalHeader()->hide();
    UserView->setSelectionBehavior(QAbstractItemView::SelectRows);
    UserView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UserView->setSelectionMode(QAbstractItemView::SingleSelection);
    UserView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    UserView->show();
    connect(UserView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this,
            SLOT(slotUserChanged(QModelIndex, QModelIndex))
    );

    BookView = new QTableView;
    BookView->setModel(BookModel);
    BookView->setSortingEnabled(true);
    BookView->verticalHeader()->hide();
    BookView->setSelectionBehavior(QAbstractItemView::SelectRows);
    BookView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    BookView->setSelectionMode(QAbstractItemView::SingleSelection);
    BookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    BookView->show();
    connect(BookView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this,
            SLOT(slotBookChanged(QModelIndex, QModelIndex))
    );

    UserID = new QLabel(tr("User ID: "));
    BookID = new QLabel(tr("Book ID: "));
    UserLineEdit = new QLineEdit;
    BookLineEdit = new QLineEdit;
    Button = new QPushButton(tr("Borrow"));
    connect(Button,
            SIGNAL(clicked()),
            this,
            SLOT(slotBorrow())
    );

    auto *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(UserView, 0, 0, 1, 2);
    mainLayout->addWidget(BookView, 0, 2, 1, 2);
    mainLayout->addWidget(UserID, 1, 0, 1, 1);
    mainLayout->addWidget(UserLineEdit, 1, 1, 1, 1);
    mainLayout->addWidget(BookID, 1, 2, 1, 1);
    mainLayout->addWidget(BookLineEdit, 1, 3, 1, 1);
    mainLayout->addWidget(Button, 2, 3, 1, 1);

}

void Borrow::slotUserChanged(const QModelIndex &current, const QModelIndex &previous) {
    UserLineEdit->setText(UserModel->index(current.row(), 0).data().toString());
}

void Borrow::slotBookChanged(const QModelIndex &current, const QModelIndex &previous) {
    BookLineEdit->setText(BookModel->index(current.row(), 0).data().toString());
}

void Borrow::slotUpdate() {
    UserModel->select();
    BookModel->select();
}

void Borrow::slotBorrow() {
    QString bookno = BookLineEdit->text();
    QString userno = UserLineEdit->text();
    if (bookno.isEmpty() || userno.isEmpty()) {
        QMessageBox::information(this, tr("Error"), tr("Missing user ID or book ID!"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QSqlQueryModel model;
    model.setQuery(QString("SELECT storage FROM books WHERE bookno='%1'").arg(bookno));
    qDebug() << bookno << " " << userno << endl;
    if (model.record(0).value(0).toInt() <= 0) {
        QMessageBox::information(this, tr("Error"), tr("Out of storage!"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QString oper = Login::getUser();
    QSqlQuery q;
    q.prepare("INSERT INTO libraryrecords(cardno, bookno, lentdate, returndate, operator) "
              "VALUES (:cardno, :bookno, :lentdate, :returndate, :operator)");
    QDateTime time = QDateTime::currentDateTime();
    q.bindValue(":cardno", userno);
    q.bindValue(":bookno", bookno);
    q.bindValue(":lentdate", time);
    q.bindValue(":returndate", QString());
    q.bindValue(":operator", oper);
    if (q.exec()) {
        QMessageBox::information(this, tr("Success"), tr("Borrow book successfully!"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        q.prepare(QString("UPDATE books SET storage=storage-1 WHERE bookno='%1'").arg(bookno));
        q.exec();
    } else {
        QMessageBox::warning(this, tr("Error"), q.lastError().text(),
                             QMessageBox::Yes, QMessageBox::Yes);
    }
    BookModel->select(); // update
}
