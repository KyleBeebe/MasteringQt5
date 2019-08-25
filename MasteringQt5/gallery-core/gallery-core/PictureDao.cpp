#include "PictureDao.h"

#include <QSqlQuery>
#include <QStringList>
#include <QDebug>

#include "Picture.h"
#include "CustomExceptions.h"

PictureDao::PictureDao(QSqlDatabase& database) : mDatabase(database)
{

}

void PictureDao::init() const
{
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);

            query.exec(QString("CREATE TABLE pictures")
            + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
            + "album_id INTEGER, "
            + "url TEXT)");


    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const{

    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("INSERT INTO pictures (album_id, url) VALUES (:album_id, :url)");

    //bind picture table values
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.fileUrl());


    query.exec();

    //retrieve id of picture row just inserted
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);

}
void PictureDao::removePicture(int id) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("DELETE FROM pictures WHERE id = (:id)");

    //bind picture table values
    query.bindValue(":id", id);


    query.exec();

}
void PictureDao::removePicturesForAlbum(int albumId) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");

    //bind picture table values
    query.bindValue(":album_id", albumId);


    query.exec();

}
std::unique_ptr<std::vector<std::unique_ptr<Picture>>>
    PictureDao::picturesForAlbum(int albumId) const{

    QSqlQuery query("SELECT * FROM pictures", mDatabase);

    query.exec();


    std::unique_ptr<std::vector<std::unique_ptr<Picture>>>
            list(new std::vector<std::unique_ptr<Picture>>);

    while(query.next()) {
        if(query.value("album_id").toInt() == albumId){
            std::unique_ptr<Picture> picture(new Picture());

            picture->setId(query.value("id").toInt());
            picture->setAlbumId(query.value("album_id").toInt());
            picture->setFileUrl(query.value("url").toUrl());

            list->push_back(move(picture));
        }
    }
    return list;
}
