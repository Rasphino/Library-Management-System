#include "content.h"
#include "MQListWidget.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto *splitterMain = new QSplitter(Qt::Horizontal, 0);
    splitterMain->setOpaqueResize(true);
    auto *list = new MQListWidget(splitterMain);
    list->insertItem(0, QObject::tr("Base Info"));
    list->insertItem(1, QObject::tr("Admin Login/out"));
    list->insertItem(2, QObject::tr("License Manage"));
    list->setHideItem(2);
    list->item(2)->setFlags(list->item(2)->flags() & ~Qt::ItemIsEnabled);


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