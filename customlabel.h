#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QObject>
#include<QLabel>
#include<QWidget>
#include<QEvent>
#include<QMouseEvent>
class customLabel : public QLabel
{
    Q_OBJECT
public:
    explicit customLabel(QWidget *parent = nullptr);
    protected:
    //鼠标进入事件
    void enterEvent(QEvent *event) override;
    //鼠标离开事件
    void leaveEvent(QEvent *event) override;

    //鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;
public:
    //设置头像
    void setHeadImage(const QString &FileName);
    //处理更改头像信号的槽函数
    void handleChangeImgSlot();
private:
    QString m_fileName;
signals:
public slots:
};

#endif // CUSTOMLABEL_H
