#include "onlineplayer.h"
#include<QMediaPlayer>
#include<QMediaContent>
#include<QString>
#include<QFile>
#include<QFileInfo>
#include<QBuffer>
onLinePlayer::onLinePlayer(QObject *parent) : QObject(parent)
{
    qDebug() << "来了来了来了" << endl;


        player = new QMediaPlayer(this);

        connect(player, &QMediaPlayer::positionChanged, this, &onLinePlayer::testSlot);
        QString musicPath = "D:\\qtObject\\musicPlayer\\music\\花海.mp3";
        /* 音乐路径 */
        QFileInfo checkInfo(musicPath);
        if (checkInfo.exists() == false)
        {
            qDebug() << "文件不存在" << musicPath << endl;
        }

        QFile file(musicPath);
        if (file.open(QIODevice::ReadOnly) == false)
        {
            qDebug() << "open QIODevice::ReadOnly" << endl;
        }

        /* 音乐数据 */
        QByteArray audioData = file.readAll();
        /* 关闭文件 */
        file.close();

    #if 1
        /* 创建一个QBuffer缓冲区 */
        QBuffer * buffer = new QBuffer(this);
        buffer->setData(audioData);

        if (buffer->open(QIODevice::ReadOnly) == false)
        {
            qDebug() << "无法打开缓冲区" << endl;
        }

    #endif
//        player->setMedia(QMediaContent(), buffer);

        QMediaContent mediaContent(QUrl::fromLocalFile(musicPath));
        player->setMedia(mediaContent, buffer);

        /* 播放音乐 */
        player->play();
        /* 设置音乐 */
//        player->setVolume(100);
}

void onLinePlayer::testSlot()
{
    qDebug() << player->position() << endl;
}
