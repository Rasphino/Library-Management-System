//
// Created by rasp on 19-5-4.
//

#include "content.h"

Content::Content(QWidget *parent) : QFrame(parent) {
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel);

    bassInfo = new BaseInfo();
    login = new Login();
    stack->addWidget(bassInfo);
    stack->addWidget(login);

//    AmendBtn = new QPushButton(tr("Save"));
//    CloseBtn = new QPushButton(tr("Close"));

//    QHBoxLayout *BtnLayout = new QHBoxLayout;
//    BtnLayout->addStretch(1);
//    BtnLayout->addWidget(AmendBtn);
//    BtnLayout->addWidget(CloseBtn);

    auto *RightLayout = new QVBoxLayout(this);
    RightLayout->setMargin(10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stack);
//    RightLayout->addLayout(BtnLayout);

}