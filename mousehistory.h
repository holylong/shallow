#ifndef MOUSEHISTORY_H
#define MOUSEHISTORY_H

#include <QObject>

class MouseHistory : public QObject
{
    Q_OBJECT
public:
    MouseHistory(QObject* parent = nullptr):QObject(parent){}
    virtual ~MouseHistory(){}
       static MouseHistory *&instance()
       {
           static MouseHistory *s = nullptr;
           if (s == nullptr)
           {
               s = new MouseHistory();
           }
           return s;
       }

     public:
       void setPosValue(long x, long y)
       {
           emit getPos(x,y);
       }

       void setPressEvent(int key){
           emit getPress(key);
       }

     signals:
       void getPos(long, long);
       void getPress(int);
};

#endif // MOUSEHISTORY_H
