#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QMainWindow>
#include"musicitem.h"
#include<QWidget>
#include <QDebug>
class musicPlaybackControls;
namespace Ui {
class musicList;
}

class musicList : public QWidget
{
    Q_OBJECT

public:
    explicit musicList(QWidget *parent = nullptr);
    ~musicList();
public:
    //点击跳转功能
    void handleItemClicked();
    void startAppointMusic();
    //元素初始化
    void handleItemInit(const QString &filePath);
    int getMusicCount();
    int getMusicRow();
    void setMusicRow(int nextRow);
    QString millTimeToMinuteTimeStr(qint64 millSeconds);
    void insertSongItem(musicItem * item);
    QString getMusciSongName();

    //获取时间
    int musicGetTotalTime(const QString & filepath);
private:
    /* 解析时间 */
    int parseTime(const QString & time);
    qint64 getMusicDuration(const QString &filePath);
private:
    musicItem *item1;
    /* 当前播放音乐在歌单里面是哪一行 */
    int m_currentSongRow;
    /* 文件夹路径 */
    QString m_musicPath;

    musicPlaybackControls *m_playBackControls;
    Ui::musicList *ui;
};

#endif // MUSICLIST_H
