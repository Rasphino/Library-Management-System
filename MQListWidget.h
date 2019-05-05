//
// Created by rasp on 19-5-5.
//

#ifndef LIBRARY_MANAGEMENT_MQLISTWIDGET_H
#define LIBRARY_MANAGEMENT_MQLISTWIDGET_H

#include <QtWidgets>
#include <vector>

class MQListWidget : public QListWidget {
Q_OBJECT

public:
    explicit MQListWidget(QWidget *parent = nullptr) : QListWidget(parent) {}

    ~MQListWidget() {}

    void setHideItem(int idx) {
        this->hideItemIdx.push_back(idx);
    }

public slots:

    void slotSwitchHideItemStatus() {
        for (const auto &idx : hideItemIdx) {
            if ((this->item(idx)->flags() & Qt::ItemIsEnabled) == 0)
                this->item(idx)->setFlags(this->item(idx)->flags() | Qt::ItemIsEnabled);
            else
                this->item(idx)->setFlags(this->item(idx)->flags() & ~Qt::ItemIsEnabled);
        }
    }

private:
    std::vector<int> hideItemIdx;

};


#endif //LIBRARY_MANAGEMENT_MQLISTWIDGET_H
