#ifndef MUSICLIRC_H
#define MUSICLIRC_H

#include <QMainWindow>

namespace Ui {
class musicLirc;
}

class musicLirc : public QMainWindow
{
    Q_OBJECT

public:
    explicit musicLirc(QWidget *parent = nullptr);
    /* 播放指定音乐 */
    void startAppointMusic();
    ~musicLirc();

private:
    Ui::musicLirc *ui;
};

#endif // MUSICLIRC_H
