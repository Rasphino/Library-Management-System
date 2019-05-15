#ifndef CONTENT
#define CONTENT

#include <QStackedWidget>
#include <QPushButton>
#include "BookQuery.h"
#include "baseinfo.h"
#include "login.h"
#include "CardManagement.h"
#include "Borrow.h"
#include "Return.h"

class Content : public QFrame {
Q_OBJECT

signals:

public slots:
    void slotUpdate();

public:
    explicit Content(QWidget *parent = nullptr);

    ~Content() {};
    QStackedWidget *stack;
    BookQuery *bookQuery;
    BaseInfo *bassInfo;
    Login *login;
    CardManagement *cardManagement;
    Borrow *borrow;
    Return *returnB;
};

#endif
