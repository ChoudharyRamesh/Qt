#include "widget.h"
#include "ui_widget.h"
#include<QThread>
#include<QScroller>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    netmanager = new QNetworkAccessManager(this);
    netreply_main = nullptr;
    netreply_picture = nullptr;
    pictureCount = 0;

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->Button_Next->setEnabled(false);
    ui->Button_Prev->setEnabled(false);

    ui->spinBox->setEnabled(false);
    ui->spinBox->hide();

    setWindowTitle("Image Search Ap");

   // for touch on android
   QScroller::grabGesture(ui->tableWidget,QScroller::TouchGesture);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_Button_search_clicked()
{
    QNetworkRequest request;
    if(ui->lineEdit_searchbar->text()=="")
    {
        if(ui->tableWidget->rowCount()<=1)
        { qDebug()<<"Search bar is empty ";
          ui->tableWidget->setColumnCount(1);
          ui->tableWidget->setRowCount(1);
         QLabel * temp_label = new QLabel("Search bar is empty");
          temp_label->setFont(QFont("times",20,true));
          ui->tableWidget->setCellWidget(0,0,temp_label);
          return;
        }
        else
        return;
    }
    else
      search_tag = ui->lineEdit_searchbar->text();

    bytearray.clear();
    pictureCount=0;
    row=column=0;
    ui->tableWidget->clear();
    TotalPages = 0;
    ui->spinBox->blockSignals(true);
    ui->spinBox->setValue(1);
   ui->spinBox->blockSignals(false);

   // i am using unsplash api ,you can you your own and modify code accorrding to json response

    request.setUrl(QUrl("https://api.unsplash.com/search/photos?page=1&query="+search_tag+"&client_id="+ACCESS_KEY+"&format=json"));
    netreply_main = netmanager->get(request);
    connect(netreply_main,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
    connect(netreply_main,&QNetworkReply::finished,this,&Widget::dataReadFinished);
    static int i=0;
    if(i!=1){
        ui->tableWidget->setColumnCount(2);
       ui->tableWidget->setRowCount(5);
       i=1;
    }
}


void Widget::dataReadyToRead()
{
   bytearray.append(netreply_main->readAll());
}

void Widget::dataReadFinished()
{
     if(netreply_main->error())
        {
            qDebug()<<"network error "<<netreply_main->errorString();
            ui->Button_Prev->setEnabled(false);
            ui->Button_Next->setEnabled(false);
            QLabel * temp_label = new QLabel("No Internet");
            temp_label->setFont(QFont("times",20,true));
             ui->tableWidget->setCellWidget(0,0,temp_label);
            return;
        }
     else
      { QJsonDocument doc  = QJsonDocument::fromJson(bytearray);
         qDebug()<<bytearray;
          QJsonObject object = doc.toVariant().toJsonObject();
          QVariantMap picmap = object.toVariantMap();

           pictureArray = picmap["results"].toJsonArray();
           qDebug()<<"number of picture coming from server is "<<pictureArray.size();
               if(!TotalPages)
               { TotalPages = picmap["total_pages"].toInt();
                   if(TotalPages>0)
                   { if(TotalPages!=1)
                       { ui->Button_Next->setEnabled(true);
                          ui->spinBox->setEnabled(true);
                          ui->spinBox->setRange(1,TotalPages);
                       }
                   }
                   else
                   {
                       ui->Button_Prev->setEnabled(false);
                       ui->Button_Next->setEnabled(false);
                       QLabel * temp_label = new QLabel("No data available");
                       temp_label->setFont(QFont("times",20,true));
                        ui->tableWidget->setCellWidget(0,0,temp_label);
                       return;
                   }
               }
             QString  thumb_path = pictureArray.at(pictureCount).toObject().toVariantMap()["urls"].toJsonObject().toVariantMap()["thumb"].toString();
             InitiatePictureRquest(thumb_path);
             pictureCount++;
        isProcessRunning =  true;
     }
   bytearray.clear();
}


void Widget::InitiatePictureRquest(const QString url)
{
      QNetworkRequest request;
       request.setUrl(QUrl(url));
      netreply_picture = netmanager->get(request);
      connect(netreply_picture,&QIODevice::readyRead,this,&Widget::dataReadyToRead_Pic);
      connect(netreply_picture,&QNetworkReply::finished,this,&Widget::SetPicture);
}

void Widget::dataReadyToRead_Pic()
{
     bytearray_pic.append(netreply_picture->readAll());
}


void Widget::SetPicture()
{
    if(bytearray_pic.isEmpty()==false)
    {  /*QDebug debug =  qDebug();
        static int i=0;
        debug<<"started";
        if(i<1)
        {   int j=0;
            for(int i=0;i<bytearray_pic.size();i++)
            {
                debug.noquote()<<bytearray_pic.at(i)+0<<","; j++;
                if(j>20){  debug.noquote()<<"\\\n"; j=0; }
            }
            i++;
            debug<<"closed";
        }*/

    QPixmap picture;
    picture.loadFromData(bytearray_pic);
    picture = picture.scaled(ui->tableWidget->width()/2,ui->tableWidget->height()/4,Qt::IgnoreAspectRatio);
    QLabel * temp_label = new QLabel;
    temp_label->setPixmap(picture);
    ui->tableWidget->setCellWidget(row,column,temp_label);
    bytearray_pic.clear();
    if(column==1)
    {
        column=0;
        row++;
    }
    else
    column++;


    if(pictureCount<pictureArray.size())
      {  QString  thumb_path = pictureArray.at(pictureCount).toObject().toVariantMap()["urls"].toJsonObject().toVariantMap()["thumb"].toString();
          InitiatePictureRquest(thumb_path);
          pictureCount++;
      }
    else
         isProcessRunning = false;

    }
    else
    { qDebug()<<"empty byte array";
        bytearray_pic.clear();
        QLabel * temp_label = new QLabel("No data available");
          temp_label->setFont(QFont("times",20,true));
         ui->tableWidget->setCellWidget(0,0,temp_label);
        if(pictureCount<pictureArray.size())
          {
             pictureCount++;
             QString  thumb_path = pictureArray.at(pictureCount).toObject().toVariantMap()["urls"].toJsonObject().toVariantMap()["thumb"].toString();
             InitiatePictureRquest(thumb_path);
             pictureCount++;
          }
    }

}


void Widget::on_Button_Prev_clicked()
{
       if(ui->spinBox->value()>1)
            ui->spinBox->setValue(ui->spinBox->value()-1);

       if(ui->spinBox->value()==1)
             ui->Button_Prev->setEnabled(false);
         ui->Button_Next->setEnabled(true);
}

void Widget::on_Button_Next_clicked()
{
        if(ui->spinBox->value()<TotalPages)
           ui->spinBox->setValue(ui->spinBox->value()+1);

          if(ui->spinBox->value()==TotalPages)
             ui->Button_Next->setEnabled(false);
         ui->Button_Prev->setEnabled(true);
}


void Widget::on_spinBox_valueChanged(int arg1)
{

    int integer = arg1;
        if(integer<=TotalPages )
         {
            if(isProcessRunning)
              {  netreply_picture->close();
                  disconnect(netreply_picture,&QIODevice::readyRead,this,&Widget::dataReadyToRead_Pic);
                  disconnect(netreply_picture,&QNetworkReply::finished,this,&Widget::SetPicture);
                  bytearray_pic.clear();
                  bytearray.clear();
              }
           QNetworkRequest request;
           bytearray.clear();
           pictureCount=0;
           row=column=0;
           ui->tableWidget->clear();
           request.setUrl(QUrl("https://api.unsplash.com/search/photos?page="+QString::number(integer)+"&query="+search_tag+"&client_id="+ACCESS_KEY+"&format=json"));
           netreply_main = netmanager->get(request);
           connect(netreply_main,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
           connect(netreply_main,&QNetworkReply::finished,this,&Widget::dataReadFinished);
         }

        if(integer==TotalPages)
            ui->Button_Next->setEnabled(false);
        else
           ui->Button_Next->setEnabled(true);

         if(integer==1)
              ui->Button_Prev->setEnabled(false);
        else
          ui->Button_Prev->setEnabled(true);
}

void Widget::on_pushButton_clicked()
{
    QMessageBox temp;
    temp.about(this,"About","This application is made by using Qt C++ API\n\
               Qt version -- 15.5.0\n\
               Built on -- 18/08/20 \n\
               Based on -- Andriod Clang C++ 7.1.0 \n\
               Application Version -- 1.0 ( Demo App for Rest API connection )\n\
               REST API of  -- https://unsplash.com\n\
               Developer Contact\n\t\
                  Email -- rchoudhary4856@gmail.com\n\
               ");
}
