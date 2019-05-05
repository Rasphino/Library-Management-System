#include "content.h"

Content::Content(QWidget *parent) : QFrame(parent) {
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel);

    bookQuery = new BookQuery;
    bassInfo = new BaseInfo;
    login = new Login;
    stack->addWidget(bookQuery);
    stack->addWidget(login);
    stack->addWidget(bassInfo);
    stack->addWidget(bassInfo);

    auto *RightLayout = new QVBoxLayout(this);
    RightLayout->setMargin(10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stack);

}