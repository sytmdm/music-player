#include "musicplaybackcontrols.h"
#include "ui_musicplaybackcontrols.h"
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
#include "musiclist.h"
#include"musiclist.h"
musicPlaybackControls::musicPlaybackControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::musicPlaybackControls),
    m_player(new QMediaPlayer(this)),
    m_isPlay(false),
    m_currentPlayMode(ORDER_MODE),
    m_timer(new QTimer(this)),
    m_backupLastSongRow(0)
{
    ui->setupUi(this);
    /* 清空哈希表 */
    m_lyricInfo.clear();
    /* 初始化设置头像 */
    setAlbumPic(":/image/8.png");
    /* 设置初始的按钮图标 */
    setInitButtonIcon();

    /* 初始化文件路径 */
    m_musicPath = "D:\\qtObject\\musicPlayer\\music\\";
    loadAppointMusicPath(m_musicPath);

    connect(ui->prevBtn, &QPushButton::clicked, this, &musicPlaybackControls::handlePrevSlot);
    connect(ui->playBtn, &QPushButton::clicked, this, &musicPlaybackControls::handlePlaySlot);
    connect(ui->nextBtn, &QPushButton::clicked, this, &musicPlaybackControls::handleNextSlot);
    connect(ui->switchModeBtn, &QPushButton::clicked, this, &musicPlaybackControls::handleSwitchModeSlot);
    connect(ui->volumeBtn, &QPushButton::clicked, this, &musicPlaybackControls::handleVolumeSlot);
    connect(ui->lyricBtn, &QPushButton::clicked, this, &musicPlaybackControls::handleLyricSlot);
    connect(ui->enjoyBtn, &QPushButton::clicked, this, &musicPlaybackControls::handleEnjoySlot);


    m_backupExitMusic = "七里香.mp3";
    m_player->setMedia(QUrl::fromLocalFile(m_musicPath + m_backupExitMusic));
//    QString m_backupExitMusic = "七里香.lrc";
//    loadAppointLyricPath(m_musicPath + m_backupExitMusic);

    /* 信号和槽 */
    connect(m_player, &QMediaPlayer::durationChanged, this, &musicPlaybackControls::handleDurationSlot);
    connect(m_player, &QMediaPlayer::positionChanged, this, &musicPlaybackControls::handlePositionSlot);
    connect(m_player, &QMediaPlayer::stateChanged, this, &musicPlaybackControls::handleStateChangeSlot);
    connect(ui->processBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
    /* 定时器 */
    m_timer->setInterval(500);
    connect(m_timer, &QTimer::timeout, this, &musicPlaybackControls::handleTimeoutSlot);
}
/* 音乐状态改变 */
void musicPlaybackControls::handleStateChangeSlot()
{
    qDebug() << "state:" << m_player->state() << endl;

    if (m_player->state() == QMediaPlayer::StoppedState && m_player->position() != 0)
    {
        /* 播放下一首 */
        handleNextSlot();
    }
}

/* 播放指定音乐 */
void musicPlaybackControls::startAppointMusic()
{
    if (m_musicList) { // 检查m_musicList是否已经初始化
            QString songName = m_musicList->getMusciSongName();
            /* 加载音乐 */
            QString absPathname = m_musicPath + songName + ".mp3";

            m_player->setMedia(QUrl::fromLocalFile(absPathname));
            qDebug() << "absPathname:" << absPathname << endl;
            // 加载歌词
            loadAppointLyricPath(m_musicPath + songName + ".lrc");

            /* 播放音乐 */
            handlePlaySlot();
        } else {
            qDebug() << "m_musicList is not initialized.";
        }
}
void musicPlaybackControls::loadAppointMusicPath(const QString & filepath)
{
    QDir dir(filepath);

    if (dir.exists() == false)
    {
        QMessageBox::warning(this, "打开文件夹", "文件夹不存在");
        return;
    }

}
/* 处理定时器超时 */
void musicPlaybackControls::handleTimeoutSlot()
{
//    qDebug() << "handleTimeoutSlot" << endl;

    /* 获取当前歌曲的位置 */
    int currentPos = m_player->position();
//    qDebug() << "currentPos:" << currentPos << endl;


    for (auto iter = m_lyricInfo.begin(); iter != m_lyricInfo.end(); iter++)
    {
        int prevPos = iter.key();
        int nextPos = (iter + 1).key();

        if (prevPos < currentPos && currentPos < nextPos)
        {
            ui->lyricLabel->setText(iter.value());
            break;
        }
    }


}


/* 解析时间 */
int musicPlaybackControls::parseTime(const QString & time)
{
    int minutes = time.split(":")[0].toUInt();
    int seconds = time.split(":")[1].split(".")[0].toUInt();
    int millsecond = time.split(".")[1].toUInt();

//    qDebug() << "minutes:" << minutes << "seconds:" << seconds << "millsecond:" << millsecond << endl;

    int totalMills = minutes * 60 * 1000 + seconds * 1000 + millsecond;
    return totalMills;
}
int musicPlaybackControls::musicGetTotalTime(const QString & filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filepath;
        return -1;  // 返回一个负数表示失败
    }

    int maxTime = 0;
    char buffer[128] = {0};
    while (!file.atEnd()) {
        file.readLine(buffer, sizeof(buffer));

        QString lineData(buffer);

        QStringList listInfo = lineData.split("]");
        if (listInfo.size() < 2) continue;  // 忽略不符合格式的行

        QString timeStr = listInfo[0].split("[")[1];
        int lyricTime = parseTime(timeStr);

        if (lyricTime > maxTime) {
            maxTime = lyricTime;
        }
    }

    file.close();
    return maxTime;

}
/* 加载歌词 */
void musicPlaybackControls::loadAppointLyricPath(const QString & filepath)
{
    QFile file(filepath);

    if (file.open(QIODevice::ReadOnly) == false)
    {
        QMessageBox::warning(this, "歌词文件", "文件不存在");
        return;
    }

    char buffer[128] = { 0 };

    while (file.atEnd() != true)
    {
        file.readLine(buffer, sizeof(buffer));

        QString lineData(buffer);

        QStringList listInfo = lineData.split("]");

        /* 将字符串时间转换毫秒 */
        int lyricTime = parseTime(listInfo[0].split("[")[1]);
        QString lyric = listInfo[1];

        /* 插入哈希表 */
        m_lyricInfo[lyricTime] = lyric;
        memset(buffer, 0, sizeof(buffer));
    }

    /* 关闭文件 */
    file.close();
}


