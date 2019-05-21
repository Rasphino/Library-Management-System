//
// Created by rasp on 19-4-8.
//

#ifndef DBOPERATION_H
#define DBOPERATION_H

#include <QtSql>
#include <QString>

bool addBook(QSqlQuery &q, const QString &BookType, const QString &BookName,
             const QString &Publisher, int Year, const QString &Author, double Price, int Total,
             int Storage, const QString &UpdateTime);

bool addBook(QSqlQuery &q, const QString &BookType, const QString &BookName,
             const QString &Publisher, int Year, const QString &Author, double Price, int Total,
             int Storage, const QDateTime &UpdateTime);

bool addLibraryCard(QSqlQuery &q, const QString &Name, const QString &Department,
                    const QString &CardType, const QString &UpdateTime);

bool addLibraryRecord(QSqlQuery &q, const QString &CardNo, const QString &BookNo,
                      const QString &LentDate, const QString &ReturnDate, const QString &Operator);

bool addUser(QSqlQuery &q, const QString &Password, const QString &Name, const QString &Contact);

QSqlError initDb();

#endif //BMS_DBOPERATION_H
