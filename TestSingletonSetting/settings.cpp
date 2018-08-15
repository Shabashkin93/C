#include "settings.h"

Settings::Settings()
{
    qDebug() << QString("settings -> constructor\n");
}

bool Settings::openDb(QString nameDb){
    qDebug() << QString("settings -> openDb\n");
    return true;
}

bool Settings::createObj(){
        qDebug() << QString("settings -> createDb\n");
    return true;
}

bool Settings::saveObjInDb(){
        qDebug() << QString("settings -> saveObjInDb\n");
    return true;
}
