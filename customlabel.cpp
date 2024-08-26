#include "customlabel.h"
#include<QWidget>
#include<QDebug>
#include<QFileDialog>
#include<QPushButton>
customLabel::customLabel(QWidget *parent) : QLabel(parent)
{

}
//鼠标进入事件
void customLabel::enterEvent(QEvent *event)
{
    setStyleSheet("background-color:rgba(0,0,0,100);"//半透明
                  "color:white;"        //白色文本
                  "font-weight:bold;"//粗体
                  );
    setText("更改头像");
    setAlignment(Qt::AlignCenter);

    //让进入事件回归父类
    QLabel::enterEvent(event);
}
//鼠标离开事件
void customLabel::leaveEvent(QEvent *event)
{
    setHeadImage(m_fileName);
    //让进入事件回归父类
    QLabel::leaveEvent(event);
}

//鼠标点击事件
void customLabel::mousePressEvent(QMouseEvent *event)
{

    QString filter="Imags Files (*.jpg *.jpeg *.gif *.png)";
    QString FileName=QFileDialog::getOpenFileName(this,"选择头像","",filter);
    //设置头像
    setHeadImage(FileName);
    m_fileName=FileName;
    //让进入事件回归父类
    QLabel::mousePressEvent(event);
}
void customLabel::setHeadImage(const QString &FileName)
{

    QPixmap headPic(FileName);
    m_fileName=FileName;
    setPixmap(headPic.scaled(110,110, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
//void customLabel::handleChangeImgSlot()
//{
//    qDebug()<<"更改头像..."<<endl;

//    QString filter="Imags Files (*.jpg *.jpeg *.gif *.png)";
//    QString FileName=QFileDialog::getOpenFileName(this,"选择头像","",filter);
//    //设置头像
//    setHeadImage(FileName);
//}
