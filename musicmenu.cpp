#include "musicmenu.h"
#include "ui_musicmenu.h"
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QUrl>
#include <QVector>
#include <QDir>
#include <QMessageBox>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSlider>
#include <QFile>
#include <string.h>
#include<QStringList>//歌曲清单


musicMenu::musicMenu(clientSocket *m_clientInfo,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::musicMenu),
    m_clientInfo(m_clientInfo),
    m_complete(new QCompleter(this))

{
    ui->setupUi(this);
    //设置占位符
    ui->searchMusic->setPlaceholderText("搜索音乐");
    QStringList songList;
    songList.push_back("七里香");
    songList.push_back("七子之歌");
    songList.push_back("丑八怪");
    songList.push_back("花海");
    songList.push_back("七色花");
    songList.push_back("花花花");
    songList.push_back("花千骨");

    m_complete=new QCompleter(songList,this);
    //弹出匹配项
    m_complete->setCompletionMode(QCompleter::PopupCompletion);
    //将补全器设置到搜索框
    ui->searchMusic->setCompleter(m_complete);


}
//关闭实现
void musicMenu::closeEvent(QCloseEvent *event)
{
    QMessageBox::information(this,"关闭","关闭窗口");
    //todo... 记录数据

}
musicMenu::~musicMenu()
{
    delete ui;
}
