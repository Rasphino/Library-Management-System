#ifndef LIBRARY_MANAGEMENT_RETURN_H
#define LIBRARY_MANAGEMENT_RETURN_H

#include <QtWidgets>
#include <QtSql>

class Return : public QWidget {
Q_OBJECT
public:
    explicit Return(QWidget *parent = nullptr);

    ~Return() {};

signals:

public slots:
    void slotDeleteEntry();
    void slotUpdate();

private:
    QTableView *RecordView;
    QSqlQueryModel *RecordModel;
    QPushButton *Button;

};


#endif //LIBRARY_MANAGEMENT_RETURN_H
