#include "DatabaseManager.h"

#include <QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSLITE"))),
albumDao(*mDatabase), pictureDao(*mDatabase){

    mDatabase->setDatabaseName(path);
    mDatabase->open();

    //albumDao initialized after mDatabase
    albumDao.init();
    pictureDao.init();
}

DatabaseManager::~DatabaseManager(){
    mDatabase->close();
    delete mDatabase;
}
