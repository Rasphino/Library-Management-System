#ifndef LIBRARY_MANAGEMENT_LOGIN_H
#define LIBRARY_MANAGEMENT_LOGIN_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class Login : public QWidget {
Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);

    ~Login() {};

signals:
    void loginSuccess();
    void logoutSuccess();

public slots:
    void slotClear();
    void slotAcceptLogin();
    void slotLogout();


private:
    QLabel *UserNameLabel;
    QLineEdit *UserNameLineEdit;
    QLabel *PasswdLabel;
    QLineEdit *PasswdLineEdit;
    QDialogButtonBox *Buttons;
    QLabel *LoginInfoLabel;

    bool checkLoginInfo(const QString &username, const QString &passwd);

};


#endif //LIBRARY_MANAGEMENT_LOGIN_H
