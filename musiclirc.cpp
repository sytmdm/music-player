#include "musiclirc.h"
#include "ui_musiclirc.h"

musicLirc::musicLirc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::musicLirc)
{
    ui->setupUi(this);
}

musicLirc::~musicLirc()
{
    delete ui;
}
