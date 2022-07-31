#include "customlabel.h"

CustomLabel::CustomLabel(QWidget * parent) : QLabel(parent)
{
    setAcceptDrops(true);
}
bool CustomLabel::isImage(QFileInfo file)
{
    return( (file.suffix()=="PNG" ) ||
               (file.suffix()=="png" ) ||
               (file.suffix()=="JPG" ) ||
               (file.suffix()=="jpg" ) ||
               (file.suffix()=="JPEG" ) ||
               (file.suffix()=="jpeg" )
             );
}

void CustomLabel::dragEnterEvent(QDragEnterEvent *event)
{
     if(event->mimeData()->hasUrls())
       {  QList<QUrl> urlList =  event->mimeData()->urls();
           QFileInfo file(urlList.at(0).toLocalFile());
          if(isImage(file.absoluteFilePath()))
              event->accept();
          else
           event->ignore();
      }
      else
      event->ignore();
}

void CustomLabel::dropEvent(QDropEvent *event)
{
   event->accept();
   setPixmap(QPixmap(event->mimeData()->urls().at(0).toLocalFile()).scaled(800,800,Qt::KeepAspectRatio));
}
