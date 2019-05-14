#ifndef LIBRARY_MANAGEMENT_CARDMANAGEMENT_H
#define LIBRARY_MANAGEMENT_CARDMANAGEMENT_H

#include <QtWidgets>
#include <QtSql>

class CardManagement : public QWidget {
Q_OBJECT
public:
    explicit CardManagement(QWidget *parent = nullptr);

    ~CardManagement() {}


signals:

public slots:
    void slotDeleteEntry();
    void slotAddEntry();
    void slotCommit();
    void slotReset();

private:
    QTableView *CardView;
    QSqlRelationalTableModel *CardModel;
    QDialogButtonBox *Buttons;
    QDialogButtonBox *CommitButtons;

    QLabel *NameLabel;
    QLabel *DepartmentLabel;
    QLabel *CardTypeLabel;
    QLabel *InfoLabel;

    QLineEdit *NameLineEdit;
    QLineEdit *DepartmentLineEdit;
    QLineEdit *CardTypeLineEdit;
};


#endif //LIBRARY_MANAGEMENT_CARDMANAGEMENT_H
