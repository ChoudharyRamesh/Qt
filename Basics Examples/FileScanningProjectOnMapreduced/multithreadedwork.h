#ifndef MULTITHREADEDWORK_H
#define MULTITHREADEDWORK_H

#include <QObject>
#include<QtConcurrent>
#include<QMutex>
#include<QElapsedTimer>
#include<QFutureWatcher>
// monitor progress
// http://blackberry.github.io/Qt2Cascades-Samples/docs/qtconcurrent-progressdialog.html

class MultiThreadedWork : public QObject
{
    Q_OBJECT
public:
    explicit MultiThreadedWork(QString dirPath,QObject *parent = nullptr);
public slots:
    void doWork();
    static QPair<int,QList<QString>> threadedScaning
    (QString filePath);
    static void ReducedWork
    ( QPair<int,QList<QString>> &, const QPair<int,QList<QString>>
     & intermediate_result);

signals:
    void workDone(int fileCount,QString timetaken);
private:
    QString dirPath;

};

#endif // MULTITHREADEDWORK_H
