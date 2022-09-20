#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <hookutil.h>
#include <mousehistory.h>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitTrayIcon();

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setFixedSize(QSize(50,50));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground, true);

    connect(MouseHistory::instance(), &MouseHistory::getPos, [=](long x, long y){
        move(x-25, y-25);
    });

    connect(MouseHistory::instance(), &MouseHistory::getPress, [=](int key){
        if(key == 1)
            pressed_ = true;
        else{
            pressed_ = false;
        }
        update();
    });

    startMouseHook();
}

void MainWindow::InitTrayIcon()
{
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/res/cat.ico"));
    _trayIcon->setToolTip("Shallow");
    _trayMenu = new QMenu(this);
//    _trayMenu->addAction(tr("显示Shallow窗口"),this,[=](){
//          this->show();
//          this->activateWindow();
//     });
    _trayMenu->addAction(tr("退出Shallow"),this,[=](){
          qApp->quit();
     });
    _trayIcon->setContextMenu(_trayMenu);
    _trayIcon->show();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(pressed_){
        painter.setBrush(QColor(255,200,200,100));
    }
    else{
        painter.setBrush(QColor(125,125,125,100));
    }
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.drawEllipse(QPoint(this->rect().left()+25, this->rect().top()+25), 25, 25);
}

MainWindow::~MainWindow()
{
    delete ui;
    stopMouseHook();
}

