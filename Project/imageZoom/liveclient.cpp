#include "liveclient.h"
LiveClient::LiveClient(QObject *parent): QObject (parent)
{

}

void LiveClient::loadQml()
{
    m_engine->clearComponentCache();
    m_engine->load("file:///C:/mycode/Qt Quick/imageZoom/main.qml");
}
