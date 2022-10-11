#ifndef KEYBOARDHISTORY_H
#define KEYBOARDHISTORY_H


#include <QObject>
#include <QThread>

class KeyboardHistory : public QObject
{
    Q_OBJECT
public:
    KeyboardHistory(QObject* parent = nullptr):QObject(parent){}

public:
    virtual ~KeyboardHistory(){}
   static KeyboardHistory *&instance()
   {
       static KeyboardHistory *s = nullptr;
       if (s == nullptr)
       {
           s = new KeyboardHistory();
       }
       return s;
   }

 public:
   void setKeyValue(unsigned long key)
   {
       emit getKey(key);
   }

   void setKeyValueName(QString key)
   {
       emit getKeyName(key);
   }

   void resetKeyValueName(QString key){
        dropKeyName(key);
   }

 signals:
   void getKey(unsigned long);
   void getKeyName(QString&);
   void dropKeyName(QString&);
};

#endif // KEYBOARDHISTORY_H
