#include "BookQuery.h"
#include "DBOperation.h"
#include <QSizePolicy>

BookQuery::BookQuery(QWidget *parent) : QWidget(parent) {
    BookTypeLabel = new QLabel(tr("Type: "));
    BookNameLabel = new QLabel(tr("Name: "));
    PublisherLabel = new QLabel(tr("Publisher: "));
    YearLabel = new QLabel(tr("Year: "));
    AuthorLabel = new QLabel(tr("Author: "));
    PriceLabel = new QLabel(tr("Price: "));

    BookTypeLineEdit = new QLineEdit;
    BookNameLineEdit = new QLineEdit;
    PublisherLineEdit = new QLineEdit;
    YearLineEditL = new QLineEdit;
    YearLineEditH = new QLineEdit;
    AuthorLineEdit = new QLineEdit;
    PriceLineEditL = new QLineEdit;
    PriceLineEditH = new QLineEdit;

    Buttons = new QDialogButtonBox(this);
    Buttons->addButton(QDialogButtonBox::Ok);
    Buttons->addButton(QDialogButtonBox::Cancel);
    Buttons->button(QDialogButtonBox::Ok)->setText(tr("Find"));
    Buttons->button(QDialogButtonBox::Cancel)->setText(tr("Clear"));

    connect(Buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (slotClear())
    );

    connect(Buttons->button(QDialogButtonBox::Ok),
            SIGNAL (clicked()),
            this,
            SLOT (slotQuery())
    );


    qDebug() << initDb();

    BookModel = new QSqlTableModel;
    BookModel->setTable("books");

    BookView = new QTableView;
    BookView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    BookView->setModel(BookModel);
    BookView->setSortingEnabled(true);
    BookView->setSelectionMode(QAbstractItemView::SingleSelection);
    BookView->setItemDelegate(new QSqlRelationalDelegate(BookView));
    BookView->show();


    auto *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(BookTypeLabel, 0, 0);
    mainLayout->addWidget(BookTypeLineEdit, 0, 1);
    mainLayout->addWidget(BookNameLabel, 0, 2);
    mainLayout->addWidget(BookNameLineEdit, 0, 3);
    mainLayout->addWidget(YearLabel, 0, 4);
    mainLayout->addWidget(YearLineEditL, 0, 5);
    mainLayout->addWidget(YearLineEditH, 0, 6);
    mainLayout->addWidget(PublisherLabel, 1, 0);
    mainLayout->addWidget(PublisherLineEdit, 1, 1);
    mainLayout->addWidget(AuthorLabel, 1, 2);
    mainLayout->addWidget(AuthorLineEdit, 1, 3);
    mainLayout->addWidget(PriceLabel, 1, 4);
    mainLayout->addWidget(PriceLineEditL, 1, 5);
    mainLayout->addWidget(PriceLineEditH, 1, 6);

    mainLayout->addWidget(BookView, 2, 0, 1, 7);

    mainLayout->setColumnStretch(1, 2);
    mainLayout->setColumnStretch(3, 2);
    mainLayout->setColumnStretch(5, 1);
    mainLayout->setColumnStretch(6, 1);

    mainLayout->addWidget(Buttons, 3, 5, 1, 2);

}

void BookQuery::slotClear() {
    BookTypeLineEdit->clear();
    BookNameLineEdit->clear();
    PublisherLineEdit->clear();
    YearLineEditL->clear();
    YearLineEditH->clear();
    AuthorLineEdit->clear();
    PriceLineEditL->clear();
    PriceLineEditH->clear();
    BookModel->setFilter("");
    BookModel->select();
}

void BookQuery::slotQuery() {
    QString filter = "1=1 ";
    QString type = BookTypeLineEdit->text();
    QString name = BookNameLineEdit->text();
    QString publisher = PublisherLineEdit->text();
    QString author = AuthorLineEdit->text();
    QString yearL = YearLineEditL->text();
    QString yearH = YearLineEditH->text();
    QString priceL = PriceLineEditL->text();
    QString priceH = PriceLineEditH->text();
    if (type != "") filter.append(QString("and booktype='%1' ").arg(type));
    if (name != "") filter.append(QString("and bookname='%1' ").arg(name));
    if (publisher != "") filter.append(QString("and publisher='%1' ").arg(publisher));
    if (author != "") filter.append(QString("and author='%1' ").arg(author));
    if (yearL != "") filter.append(QString("and year>=%1 ").arg(yearL));
    if (yearH != "") filter.append(QString("and year<=%1 ").arg(yearH));
    if (priceL != "") filter.append(QString("and price>=money(%1) ").arg(priceL));
    if (priceH != "") filter.append(QString("and price<=money(%1) ").arg(priceH));

    BookModel->setFilter(filter);
    BookModel->select();
    qDebug() << BookModel->filter() << endl;
}