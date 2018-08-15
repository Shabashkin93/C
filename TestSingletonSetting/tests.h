#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include "settings.h"
#include "tests_settings.h"

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests(QObject *parent = nullptr);

signals:

public slots:
private slots:
    void firstTest();
    void testSingleton();
};

#endif // TESTS_H
