#include "content.h"
#include "MQListWidget.h"
//#include "BookQuery.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto *splitterMain = new QSplitter(Qt::Horizontal, nullptr);
    splitterMain->setOpaqueResize(true);
    auto *list = new MQListWidget(splitterMain);
    list->insertItem(0, QObject::tr("Book Query"));
    list->insertItem(1, QObject::tr("Admin Login/out"));
    list->insertItem(2, QObject::tr("Library Card Management"));
    list->insertItem(3, QObject::tr("Borrow Management"));
    list->insertItem(4, QObject::tr("Return Management"));
    list->insertItem(5, QObject::tr("Book Management"));
    list->setHideItem(2);
    list->setHideItem(3);
    list->setHideItem(4);
    list->setHideItem(5);


    auto *content = new Content(splitterMain);
    QObject::connect(list,
                     SIGNAL(currentRowChanged(int)),
                     content->stack,
                     SLOT(setCurrentIndex(int))
    );

    QObject::connect(content->login,
                     SIGNAL(loginSuccess()),
                     list,
                     SLOT(slotSwitchHideItemStatus())
    );
    QObject::connect(content->login,
                     SIGNAL(logoutSuccess()),
                     list,
                     SLOT(slotSwitchHideItemStatus())
    );

    splitterMain->setWindowTitle(QObject::tr("Library"));
    splitterMain->setMinimumSize(splitterMain->minimumSize());
    splitterMain->setMaximumSize(splitterMain->maximumSize());
    splitterMain->show();

    return a.exec();
}
