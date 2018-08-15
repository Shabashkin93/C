#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QDebug>
#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include <odb/sqlite/database.hxx>

#include <storage/storedvalue-odb.hxx>

class Settings {

public:
    Settings();
    virtual bool openDb(QString nameDb);
    virtual bool createObj();
    virtual bool saveObjInDb();
};

#endif // SETTINGS_H
