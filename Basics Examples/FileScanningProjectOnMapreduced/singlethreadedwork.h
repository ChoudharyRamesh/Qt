#ifndef SINGLETHREADEDWORK_H
#define SINGLETHREADEDWORK_H

#include <QObject>
#include<QElapsedTimer>
class SingleThreadedWork : public QObject
{
    Q_OBJECT
public:
    explicit SingleThreadedWork(QString dirPath ,QObject *parent = nullptr);
public slots:
    void doWork();

signals:
    void workDone(int files,QString timetaken);
private:
    QString dirPath;

};

#endif // SINGLETHREADEDWORK_H
