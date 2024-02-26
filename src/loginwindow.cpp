#include "loginwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel *loginLabel = new QLabel("Логин:", this);
    QLineEdit *loginEdit = new QLineEdit(this);

    QLabel *passwordLabel = new QLabel("Пароль:", this);
    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Вход", this);

    QGridLayout *loginLayout = new QGridLayout;
    loginLayout->addWidget(new QLabel(""), 0, 0);      
    loginLayout->addWidget(new QLabel(""), 1, 0);
    loginLayout->addWidget(new QLabel(""), 2, 0);      
    loginLayout->addWidget(new QLabel(""), 3, 0);  
    loginLayout->addWidget(new QLabel(""), 4, 0);      
    loginLayout->addWidget(new QLabel(""), 5, 0);
    loginLayout->addWidget(new QLabel(""), 6, 0);      
    loginLayout->addWidget(new QLabel(""), 7, 0);
    loginLayout->addWidget(new QLabel(""), 8, 0);      
    loginLayout->addWidget(new QLabel(""), 9, 0);
    loginLayout->addWidget(new QLabel(""), 10, 0);      
    loginLayout->addWidget(new QLabel(""), 11, 0);  
    loginLayout->addWidget(new QLabel(""), 12, 0);      
    loginLayout->addWidget(new QLabel(""), 13, 0);
    loginLayout->addWidget(new QLabel(""), 14, 0);
    loginLayout->addWidget(new QLabel("Авторизвция"), 14, 1);      
    loginLayout->addWidget(new QLabel(""), 15, 0);        
    loginLayout->addWidget(loginLabel, 16, 0);          
    loginLayout->addWidget(loginEdit, 16, 1);  
    loginLayout->addWidget(passwordLabel, 17, 0);       
    loginLayout->addWidget(passwordEdit, 17, 1);
    loginLayout->addWidget(loginButton, 18, 0, 1, 2);


    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap("../src/grafic/foto/zxc.png"));
    imageLabel->setScaledContents(true); 
    imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding); 

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(imageLabel, 0, 0);
    mainLayout->addLayout(loginLayout, 0, 1);

    loginLayout->setVerticalSpacing(5);
    loginLayout->setHorizontalSpacing(5);

    loginLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    loginLayout->setRowMinimumHeight(3, 20);
    mainLayout->setColumnStretch(0, 1); 
    mainLayout->setColumnStretch(1, 3);

    setLayout(mainLayout);
}

LoginWindow::~LoginWindow()
{
}