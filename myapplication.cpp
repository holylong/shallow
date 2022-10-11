#include "myapplication.h"
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

MyApplication::MyApplication(int &argc,char **argv): QApplication(argc,argv)
{

}

MyApplication::~MyApplication()
{

}

bool MyApplication::event(QEvent *e)
{
    qDebug() << "type:" << e->type();

    return QApplication::event(e);
}

void MyApplication::setWindowInstance(QWidget *wnd)
{
}

bool MyApplication::notify(QObject *obj, QEvent *e)
{
    const QMetaObject* meta = obj->metaObject();
    QString clName = meta->className();

    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        if(keyEvent->key() == Qt::Key_Escape)qDebug() << clName << " escape";
     }
    else if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
        if(mouseEvent->buttons() == Qt::LeftButton) qDebug() << "button left";
        if(mouseEvent->button() == Qt::RightButton)qDebug() << "button right";
    }
    return QApplication::notify(obj,e);
}
