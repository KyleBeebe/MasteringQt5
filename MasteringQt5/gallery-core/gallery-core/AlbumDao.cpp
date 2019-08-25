#include "AlbumDao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <exception>
#include <QDebug>

#include "DatabaseManager.h"
#include "Album.h"
#include "CustomExceptions.h"



AlbumDao::AlbumDao(QSqlDatabase& database):
    mDatabase(database)
{

}

void AlbumDao::init() const{

    if(!mDatabase.tables().contains("albums")){
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY "
            "AUTOINCREMENT, name TEXT)");


    }
}

void AlbumDao::addAlbum(Album &album) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    //bind query name value to album name
    query.bindValue(":name", album.name());


    query.exec();

    //retrieve id of album row just inserted
    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::removeAlbum(int id) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("DELETE FROM albums WHERE id = (:id)");

    query.bindValue(":id", id);


    query.exec();

}

std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);

    query.exec();

    unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>());
    while(query.next()) {

        unique_ptr<Album> album(new Album());
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(move(album));
    }
    return list;
}

void AlbumDao::updateAlbum(const Album& album) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");

    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());


    query.exec();


}
