#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>

class QSystemTrayIcon;
class QMenu;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void InitTrayIcon();

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *_trayIcon{nullptr};
    QMenu           *_trayMenu{nullptr};

    //鼠标点击事件
    bool            pressed_{false};
};
#endif // MAINWINDOW_H
