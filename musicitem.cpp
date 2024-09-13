#include "musicitem.h"
#include "ui_musicitem.h"
#include<QListWidgetItem>
musicItem::musicItem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::musicItem)
{

    ui->setupUi(this);


    QIcon enjoyItemIcon(":/musicimg/enjoy.png");
    ui->enjoy_item->setIcon(enjoyItemIcon);
    ui->enjoy_item->setIconSize(QSize(30, 30));
    ui->enjoy_item->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon downLoadItemIcon(":/musicimg/downLoadBtn.png");
    ui->downLoad_item->setIcon(downLoadItemIcon);
    ui->downLoad_item->setIconSize(QSize(30, 30));
    ui->downLoad_item->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");



}
void musicItem::setMusicName(const QString &musicName)
{
        ui->musicname->setText(musicName);
}
void musicItem::setMusicTime(const QString &setMusicTime)
{
    ui->musicTime->setText(setMusicTime);
}

void musicItem::setSingerName(const QString &setSingerName)
{
    ui->singerName->setText(setSingerName);
}
QString musicItem::getMusicName() const
{
    return ui->musicname->text();
}

musicItem::~musicItem()
{

    delete ui;
}
