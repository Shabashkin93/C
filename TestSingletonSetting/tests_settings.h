#ifndef TESTS_SETTINGS_H
#define TESTS_SETTINGS_H

#include "settings.h"

class Tests_Settings : public Settings{

public:
    Tests_Settings();
    bool openDb(QString nameDb);
    bool createObj();
    bool saveObjInDb();

    void coutTest();
};

class Singleton
{
    private:

        static Singleton* instance;

        Singleton();

    public:
        static Singleton* getInstance();
};

#endif // TESTS_SETTINGS_H
