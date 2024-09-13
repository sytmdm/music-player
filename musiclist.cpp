#include "musiclist.h"
#include "ui_musiclist.h"
#include <QMessageBox>
#include <QFileInfoList>
#include "musicitem.h"
#include <QDir>
#include <QString>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaMetaData>
musicList::musicList(QWidget *parent) : QWidget(parent),
                                        m_currentSongRow(0),
                                        m_playBackControls(nullptr),
                                        ui(new Ui::musicList)
{
    ui->setupUi(this);

    /* 初始化文件路径 */
    m_musicPath = ":/music/";
    handleItemInit(m_musicPath);
}

QString musicList::getMusciSongName()
{

    QListWidgetItem *listItem = ui->m_musicList->item(getMusicRow());
    if (listItem)
    {
        item1 = qobject_cast<musicItem *>(ui->m_musicList->itemWidget(listItem));
        if (item1)
        {
            return item1->getMusicName();
        }
    }
    return QString();
}
void musicList::setMusicRow(int nextRow)
{
    ui->m_musicList->setCurrentRow(nextRow);
    qDebug() << "nextRow:" << nextRow << endl;
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
#if 0
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
            int time=musicGetTotalTime(info.baseName());
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
#endif
    QDir rootDir(filePath);

    // 获取所有艺术家的文件夹
    QFileInfoList artistFolders = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    // 遍历每个艺术家的文件夹
    foreach (const QFileInfo &artistFolderInfo, artistFolders)
    {
        QString artistName = artistFolderInfo.fileName(); // 艺术家名 = 文件夹名

        // 获取该文件夹中的所有音乐文件
        QDir artistDir(artistFolderInfo.absoluteFilePath());
        QStringList musicFiles = artistDir.entryList(QStringList() << "*.mp3" << "*.wav" << "*.flac", QDir::Files);

        foreach (const QString &musicFile, musicFiles)
        {
            QString filePath = artistDir.absoluteFilePath(musicFile);
            qint64 duration = getMusicDuration(filePath);

            qDebug() << "absoluteFilePath:" << filePath << endl;
            // 获取文件名（不包括扩展名）
            QFileInfo fileIf(filePath);

            musicItem *specialItem = new musicItem();
            specialItem->setMusicName(fileIf.completeBaseName());
            specialItem->setSingerName(artistName);
            specialItem->setMusicTime(millTimeToMinuteTimeStr(duration));
            insertSongItem(specialItem);

            /* 歌单匹配列表 */
            filePath.push_back(fileIf.completeBaseName());
        }
    }
}
/* 添加歌单 */
void musicList::insertSongItem(musicItem *item)
{
    // 创建一个QListWidgetItem对象
    QListWidgetItem *listItem = new QListWidgetItem(ui->m_musicList);

    // 设置QListWidgetItem的尺寸
    listItem->setSizeHint(item->sizeHint());

    // 将musicItem对象作为listItem的显示部件
    ui->m_musicList->setItemWidget(listItem, item);

    // 将listItem添加到listWidget中
    ui->m_musicList->addItem(listItem);
}
// 获取音乐文件时长的辅助函数
qint64 musicList::getMusicDuration(const QString &filePath)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(filePath));

    QEventLoop loop;
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, &loop, [&](QMediaPlayer::MediaStatus status)
                     {
        if (status == QMediaPlayer::LoadedMedia) {
            loop.quit();
        } });
    loop.exec();

    qint64 duration = player->duration();
    delete player;
    return duration;
}
/* 将毫秒转化为分数字符串 */
QString musicList::millTimeToMinuteTimeStr(qint64 millSeconds)
{
    int minutes = millSeconds / 1000 / 60;
    int seconds = millSeconds / 1000 % 60;

    QString formatStr = "%1:%2";
    QString currentTime = formatStr.arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

    return currentTime;
}
// int musicList::musicGetTotalTime(const QString & filepath)
//{
//     QFile file(filepath);

//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "Failed to open file:" << filepath;
//        return -1;  // 返回一个负数表示失败
//    }

//    int maxTime = 0;
//    char buffer[128] = {0};
//    while (!file.atEnd()) {
//        file.readLine(buffer, sizeof(buffer));

//        QString lineData(buffer);

//        QStringList listInfo = lineData.split("]");
//        if (listInfo.size() < 2) continue;  // 忽略不符合格式的行

//        QString timeStr = listInfo[0].split("[")[1];
//        int lyricTime = parseTime(timeStr);

//        if (lyricTime > maxTime) {
//            maxTime = lyricTime;
//        }
//    }

//    file.close();
//    return maxTime;
//}
void musicList::handleItemClicked()
{
    // 获取当前点击的行号
    m_currentSongRow = ui->m_musicList->currentRow();
    QString songName = ui->m_musicList->currentItem()->text();
    // 根据行号播放对应的音乐文件
    // m_playBackControls->startAppointMusic();
}

musicList::~musicList()
{
    delete ui;
}
