//
// Created by rasp on 19-5-10.
//

#ifndef LIBRARY_MANAGEMENT_READONLYDELEGATE_H
#define LIBRARY_MANAGEMENT_READONLYDELEGATE_H


#include <QtWidgets>

class ReadOnlyDelegate : public QItemDelegate {

Q_OBJECT
public:
    explicit ReadOnlyDelegate(QObject *parent = nullptr)
            : QItemDelegate(parent) {}

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) { return false; }

    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &,
                          const QModelIndex &) const { return Q_NULLPTR; }
};


#endif //LIBRARY_MANAGEMENT_READONLYDELEGATE_H
