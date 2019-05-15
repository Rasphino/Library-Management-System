//
// Created by rasp on 19-5-15.
//

#include "Return.h"

Return::Return(QWidget *parent) : QWidget(parent) {
    RecordView = new QTableView;
    RecordModel = new QSqlQueryModel;
    Button = new QPushButton(tr("Delete"));
    connect(Button,
            SIGNAL(clicked()),
            this,
            SLOT(slotDeleteEntry())
    );

    RecordModel->setQuery(QString("SELECT fid,c.cardno,name,b.bookno,bookname,lentdate,operator "
                                  "FROM libraryrecords as r, books as b, librarycard as c "
                                  "WHERE r.bookno=b.bookno AND r.cardno=c.cardno AND returndate IS NULL;"));
    RecordView->setModel(RecordModel);
    RecordView->setSortingEnabled(true);
    RecordView->verticalHeader()->hide();
    RecordView->setSelectionBehavior(QAbstractItemView::SelectRows);
    RecordView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    RecordView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    RecordView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    RecordView->show();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(RecordView);
    mainLayout->addWidget(Button);
}

void Return::slotDeleteEntry() {
    auto selection = RecordView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        if (QMessageBox::Yes == QMessageBox::question(this,
                                                      tr("Really?"),
                                                      tr("Do you want to delete that?"),
                                                      QMessageBox::Yes | QMessageBox::No,
                                                      QMessageBox::No)) {
            for (const auto &item : selection) {
                int idx = item.data().value<int>();
                QDateTime time = QDateTime::currentDateTime();
                QSqlQuery q;
                q.prepare("UPDATE libraryrecords SET returndate=:returndate WHERE fid=:fid");
                q.bindValue(":returndate", time);
                q.bindValue(":fid", idx);
                if (q.exec())
                    QMessageBox::information(this, tr("Success"), tr("Return book successfully!"),
                                             QMessageBox::Yes, QMessageBox::Yes);
                else
                    QMessageBox::warning(this, tr("Error"), q.lastError().text(),
                                         QMessageBox::Yes, QMessageBox::Yes);
            }
        }
    }
    RecordModel->setQuery(QString("SELECT fid,c.cardno,name,b.bookno,bookname,lentdate,operator "
                                  "FROM libraryrecords as r, books as b, librarycard as c "
                                  "WHERE r.bookno=b.bookno AND r.cardno=c.cardno AND returndate IS NULL;"));
}
