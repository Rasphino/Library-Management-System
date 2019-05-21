#include "DBOperation.h"

QLatin1String createBooksSql(
        "create table Books(\n"
        "\tBookNo serial,\n"
        "\tBookType varchar(50),\n"
        "\tBookName varchar(50),\n"
        "\tPublisher varchar(50),\n"
        "\tYear integer,\n"
        "\tAuthor varchar(50),\n"
        "\tPrice money,\n"
        "\tTotal integer,\n"
        "\tStorage integer,\n"
        "\tUpdateTime timestamp,\n"
        "\tprimary key (BookNo)\n"
        ");");

QLatin1String createLibraryCardSQL(
        "create table LibraryCard(\n"
        "\tCardNo serial,\n"
        "\tName varchar(50),\n"
        "\tDepartment varchar(50),\n"
        "\tCardType varchar(50),\n"
        "\tUpdateTime timestamp,\n"
        "\tprimary key (CardNo)\n"
        ");");

QLatin1String createUsersSQL(
        "create table Users(\n"
        "\tUserID serial,\n"
        "\tPassword varchar(50),\n"
        "\tName varchar(50),\n"
        "\tContact varchar(50),\n"
        "\tprimary key (UserID)\n"
        ");");

QLatin1String createLibraryRecord(
        "create table LibraryRecords(\n"
        "\tFID serial,\n"
        "\tCardNo integer,\n"
        "\tBookNo integer,\n"
        "\tLentDate timestamp,\n"
        "\tReturnDate timestamp,\n"
        "\tOperator varchar(50),\n"
        "\tprimary key (FID),\n"
        "\tforeign key (CardNo) references LibraryCard,\n"
        "\tforeign key (BookNo) references Books\n"
        ");");

bool addBook(QSqlQuery &q, const QString &BookType, const QString &BookName,
             const QString &Publisher, int Year, const QString &Author, double Price, int Total,
             int Storage, const QString &UpdateTime) {
    q.addBindValue(BookType);
    q.addBindValue(BookName);
    q.addBindValue(Publisher);
    q.addBindValue(Year);
    q.addBindValue(Author);
    q.addBindValue(Price);
    q.addBindValue(Total);
    q.addBindValue(Storage);
    q.addBindValue(UpdateTime);
    return q.exec();
}

bool addBook(QSqlQuery &q, const QString &BookType, const QString &BookName,
             const QString &Publisher, int Year, const QString &Author, double Price, int Total,
             int Storage, const QDateTime &UpdateTime) {
    q.addBindValue(BookType);
    q.addBindValue(BookName);
    q.addBindValue(Publisher);
    q.addBindValue(Year);
    q.addBindValue(Author);
    q.addBindValue(Price);
    q.addBindValue(Total);
    q.addBindValue(Storage);
    q.addBindValue(UpdateTime);
    return q.exec();
}

bool addLibraryCard(QSqlQuery &q, const QString &Name, const QString &Department,
                    const QString &CardType, const QString &UpdateTime) {
    q.addBindValue(Name);
    q.addBindValue(Department);
    q.addBindValue(CardType);
    q.addBindValue(UpdateTime);
    return q.exec();
}

bool addLibraryRecord(QSqlQuery &q, const QString &CardNo, const QString &BookNo,
                      const QString &LentDate, const QString &ReturnDate, const QString &Operator) {
    q.addBindValue(CardNo);
    q.addBindValue(BookNo);
    q.addBindValue(LentDate);
    q.addBindValue(ReturnDate);
    q.addBindValue(Operator);
    return q.exec();
}


bool addUser(QSqlQuery &q, const QString &Password, const QString &Name, const QString &Contact) {
    q.addBindValue(Password);
    q.addBindValue(Name);
    q.addBindValue(Contact);
    return q.exec();
}

QSqlError initDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("book");
    db.setUserName("rasp");
    db.setPassword("");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("Books", Qt::CaseInsensitive)
        && tables.contains("librarycard", Qt::CaseInsensitive)
        && tables.contains("users", Qt::CaseInsensitive)
        && tables.contains("libraryrecords", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(createBooksSql))
        return q.lastError();
    if (!q.exec(createLibraryCardSQL))
        return q.lastError();
    if (!q.exec(createUsersSQL))
        return q.lastError();
    if (!q.exec(createLibraryRecord))
        return q.lastError();

    if (!q.prepare(QLatin1String(
            "insert into users(password, name, contact) "
            "VALUES (?, ?, ?);")))
        qDebug() << q.lastError();
    addUser(q, "123456", "admin", "");

    if (!q.prepare(QLatin1String(
            "insert into librarycard(name, department, cardtype, updatetime) "
            "VALUES (?, ?, ?, ?);")))
        qDebug() << q.lastError();
    addLibraryCard(q, "张鑫", "ckc", "normal", "2019-04-08 00:00:00");
    addLibraryCard(q, "张驰", "pku", "normal", "2018-04-08 00:00:00");

    if (!q.prepare(QLatin1String(
            "insert into books(BookType, BookName, Publisher, Year, "
            "Author, Price, Total, Storage, UpdateTime) "
            "values(?, ?, ?, ?, ?, ?, ?, ?, ?);")))
        qDebug() << q.lastError();
    addBook(q, "小说", "三体", "unknown", 1984, "lcx", 49.8, 4, 2, "2012-01-08 04:05:06");
    addBook(q, "小说", "活着", "", 2002, "余华", 24.1, 20, 19, "2016-06-21 12:00:01");
    addBook(q, "教辅", "五年高考三年模拟", "", 2019, "?", 43, 20, 0, "2019-04-03 18:23:49");

    if (!q.prepare(QLatin1String(
            "insert into libraryRecords( cardno, bookno, lentdate, returndate, operator) "
            "VALUES ( ?, ?, ?, ?, ?);")))
        qDebug() << q.lastError();
    addLibraryRecord(q, "0001", "2000", "1999-01-01 01:00:00", "now", "001");

    return QSqlError();
}