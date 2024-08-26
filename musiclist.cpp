#include "musiclist.h"
#include "ui_musiclist.h"
#include<QMessageBox>
#include<QFileInfoList>
#include"musicitem.h"
#include<QDir>
#include<QString>
musicList::musicList(QWidget *parent) :
    QWidget(parent),
    m_currentSongRow(0),
    m_playBackControls(nullptr),
    ui(new Ui::musicList)
{
    ui->setupUi(this);

    /* 初始化文件路径 */
    m_musicPath = "D:\\qtObject\\musicPlayer\\music\\";
    handleItemInit(m_musicPath);

}

QString musicList::getMusciSongName()
{
    return ui->m_musicList->currentItem()->text();
}
void musicList::setMusicRow(int nextRow)
{
    ui->m_musicList->setCurrentRow(nextRow);
}
int musicList::getMusicCount()
{
    return ui->m_musicList->count();
}
int musicList::getMusicRow()
{
    return ui->m_musicList->currentRow();
}
void musicList::handleItemInit(const QString &filePath)
{
    QDir dir(filePath);
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files);
    /* 循环查找 */
    for (const QFileInfo & info : fileInfo)
    {
        /* 后缀 */
        if (info.suffix() == "mp3")
        {
            // 创建一个QListWidgetItem
            musicItem *item = new musicItem(this);
            item->setMusicName(info.baseName());
            int time=m_playBackControls->musicGetTotalTime(info.baseName());
            // 检查time是否有效
            if (time >= 0) {
                // 将时间转换为字符串
                QString totalTime = QString::number(time);
                // 调用setMusicTime方法
                item->setMusicTime(totalTime);
            } else {
                // 处理无效的时间值
                qDebug() << "Invalid time value:" << time;}
                // 创建一个QListWidgetItem
                QListWidgetItem *listItem = new QListWidgetItem(ui->m_musicList);
                // 设置列表项的大小提示
                listItem->setSizeHint(item->sizeHint());  // 确保item有正确的sizeHint实现
                ui->m_musicList->setItemWidget(listItem,item);

        }
    }
}
void musicList::handleItemClicked()
{
    // 获取当前点击的行号
    m_currentSongRow = ui->m_musicList->currentRow();
    QString songName = ui->m_musicList->currentItem()->text();
    // 根据行号播放对应的音乐文件
    m_playBackControls->startAppointMusic();
}


musicList::~musicList()
{
    delete ui;


}
