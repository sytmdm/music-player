#ifndef SELECTMENU_H
#define SELECTMENU_H

#include <QWidget>

namespace Ui {
class selectMenu;
}

class selectMenu : public QWidget
{
    Q_OBJECT

public:
    explicit selectMenu(QWidget *parent = nullptr);
    ~selectMenu();

private:
    /* 设置初始的按钮图标 */
    void setInitButtonIcon();

public slots:
    void OnLocalSlot();
    void OnOnlineSlot();
    void OnCollectionSlot();

private:
    Ui::selectMenu *ui;
};

#endif // SELECTMENU_H
