#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>

class QLabel;

class KeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = nullptr);

public:
    void updateContent(QString& str);

signals:

private:
    QLabel    *_labelKeyboard;
};

#endif // KEYBOARDWIDGET_H
