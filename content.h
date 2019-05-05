#ifndef CONTENT
#define CONTENT

#include <QStackedWidget>
#include <QPushButton>
#include "baseinfo.h"
#include "login.h"

class Content : public QFrame {
Q_OBJECT
public:
    explicit Content(QWidget *parent = nullptr);

    ~Content() {};
    QStackedWidget *stack;
//    QPushButton *AmendBtn;
//    QPushButton *CloseBtn;
    BaseInfo *bassInfo;
    Login *login;

};

#endif
