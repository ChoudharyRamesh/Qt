#include "application.h"

Application::Application(int argc, char *argv[]) : QApplication(argc,argv)
{

}

bool Application::notify(QObject * destination, QEvent * event)
{
    qDebug()<<"Application notify called "<<"class name "<<destination->metaObject()->className()<<" event type "<< event->type();
    return QApplication::notify(destination,event);
}
