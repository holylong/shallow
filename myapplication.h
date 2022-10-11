#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include <QApplication>

class MyApplication : public QApplication
{
     Q_OBJECT
public:
     MyApplication(int&argc,char **argv);
     ~MyApplication();

     bool notify(QObject*, QEvent *);
     void setWindowInstance(QWidget*wnd);

     bool event(QEvent *) override;
};

#endif // MYAPPLICATION_H
