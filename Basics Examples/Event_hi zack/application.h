#ifndef APPLICATION_H
#define APPLICATION_H

#include<QApplication>
#include<QDebug>

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    bool notify(QObject *, QEvent *)override;
};

#endif // APPLICATION_H
