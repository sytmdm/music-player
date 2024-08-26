#ifndef MUSICPLAYBACKCONTROLS_H
#define MUSICPLAYBACKCONTROLS_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVector>
#include <QString>
#include <QMap>
#include <QTimer>       /* 定时器 */
#include<QCompleter>   //补全
#include"clientsocket.h"
#include<QCloseEvent>
#include"musiclist.h"
class musicList;
namespace Ui {
class musicPlaybackControls;
}
enum PLAYMODE
{
    ORDER_MODE,
    CYCLE_MODE,
    RANDOM_MODE,
    PLAYMODE_MAX,
};

class musicPlaybackControls : public QWidget
{
    Q_OBJECT

public:
    explicit musicPlaybackControls(QWidget *parent = nullptr);
    ~musicPlaybackControls();
public slots:
    void handlePrevSlot();
    void handlePlaySlot();
    void handleNextSlot();
    void handleSwitchModeSlot();
    void handleVolumeSlot();
    void handleLyricSlot();
    void handleEnjoySlot();

    /* 处理进度条长度 */
    void handleDurationSlot(qint64 duration);
    /* 处理进度条的进度 */
    void handlePositionSlot(qint64 position);
    /* 处理定时器超时 */
    void handleTimeoutSlot();
    /* 音乐状态改变 */
    void handleStateChangeSlot();
    /* 加载指定音乐🎵路径 */
    void loadAppointMusicPath(const QString & filepath);
    /* 播放指定音乐 */
    void startAppointMusic();
    //加载音乐歌词
    void loadAppointLyricPath(const QString & filepath);
    void setAlbumPic(const QPixmap & pixmap);
    void setAlbumPic(const QString & picfilename);
    //获取时间
    int musicGetTotalTime(const QString & filepath);
private:
    /* 设置初始的按钮图标 */
    void setInitButtonIcon();
    /* 解析时间 */
    int parseTime(const QString & time);
private:
    Ui::musicPlaybackControls *ui;
    QMediaPlayer * m_player;

    /* 是否正在播放 */
    bool m_isPlay;

    /* 当前播放模式 */
    int m_currentPlayMode;
    /* 切换模式的图标 */
    QVector<QString> m_modeIcons;

    /* 文件夹路径 */
    QString m_musicPath;

    /* 保留上一次程序退出的歌曲名 */
    QString m_backupExitMusic;

    /* 歌词信息 <时间:歌词> */
    QMap<quint32, QString> m_lyricInfo;

    /* 定时器 - 检测positon位置的歌词 */
    QTimer * m_timer;
    /* 维护上一首歌在歌曲的行数 todo... 验收项目考核之一. */
    int m_backupLastSongRow;
    musicList *m_musicList;
};

#endif // MUSICPLAYBACKCONTROLS_H
