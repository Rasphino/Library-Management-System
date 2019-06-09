#include "Content.h"

Content::Content(QWidget *parent) : QFrame(parent) {
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel);

    bookQuery = new BookQuery;
    login = new Login;
    cardManagement = new CardManagement;
    borrow = new Borrow;
    returnB = new Return;
    book = new Book;

    stack->addWidget(bookQuery);
    stack->addWidget(login);
    stack->addWidget(cardManagement);
    stack->addWidget(borrow);
    stack->addWidget(returnB);
    stack->addWidget(book);

    connect(stack,
            SIGNAL(currentChanged(int)),
            this,
            SLOT(slotUpdate())
    );

    auto *RightLayout = new QVBoxLayout(this);
    RightLayout->setMargin(10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stack);

}

void Content::slotUpdate() {
    bookQuery->slotUpdate();
    borrow->slotUpdate();
    returnB->slotUpdate();
    book->slotUpdate();
}
