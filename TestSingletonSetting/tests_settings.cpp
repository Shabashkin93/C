#include "tests_settings.h"

Tests_Settings::Tests_Settings()
{
    qDebug() << QString("Test_Settings -> constructor\n");
}

void Tests_Settings::coutTest(){
        qDebug() << QString("Test_Settings -> cout\n");
}

bool Tests_Settings::openDb(QString nameDb){
    QString name = nameDb;
    qDebug() << QString("Test_Settings -> openDb\t") << name ;
    return true;
}

bool Tests_Settings::createObj(){
    qDebug() << QString("Test_Settings -> createObj\n");
    return true;
}

bool Tests_Settings::saveObjInDb(){
    qDebug() << QString("Test_Settings -> saveObjInDb\n");
    return true;
}

Singleton* Singleton::instance = 0;

Singleton* Singleton::getInstance()
{
    if (instance == 0)
    {
        instance = new Singleton();
    }

    return instance;
}

Singleton::Singleton()
{}
