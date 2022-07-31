#ifndef CustomLabel_H
#define CustomLabel_H

#include <QWidget>
#include<QDebug>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>
#include<QPixmap>
#include<QStringList>
#include<QFileInfo>
#include<QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget * parent = nullptr);

signals:

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    bool isImage(QFileInfo file);

};

#endif // CustomLabel_H
