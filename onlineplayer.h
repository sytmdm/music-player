#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H
#include <QMediaPlayer>
#include <QObject>

class onLinePlayer : public QObject
{
    Q_OBJECT
public:
    explicit onLinePlayer(QObject *parent = nullptr);

public slots:
    void testSlot();
signals:


private:
    QMediaPlayer * player;
};

#endif // ONLINEPLAYER_H
