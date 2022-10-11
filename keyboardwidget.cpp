#include "keyboardwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

KeyboardWidget::KeyboardWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setFixedSize(QSize(300,50));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground, true);

    move(qApp->desktop()->availableGeometry().width() - 300, qApp->desktop()->availableGeometry().height()-100);

    _labelKeyboard = new QLabel();
    _labelKeyboard->setScaledContents(true);

    QFont font;
    font.setBold(true);
    font.setPixelSize(30);
    _labelKeyboard->setFont(font);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(_labelKeyboard);
    setLayout(mainLayout);
}


void KeyboardWidget::updateContent(QString& str)
{
    _labelKeyboard->setText(str);
}