void musicPlaybackControls::handlePositionSlot(qint64 position)
{
    int minutes = position / 1000 / 60;
    int seconds = position / 1000 % 60;

    QString formatStr = "%1:%2";
    QString currentTime = formatStr.arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    ui->currentTime->setText(currentTime);
    ui->processBar->setValue(position);
}


/* 处理进度条长度 */
void musicPlaybackControls::handleDurationSlot(qint64 duration)
{
    qDebug() << "duration:" << duration << endl;

    int minutes = duration / 1000 / 60;
    int seconds = duration / 1000 % 60;

    QString formatStr = "%1:%2";
    QString totalTime = formatStr.arg(minutes).arg(seconds);
    ui->totalTime->setText(totalTime);

    /* 更新进度条的最大值 */
    ui->processBar->setRange(0, duration);
}


/* 加载指定音乐🎵路径 */
void musicPlaybackControls::handlePrevSlot()
{
    qDebug() << "handlePrevSlot()" << endl;

    /* 播放列表当前行 */
    int currentRow = m_musicList->getMusicRow();

    /* 使用被记录的上一首歌的行数 */
    int prevRow = m_backupLastSongRow;

    int nextRow = 0;
    if (m_currentPlayMode == ORDER_MODE)            /* 顺序播放 */
    {
        nextRow = (currentRow - 1 +m_musicList->getMusicCount()) % m_musicList->getMusicCount();
    }
    else if (m_currentPlayMode == CYCLE_MODE)       /* 循环播放 */
    {
        nextRow = currentRow;
    }
    else if (m_currentPlayMode == RANDOM_MODE)      /* 随机播放 */
    {
        nextRow = prevRow;
    }

    m_musicList->setMusicRow(nextRow);
}

void musicPlaybackControls::handlePlaySlot()
{
    qDebug() << "handlePlaySlot()" << endl;

    /* 如果歌曲没有播放 */
#if 0
    /* 方案1 */
    if (m_isPlay == false)
    {
        /* 播放音乐 */
        m_player->play();

        ui->playBtn->setIcon(QIcon(":/Icon/puse.png"));
        m_isPlay = true;
    }
    else
    {
        /* 暂停播放 */
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/Icon/play.png"));
        m_isPlay = false;
    }
#else
    /* 方案2 */
    if (m_player->state() == QMediaPlayer::PlayingState)
    {
        /* 暂停播放 */
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/musicimg/player.png"));
        /* 停止定时器 */
        m_timer->stop();
    }
    else
    {
        /* 播放音乐 */
        m_player->play();
        ui->playBtn->setIcon(QIcon(":/musicimg/playBtn.png"));
        /* 启动定时器 */
        m_timer->start();
    }
#endif

}

