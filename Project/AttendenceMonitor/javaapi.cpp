#include "javaapi.h"

JavaApi::JavaApi(QObject *parent) : QObject(parent)
{

}

// java native interface calls
QJsonArray JavaApi::getData()
{
   QString reply =  QAndroidJniObject::callStaticObjectMethod
                                             ("com/RameshKumar/AttendanceMonitor/AttendanceMonitor",
                                              "getData",
                                              "()Ljava/lang/String;").toString();
   if(reply=="") return QJsonArray();
   return  QJsonDocument::fromJson(reply.toUtf8()).array();
}

void JavaApi::updateData(QString jsonData)
{
   QAndroidJniObject jsonData_object = QAndroidJniObject::fromString(jsonData);
   QAndroidJniObject::callStaticMethod<void>
                                             ("com/RameshKumar/AttendanceMonitor/AttendanceMonitor",
                                              "updateData",
                                              "(Ljava/lang/String;)V",
                                              jsonData_object.object<jstring>());
}

