#ifndef MUSICMENU_H
#define MUSICMENU_H

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
namespace Ui {
class musicMenu;
}


enum PLAYMODE
{
    ORDER_MODE,
    CYCLE_MODE,
    RANDOM_MODE,
    PLAYMODE_MAX,
};

class musicMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit musicMenu( clientSocket *m_clientInfo,QWidget *parent = nullptr);
    ~musicMenu();
protected:
    void closeEvent(QCloseEvent *event) override;
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
public:
    void setAlbumPic(const QPixmap & pixmap);
    void setAlbumPic(const QString & picfilename);

    /* 加载指定音乐🎵路径 */
    void loadAppointMusicPath(const QString & filepath);
    /* 加载歌词 */
    void loadAppointLyricPath(const QString & filepath);

    /* 播放指定音乐 */
    void startAppointMusic();
    //点击跳转功能
    void handleItemClicked();

private:
    /* 设置初始的按钮图标 */
    void setInitButtonIcon();
    /* 解析时间 */
    int parseTime(const QString & time);
private:
    Ui::musicMenu *ui;
    QMediaPlayer * m_player;

    /* 是否正在播放 */
    bool m_isPlay;

    /* 当前播放模式 */
    int m_currentPlayMode;
    /* 切换模式的图标 */
    QVector<QString> m_modeIcons;

    /* 维护上一首歌在歌曲的行数 todo... 验收项目考核之一. */
    int m_backupLastSongRow;
    /* 当前播放音乐在歌单里面是哪一行 */
    int m_currentSongRow;
    /* 文件夹路径 */
    QString m_musicPath;

    /* 保留上一次程序退出的歌曲名 */
    QString m_backupExitMusic;

    /* 歌词信息 <时间:歌词> */
    QMap<quint32, QString> m_lyricInfo;

    /* 定时器 - 检测positon位置的歌词 */
    QTimer * m_timer;
    //搜索框补全
    QCompleter * m_complete;
    //通信
    clientSocket *m_clientInfo;
};

#endif // MUSICMENU_H
