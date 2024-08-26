#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QMainWindow>
#include"musicitem.h"
#include<QWidget>
#include"musicplaybackcontrols.h"
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
    QString getMusciSongName();
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
