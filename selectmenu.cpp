#include "selectmenu.h"
#include "ui_selectmenu.h"
#include <QDebug>

selectMenu::selectMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectMenu)
{
    ui->setupUi(this);

    /* 设置初始的按钮图标 */
    setInitButtonIcon();

    connect(ui->localBtn, &QPushButton::clicked, this, &selectMenu::OnLocalSlot);
    connect(ui->onlineBtn, &QPushButton::clicked, this, &selectMenu::OnOnlineSlot);
    connect(ui->collectionBtn, &QPushButton::clicked, this, &selectMenu::OnCollectionSlot);
}


/* 设置初始的按钮图标 */
void selectMenu::setInitButtonIcon()
{
    ui->localBtn->setStyleSheet(
                "QPushButton { border: none; background-color: transparent; }"
                 "QPushButton:hover { background-color: rgba(100, 100, 100, 0.2); }"
                );
    ui->onlineBtn->setStyleSheet(
                "QPushButton { border: none; background-color: transparent; }"
                 "QPushButton:hover { background-color: rgba(100, 100, 100, 0.2); }"
                );
    ui->collectionBtn->setStyleSheet(
                "QPushButton { border: none; background-color: transparent; }"
                 "QPushButton:hover { background-color: rgba(100, 100, 100, 0.2); }"
                );
}

void selectMenu::OnLocalSlot()
{
    qDebug() << "OnLocalSlot" << endl;
}

void selectMenu::OnOnlineSlot()
{
    qDebug() << "OnOnlineSlot" << endl;
}

void selectMenu::OnCollectionSlot()
{
    qDebug() << "OnCollectionSlot" << endl;
}

selectMenu::~selectMenu()
{
    delete ui;
}
