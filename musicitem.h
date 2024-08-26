#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QMainWindow>

namespace Ui {
class musicItem;
}

class musicItem : public QMainWindow
{
    Q_OBJECT

public:
    explicit musicItem(QWidget *parent = nullptr);
    ~musicItem();
public:
    void setMusicName(const QString &musicName);
    void setMusicTime(const QString &setMusicTime);
    void setSingerName(const QString &setSingerName);
private:
    Ui::musicItem *ui;
};

#endif // MUSICITEM_H
