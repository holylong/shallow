// MIT License

// Copyright (c) 2022 hooy

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <hookutil.h>
#include <mousehistory.h>
#include <keyboardhistory.h>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QSystemTrayIcon>
#include "keyboardwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << __FUNCTION__;
    ui->setupUi(this);

    _keyboard = new KeyboardWidget;
    QString ctx = "";
    _keyboard->updateContent(ctx);
    _keyboard->show();

    InitTrayIcon();

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setFixedSize(QSize(50,50));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground, true);

    connect(MouseHistory::instance(), &MouseHistory::getPos, [=](long x, long y){
        move(x-25, y-25);
    });

    connect(KeyboardHistory::instance(), &KeyboardHistory::getKeyName, [=](QString& key){
        std::vector<QString>::iterator it = std::find(_keyVec.begin(), _keyVec.end(), key);
        if(it == _keyVec.end())_keyVec.push_back(key);
        displayKey();
    });

    connect(KeyboardHistory::instance(), &KeyboardHistory::dropKeyName, [=](QString& key){
        eraseKey(key);
        displayKey();
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
    startKeyBoardHook();
}

void MainWindow::displayKey()
{
    QString ctx = "";int index = 0;
    bool showkey = false;
    for(auto key : _keyVec){
        if(key == "Shift" || key == "Enter" || key == "Ctrl" || key == "Space" || key == "Alt"
                || key == "")showkey = true;
        if(key == "") key = "Win";
        ctx += key;
        if(++index != _keyVec.size())
            ctx += " + ";
    }
    if(showkey || _keyVec.size() == 0)
        _keyboard->updateContent(ctx);
    showkey = false;
}

void MainWindow::eraseKey(QString key){
    std::vector<QString>::iterator it = std::find(_keyVec.begin(), _keyVec.end(), key);
    while (it != _keyVec.end())
    {
        it = _keyVec.erase(it);
        it = std::find(it, _keyVec.end(), key);
    }
}

void MainWindow::InitTrayIcon()
{
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon(":/res/cat.ico"));
    _trayIcon->setToolTip("Shallow");
    _trayMenu = new QMenu(this);
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
    painter.restore();
}

MainWindow::~MainWindow()
{
    delete ui;
    stopMouseHook();
    stopKeyBoardHook();
}

