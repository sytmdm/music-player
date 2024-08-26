#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qstring.h>
#include<qicon.h>
#include<QPushButton>
#include<QDebug>
#include<QPixmap>
#include<QFileDialog>   //文件对话框
#include"customlabel.h"
#include<QHostAddress>
#include<QJsonObject>
#include<QJsonDocument>
#include<QMessageBox>
#include<musicmenu.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_client(new clientSocket(this))
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("戴头套的ikun") ;
    //设置窗口图标
    QIcon picIcon(":/imag/20220726130434_f408d.jpg");
    setWindowIcon(picIcon);
    //设置头像

    ui->headimg->setHeadImage(":/imag/1.png");

    //信号和槽
    connect(ui->regisBtn,&QPushButton::clicked,this,&MainWindow::handleRegisSlot);
    connect(ui->loginBtn,&QPushButton::clicked,this,&MainWindow::handleLoginSlot);

    m_client->connectToServer("192.168.113.128",8080);
    connect(m_client,&clientSocket::connectSucessed,this,&MainWindow::handlConnectedSlot);
    connect(m_client,&clientSocket::dataRecevied,this,&MainWindow::handleDataSlot);
}
//处理完整数据的槽
void MainWindow::handleDataSlot(const QByteArray &data)
{
    qDebug()<<"data: "<<data<<endl;
    //1、解析json字符串
    QJsonDocument document= QJsonDocument::fromJson(data);
    if(document.isObject()==false)
     {
        qDebug()<<"document is not Object."<<endl;
        return ;
     }
    //1、将document对象转成json对象
    QJsonObject jsonObj=document.object();

    //3、取值
    int type=jsonObj["type"].toInt();
    QString result=jsonObj["result"].toString();
    if(type==1)
    {
        //注册
        if(result=="success")
        {
            QMessageBox::information(this,"注册","注册成功");
        }
        else
        {
            QString reason=jsonObj["reason"].toString();
            QMessageBox::information(this,"注册",reason);
        }
    }
    else if(type==2)
    {
        //登录
        if(result=="success")
        {
            QMessageBox::information(this,"登录","登录成功");
            //登录成功之后跳转到音乐播放器界面
            musicMenu *musicInterface=new musicMenu(m_client);
            musicInterface->show();
            this->hide();
        }
        else
        {
            QString reason=jsonObj["reason"].toString();
            QMessageBox::information(this,"登录",reason);
        }
    }

}
void MainWindow::handlConnectedSlot()
{
qDebug()<<"连接成功..."<<endl;
}
//处理注册信号的槽函数
void MainWindow::handleRegisSlot()
{
    qDebug()<<"注册..."<<endl;
    QString username= ui->accountInfo->text();
    QString passwd=ui->passwdInfo->text();

    qDebug()<<"username:"<<username<<" passwd:"<<passwd<<endl;
    //创建json对象
    QJsonObject jsonObj;
    //设置<key:value>属性
    jsonObj["type"]=1;
    jsonObj["username"]=username;
    jsonObj["passwd"]=passwd;
    //创建Document对象
    QJsonDocument document(jsonObj);
    m_client->writeData(document.toJson());
}
//处理登录信号的槽函数
void MainWindow::handleLoginSlot()
{
    qDebug()<<"登录..."<<endl;
    QString username= ui->accountInfo->text();
    QString passwd=ui->passwdInfo->text();

    qDebug()<<"username:"<<username<<" passwd:"<<passwd<<endl;

    //创建json对象
    QJsonObject jsonObj;
    //设置<key:value>属性
    jsonObj["type"]=2;
    jsonObj["username"]=username;
    jsonObj["passwd"]=passwd;
    //创建Document对象
    QJsonDocument document(jsonObj);
    m_client->writeData(document.toJson());
}

MainWindow::~MainWindow()
{
    delete ui;
}

