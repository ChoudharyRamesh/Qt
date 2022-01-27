#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QJsonArray>
#include<QJsonObject>
#include<QMessageBox>
#include<QTextEdit>
#include<QJsonDocument>
#include<QVariantMap>
#include<QLabel>
#include<QSslSocket>


// set your access key here
// Note ::- this code is compatible with unsplash access_key ,
//             if you using another service then change your code according to json response in Widget.cpp file .
#define ACCESS_KEY "0dKofrYi890kzKjMDj_vNDeuPLz6t8oW_BbfP_z6Zjg"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    int pictureCount;
    int row,column;
    int TotalPages;
    bool isProcessRunning;
    QString search_tag;
    ~Widget();

private slots:
    void dataReadyToRead();
    void dataReadFinished();
    void SetPicture();
    void InitiatePictureRquest(const QString url);
    void dataReadyToRead_Pic();

    void on_Button_Prev_clicked();
    void on_Button_Next_clicked();
    void on_Button_search_clicked();
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager * netmanager;
    QNetworkReply * netreply_main;
    QNetworkReply * netreply_picture;
    QByteArray bytearray;
    QJsonArray pictureArray;
    QByteArray bytearray_pic;


};
#endif // WIDGET_H
