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
#include"musicplaybackcontrols.h"
#include "musiclist.h"
namespace Ui {
class musicMenu;
}

class musicMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit musicMenu( clientSocket *m_clientInfo,QWidget *parent = nullptr);
    ~musicMenu();
protected:
    void closeEvent(QCloseEvent *event) override;

public:

private:
    Ui::musicMenu *ui;
    //通信
    clientSocket *m_clientInfo;
    musicList *m_musicList;
    musicPlaybackControls* m_musicPlayControls;
    //搜索框补全
    QCompleter * m_complete;

};

#endif // MUSICMENU_H
