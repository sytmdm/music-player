#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include"clientsocket.h"
#include<QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

public slots:
    //处理注册信号的槽函数
    void handleRegisSlot();
    //处理登录信号的槽函数
    void handleLoginSlot();
    //处理连接成功的槽函数
    void handlConnectedSlot();
    //处理完整数据的槽
    void handleDataSlot(const QByteArray &data);

private:
    Ui::MainWindow *ui;
    clientSocket * m_client;
};
#endif // MAINWINDOW_H
