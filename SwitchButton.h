#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

class SwitchButton : public QPushButton {
    Q_OBJECT

public:
    QPixmap QpixOn, QpixOff;
    bool state;

    SwitchButton(QWidget *parent=0,int x=0,int y=0,QString img_on=":/on3",QString img_off=":/off3",bool startState=false)
    {
        QpixOn = QPixmap(img_on);
        QpixOff = QPixmap(img_off);
        state = startState;
        setParent(parent);
        setGeometry(x,y,QpixOn.width(),QpixOn.height());
        //connect(this,SIGNAL(clicked(bool)),this,SLOT(setState(bool)));
    }

    void mousePressEvent(QMouseEvent *mouseClick){
        if(mouseClick->x() >= (QpixOn.width()/2))
            emit clicked(true);
        else
            emit clicked(false);
    }

    void keyReleaseEvent(QKeyEvent *k){
        if(k->key() == Qt::Key_Space)
            emit clicked(!state);
    }

    void keyPressEvent(QKeyEvent *){} //Just to clicked signal not be emitted twice.

    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        if(state) painter.drawPixmap(0,0,QpixOn);
        else painter.drawPixmap(0,0,QpixOff);
    }

    ~SwitchButton(){}

public slots:
    void setState(bool newState){
        state = newState;
        update();
        qDebug("Switch Updated");
    }
};

#endif // SWITCHBUTTON_H
