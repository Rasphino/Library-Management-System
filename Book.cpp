#include "Book.h"
#include "ReadOnlyDelegate.h"


Book::Book(QWidget *parent) : QWidget(parent) {
    SearchLineEdit = new QLineEdit;

    BookModel = new QSqlRelationalTableModel;
    BookModel->setTable("books");
    BookModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    BookView = new QTableView;
    BookView->setModel(BookModel);
    BookView->setSortingEnabled(true);
    BookView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    BookView->setSelectionBehavior(QAbstractItemView::SelectRows);
    BookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    BookView->setItemDelegate(new QSqlRelationalDelegate(BookView));
    BookView->setItemDelegateForColumn(0, new ReadOnlyDelegate(BookView));
    BookView->show();

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
            SLOT(slotUpdate())
    );

    auto *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(BookView, 0, 0, 1, 2);
    mainLayout->addWidget(Buttons, 1, 0);
    mainLayout->addWidget(CommitButtons, 1, 1);
}

void Book::slotDeleteEntry() {
    auto selection = BookView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        if (QMessageBox::Yes == QMessageBox::question(this,
                                                      tr("Really?"),
                                                      tr("Do you want to delete that?"),
                                                      QMessageBox::Yes | QMessageBox::No,
                                                      QMessageBox::No)) {
            for (const auto &item : selection) {
                int idx = item.data().value<int>();
                QSqlQuery q;
                if (q.exec(QString("DELETE FROM books WHERE bookno=%1").arg(idx)))
                    QMessageBox::information(this, tr("Success"), tr("Delete book successfully!"),
                                             QMessageBox::Yes, QMessageBox::Yes);
                else
                    QMessageBox::warning(this, tr("Error"), q.lastError().text(),
                                         QMessageBox::Yes, QMessageBox::Yes);
            }
        }
    }
    BookModel->select(); // refresh
}

void Book::slotAddEntry() {
    auto dialog = new NewBookDialog;
    dialog->setWindowTitle("New book");
    dialog->show();
    BookModel->select();
}

void Book::slotCommit() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Really?"),
                                                  tr("Do you want to commit all change?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::No)) {
        BookModel->submitAll();
        BookModel->select();
    }
}

void Book::slotUpdate() {
    BookModel->select();
}


NewBookDialog::NewBookDialog() {
    BookTypeLabel = new QLabel(tr("Type: "));
    BookNameLabel = new QLabel(tr("Name: "));
    PublisherLabel = new QLabel(tr("Publisher: "));
    YearLabel = new QLabel(tr("Year: "));
    AuthorLabel = new QLabel(tr("Author: "));
    PriceLabel = new QLabel(tr("Price: "));
    TotalLabel = new QLabel(tr("Total: "));
    StorageLabel = new QLabel(tr("Storage: "));

    BookTypeLineEdit = new QLineEdit;
    BookNameLineEdit = new QLineEdit;
    PublisherLineEdit = new QLineEdit;
    YearLineEdit = new QLineEdit;
    AuthorLineEdit = new QLineEdit;
    PriceLineEdit = new QLineEdit;
    TotalLineEdit = new QLineEdit;
    StorageLineEdit = new QLineEdit;

    Buttons = new QDialogButtonBox;
    Buttons->addButton(QDialogButtonBox::Ok);
    Buttons->addButton(QDialogButtonBox::Cancel);
    connect(Buttons->button(QDialogButtonBox::Ok),
            SIGNAL (clicked()),
            this,
            SLOT (slotAddEntry())
    );
    connect(Buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (slotCancel())
    );


    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(BookTypeLabel, 0, 0);
    mainLayout->addWidget(BookTypeLineEdit, 0, 1);
    mainLayout->addWidget(BookNameLabel, 0, 2);
    mainLayout->addWidget(BookNameLineEdit, 0, 3);
    mainLayout->addWidget(YearLabel, 0, 4);
    mainLayout->addWidget(YearLineEdit, 0, 5);
    mainLayout->addWidget(PublisherLabel, 1, 0);
    mainLayout->addWidget(PublisherLineEdit, 1, 1);
    mainLayout->addWidget(AuthorLabel, 1, 2);
    mainLayout->addWidget(AuthorLineEdit, 1, 3);
    mainLayout->addWidget(PriceLabel, 1, 4);
    mainLayout->addWidget(PriceLineEdit, 1, 5);
    mainLayout->addWidget(TotalLabel, 2, 0);
    mainLayout->addWidget(TotalLineEdit, 2, 1);
    mainLayout->addWidget(StorageLabel, 2, 2);
    mainLayout->addWidget(StorageLineEdit, 2, 3);
    mainLayout->addWidget(Buttons, 2, 5);
}

NewBookDialog::~NewBookDialog() {
    delete BookTypeLabel;
    delete BookNameLabel;
    delete PublisherLabel;
    delete YearLabel;
    delete AuthorLabel;
    delete PriceLabel;
    delete TotalLabel;
    delete StorageLabel;
    delete BookTypeLineEdit;
    delete BookNameLineEdit;
    delete PublisherLineEdit;
    delete YearLineEdit;
    delete AuthorLineEdit;
    delete PriceLineEdit;
    delete Buttons;
    delete mainLayout;
    delete TotalLineEdit;
    delete StorageLineEdit;
}

void NewBookDialog::slotAddEntry() {
    QString type = BookTypeLineEdit->text();
    QString name = BookNameLineEdit->text();
    QString pub = PublisherLineEdit->text();
    int year = YearLineEdit->text().toInt();
    QString author = AuthorLineEdit->text();
    double price = PriceLineEdit->text().toDouble();
    int total = TotalLabel->text().toInt();
    int storage = StorageLineEdit->text().toInt();
    QDateTime time = QDateTime::currentDateTime();

    if (name.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Book name cannot be empty!"),
                             QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QSqlQuery q;
    if (!q.prepare(QLatin1String(
            "insert into books(BookType, BookName, Publisher, Year, "
            "Author, Price, Total, Storage, UpdateTime) "
            "values(?, ?, ?, ?, ?, ?, ?, ?, ?);")))
        qDebug() << q.lastError();
    if (addBook(q, type, name, pub, year, author, price, total, storage, time))
        QMessageBox::information(this, tr("Success"), tr("Add book successfully!"),
                                 QMessageBox::Yes, QMessageBox::Yes);

    else
        QMessageBox::warning(this, tr("Error"), q.lastError().text(),
                             QMessageBox::Yes, QMessageBox::Yes);
    slotCancel();
}

void NewBookDialog::slotCancel() {
    close();
    delete this;
}


