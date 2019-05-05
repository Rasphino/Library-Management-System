#ifndef CONTENT
#define CONTENT

#include <QStackedWidget>
#include <QPushButton>
#include "BookQuery.h"
#include "baseinfo.h"
#include "login.h"

class Content : public QFrame {
Q_OBJECT
public:
    explicit Content(QWidget *parent = nullptr);

    ~Content() {};
    QStackedWidget *stack;
    BookQuery *bookQuery;
    BaseInfo *bassInfo;
    Login *login;

};

#endif