void musicPlaybackControls::handleNextSlot()
{
    qDebug() << "handleNextSlot()" << endl;

    Q_ASSERT(m_musicList);

    qDebug() << m_musicList << endl;


    /* 播放列表当前行 */
    int currentRow = m_musicList->getMusicRow();

    qDebug() << m_musicList << endl;

    /* 维护上一首歌的行数 */
    m_backupLastSongRow = currentRow;

    int nextRow = 0;
    if (m_currentPlayMode == ORDER_MODE)            /* 顺序播放 */
    {
        nextRow = (currentRow + 1) % m_musicList->getMusicCount();
    }
    else if (m_currentPlayMode == CYCLE_MODE)       /* 循环播放 */
    {
        nextRow = currentRow;
    }
    else if (m_currentPlayMode == RANDOM_MODE)      /* 随机播放 */
    {
        do
        {
            nextRow = qrand() % m_musicList->getMusicCount();
        } while (currentRow == nextRow);
    }

    m_musicList->setMusicRow(nextRow);

    /* 播放指定音乐 */
    startAppointMusic();
}

void musicPlaybackControls::handleSwitchModeSlot()
{
    qDebug() << "handleSwitchModeSlot()" << endl;
    m_currentPlayMode = (m_currentPlayMode + 1) % PLAYMODE_MAX;
    ui->switchModeBtn->setIcon(QIcon(m_modeIcons[m_currentPlayMode]));
}

void musicPlaybackControls::handleVolumeSlot()
{
    qDebug() << "handleVolumeSlot()" << endl;
}

void musicPlaybackControls::handleLyricSlot()
{
    qDebug() << "handleLyricSlot()" << endl;
}

void musicPlaybackControls::handleEnjoySlot()
{
    qDebug() << "handleEnjoySlot()" << endl;
}


void musicPlaybackControls::setAlbumPic(const QPixmap & pixmap)
{
    ui->albumLabel->setPixmap(pixmap.scaled(ui->albumLabel->width(), ui->albumLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void musicPlaybackControls::setAlbumPic(const QString & picfilename)
{
    QPixmap headPic(picfilename);
    setAlbumPic(headPic);
}


/* 设置初始的按钮图标 */
void musicPlaybackControls::setInitButtonIcon()
{
    QIcon prevIcon(":/musicimg/25prve.png");
    ui->prevBtn->setIcon(prevIcon);
    /* 将图标的大小适配按钮本身大小 */
    ui->prevBtn->setIconSize(QSize(30, 30));
    /* 样式表 */
    ui->prevBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon playIcon(":/musicimg/player.png");
    ui->playBtn->setIcon(playIcon);
    /* 将图标的大小适配按钮本身大小 */
    ui->playBtn->setIconSize(QSize(30, 30));
    ui->playBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon nextIcon(":/musicimg/next.png");
    ui->nextBtn->setIcon(nextIcon);
    /* 将图标的大小适配按钮本身大小 */
    ui->nextBtn->setIconSize(QSize(30, 30));
    ui->nextBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon modeIcon(":/musicimg/switchMode1.png");
    ui->switchModeBtn->setIcon(modeIcon);
    /* 将图标的大小适配按钮本身大小 */
    ui->switchModeBtn->setIconSize(QSize(30, 30));
    ui->switchModeBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon volumeIcon(":/musicimg/volumeCloseBtn.png");
    ui->volumeBtn->setIcon(volumeIcon);
    ui->volumeBtn->setIconSize(QSize(30, 30));
    ui->volumeBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon lyricIcon(":/musicimg/gost.png");
    ui->lyricBtn->setIcon(lyricIcon);
    ui->lyricBtn->setIconSize(QSize(30, 30));
    ui->lyricBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");

    QIcon collectIcon(":/musicimg/enjoy.png");
    ui->enjoyBtn->setIcon(collectIcon);
    ui->enjoyBtn->setIconSize(QSize(30, 30));
    ui->enjoyBtn->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); }");




    /* 切换模式图标 */
    m_modeIcons.push_back(":/musicimg/switchMode1.png");
    m_modeIcons.push_back(":/musicimg/switchMode.png");
    m_modeIcons.push_back(":/musicimg/switchMode2.png");
}

musicPlaybackControls::~musicPlaybackControls()
{
    delete ui;

}
