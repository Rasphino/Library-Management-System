#include <QtSql>
#include "Login.h"

QString Login::User;

Login::Login(QWidget *parent) : QWidget(parent) {
    UserNameLabel = new QLabel(tr("Username: "));
    UserNameLineEdit = new QLineEdit("admin");
    PasswdLabel = new QLabel(tr("Password: "));
    PasswdLineEdit = new QLineEdit;
    PasswdLineEdit->setEchoMode(QLineEdit::Password);
    LoginInfoLabel = new QLabel();

    Buttons = new QDialogButtonBox(this);
    Buttons->addButton(QDialogButtonBox::Ok);
    Buttons->addButton(QDialogButtonBox::Cancel);
    Buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
    Buttons->button(QDialogButtonBox::Cancel)->setText(tr("Clear"));

    connect(Buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (slotClear())
    );

    connect(Buttons->button(QDialogButtonBox::Ok),
            SIGNAL (clicked()),
            this,
            SLOT (slotAcceptLogin())
    );

    auto *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(UserNameLabel, 0, 0);
    mainLayout->addWidget(UserNameLineEdit, 0, 1);
    mainLayout->addWidget(PasswdLabel, 1, 0);
    mainLayout->addWidget(PasswdLineEdit, 1, 1);
    mainLayout->addWidget(LoginInfoLabel, 2, 1);
    mainLayout->addWidget(Buttons, 3, 1);

}

void Login::slotClear() {
    UserNameLineEdit->clear();
    PasswdLineEdit->clear();
    LoginInfoLabel->setText("");
}

void Login::slotLogout() {
    disconnect(Buttons->button(QDialogButtonBox::Ok),
               SIGNAL (clicked()),
               this,
               SLOT (slotLogout())
    );

    connect(Buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (slotClear())
    );

    connect(Buttons->button(QDialogButtonBox::Ok),
            SIGNAL (clicked()),
            this,
            SLOT (slotAcceptLogin())
    );
    UserNameLabel->show();
    UserNameLineEdit->show();
    PasswdLabel->show();
    PasswdLineEdit->show();
    Buttons->button(QDialogButtonBox::Cancel)->show();
    Buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
    LoginInfoLabel->setText("");
    slotClear();
    emit logoutSuccess();
    User = "";
}

void Login::slotAcceptLogin() {
    QString username = UserNameLineEdit->text();
    QString password = PasswdLineEdit->text();
    if (checkLoginInfo(username, password)) {
        UserNameLabel->hide();
        UserNameLineEdit->hide();
        PasswdLabel->hide();
        PasswdLineEdit->hide();
        Buttons->button(QDialogButtonBox::Cancel)->hide();
        LoginInfoLabel->setText(tr("Welcome, %1!").arg(username));
        disconnect(Buttons->button(QDialogButtonBox::Ok),
                   SIGNAL (clicked()),
                   this,
                   SLOT (slotAcceptLogin())
        );
        disconnect(Buttons->button(QDialogButtonBox::Cancel),
                   SIGNAL (clicked()),
                   this,
                   SLOT (slotClear())
        );
        Buttons->button(QDialogButtonBox::Ok)->setText(tr("Logout"));
        connect(Buttons->button(QDialogButtonBox::Ok),
                SIGNAL (clicked()),
                this,
                SLOT (slotLogout())
        );
        emit loginSuccess();
        User = username;
    } else {
        LoginInfoLabel->setText(tr("Login failed!"));
    }
}

bool Login::checkLoginInfo(const QString &username, const QString &passwd) {
    QSqlQueryModel model;
    if (username.isEmpty()) return false;
    model.setQuery(QString("SELECT password FROM users WHERE name='%1'").arg(username));
    if (model.record().isEmpty()) return false;
    QString _passwd = model.record(0).value(0).toString();
    return passwd == _passwd;
}
