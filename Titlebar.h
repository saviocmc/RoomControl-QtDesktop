#ifndef TITLEBAR_H
#define TITLEBAR_H

#endif // TITLEBAR_H

#include <QHBoxLayout>

class Titlebar : public QWidget
{
    private:
        QWidget *parent;
        QPoint cursor;

    public:
        Titlebar( QWidget *parent ) : parent( parent )
        {
            QLabel *label = new QLabel( parent->windowTitle() );
            QPushButton *buttonClose = new QPushButton( "x" );

            QHBoxLayout *layout = new QHBoxLayout( this );
                layout->addWidget( label, 1 );
                layout->addWidget( buttonClose );

            connect( buttonClose, SIGNAL( clicked() ), parent, SLOT( close() ) );
        }

    protected:
        void mousePressEvent( QMouseEvent *event )
        {
            if( event->button() == Qt::LeftButton )
                cursor = event->globalPos() - geometry().topLeft();
        }

        void mouseMoveEvent( QMouseEvent *event )
        {
            if( event->buttons() & Qt::LeftButton )
                parent->move( event->globalPos() - cursor );
        }
};
