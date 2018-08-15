#include "tests.h"

Tests::Tests(QObject *parent) : QObject(parent)
{

}

void Tests::firstTest(){
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void Tests::testSingleton(){
    Singleton* a = Singleton::getInstance();
    Singleton* b = Singleton::getInstance();
    QCOMPARE(a,b);
}

QTEST_MAIN(Tests)
