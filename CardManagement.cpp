//
// Created by rasp on 19-5-10.
//

#include "CardManagement.h"
#include "ReadOnlyDelegate.h"

CardManagement::CardManagement(QWidget *parent) : QWidget(parent) {
    CardModel = new QSqlRelationalTableModel;
    CardModel->setTable("librarycard");
    CardModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    CardView = new QTableView;
    CardView->setModel(CardModel);
    CardView->setSortingEnabled(true);
    CardView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    CardView->setSelectionBehavior(QAbstractItemView::SelectRows);
    CardView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    CardView->setItemDelegate(new QSqlRelationalDelegate(CardView));
    CardView->setItemDelegateForColumn(0, new ReadOnlyDelegate(CardView));
    CardView->show();

    Buttons = new QDialogButtonBox(this);
    Buttons->addButton(QDialogButtonBox::Ok);
    Buttons->addButton(QDialogButtonBox::Cancel);
    Buttons->button(QDialogButtonBox::Ok)->setText(tr("New"));
    Buttons->button(QDialogButtonBox::Cancel)->setText(tr("Delete"));
    connect(Buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (slotDeleteEntry())
    );
    connect(Buttons->button(QDialogButtonBox::Ok),
            SIGNAL (clicked()),
            this,
            SLOT (slotAddEntry())
    );
    CommitButtons = new QDialogButtonBox(this);
    CommitButtons->addButton(QDialogButtonBox::Ok)->setText(tr("Commit"));
    CommitButtons->addButton(QDialogButtonBox::Cancel)->setText(tr("Reset"));
    connect(CommitButtons->button(QDialogButtonBox::Ok),
            SIGNAL(clicked()),
            this,
            SLOT(slotCommit())
    );
    connect(CommitButtons->button(QDialogButtonBox::Cancel),
            SIGNAL(clicked()),
            this,
            SLOT(slotReset())
    );


    NameLabel = new QLabel(tr("Name: "));
    DepartmentLabel = new QLabel(tr("Department: "));
    CardTypeLabel = new QLabel(tr("Card type: "));
    InfoLabel = new QLabel;

    NameLineEdit = new QLineEdit;
    DepartmentLineEdit = new QLineEdit;
    CardTypeLineEdit = new QLineEdit;

    auto *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(CardView, 0, 0, 1, 3);
    mainLayout->addWidget(NameLabel, 1, 0);
    mainLayout->addWidget(NameLineEdit, 1, 1);
    mainLayout->addWidget(DepartmentLabel, 2, 0);
    mainLayout->addWidget(DepartmentLineEdit, 2, 1);
    mainLayout->addWidget(CardTypeLabel, 3, 0);
    mainLayout->addWidget(CardTypeLineEdit, 3, 1);
    mainLayout->addWidget(InfoLabel, 4, 0, 1, 3);
    mainLayout->addWidget(Buttons, 2, 2);
    mainLayout->addWidget(CommitButtons, 3, 2);
}

void CardManagement::slotDeleteEntry() {
    auto selection = CardView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        if (QMessageBox::Yes == QMessageBox::question(this,
                                                      tr("Really?"),
                                                      tr("Do you want to delete that?"),
                                                      QMessageBox::Yes | QMessageBox::No,
                                                      QMessageBox::No)) {
            for (const auto &item : selection) {
                int idx = item.data().value<int>();
                QSqlQuery q;
                if (q.exec(QString("DELETE FROM librarycard WHERE cardno=%1").arg(idx)))
                    InfoLabel->setText(tr("Delete success"));
                else
                    InfoLabel->setText(q.lastError().text());
            }
        }
    }
    CardModel->select(); // refresh
}

void CardManagement::slotAddEntry() {
    QString name = NameLineEdit->text();
    QString department = DepartmentLineEdit->text();
    QString cardType = CardTypeLineEdit->text();
    QDateTime time = QDateTime::currentDateTime();
    if (name == "") {
        InfoLabel->setText(tr("Please give a name!"));
        return;
    }
    QSqlQuery q;
    q.prepare("insert into librarycard(name, department, cardtype, updatetime) "
              "VALUES (:name, :department, :cardType, :updateTime)");
    q.bindValue(":name", name);
    q.bindValue(":department", department);
    q.bindValue(":cardType", cardType);
    q.bindValue(":updateTime", time);
    qDebug() << q.lastQuery() << endl;
    if (q.exec())
        InfoLabel->setText(tr("Insert success"));
    else
        InfoLabel->setText(q.lastError().text());
    CardModel->select(); // refresh
}

void CardManagement::slotCommit() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Really?"),
                                                  tr("Do you want to commit all change?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::No)) {
        CardModel->submitAll();
        CardModel->select();
    }
}

void CardManagement::slotReset() {
    CardModel->select();
}
