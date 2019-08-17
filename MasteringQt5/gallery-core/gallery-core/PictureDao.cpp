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
        try {
            query.exec(QString("CREATE TABLE pictures")
            + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
            + "album_id INTEGER, "
            + "url TEXT)");
        } catch (SqlQueryException& e) {
            qDebug() << e.what();
        }

    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const{

    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("INSERT INTO pictures (album_id, url) VALUES (:album_id, :url)");

    //bind picture table values
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.fileUrl());

    try {
        query.exec();
    } catch (SqlQueryException &e) {
        qDebug() << e.what();
    }
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

    try {
        query.exec();
    } catch (SqlQueryException &e) {
        qDebug() << e.what();
    }
}
void PictureDao::removePicturesForAlbum(int albumId) const{
    QSqlQuery query(mDatabase);
    //prepare the query
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");

    //bind picture table values
    query.bindValue(":album_id", albumId);

    try {
        query.exec();
    } catch (SqlQueryException &e) {
        qDebug() << e.what();
    }
}
QVector<Picture*> PictureDao::picturesForAlbum(int albumId) const{
    QSqlQuery query("SELECT * FROM pictures", mDatabase);
    try {
        query.exec();
    } catch (SqlQueryException &e) {
        qDebug() << e.what();
    }

    QVector<Picture*> list;
    while(query.next()) {
        if(query.value("album_id").toInt() == albumId){
            Picture* picture = new Picture();
            picture->setId(query.value("id").toInt());
            picture->setAlbumId(query.value("album_id").toInt());
            picture->setFileUrl(query.value("url").toUrl());

            list.append(picture);
        }
    }
    return list;
}
