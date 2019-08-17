#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
    explicit PictureDao(QSqlDatabase& database);

    /**
        Creates pictures table, called when mDAtabase is opened
    */
    void init() const;

    /**
        Adds picture associated with an specific album in the database

        @param picture object containing picture information for query
        @param albumId int holding album id number
    */
    void addPictureInAlbum(int albumId, Picture& picture) const;
    void removePicture(int id) const;
    void removePicturesForAlbum(int albumId) const;
    QVector<Picture*> picturesForAlbum(int albumId) const;

private:
    QSqlDatabase& mDatabase;

};

#endif // PICTUREDAO_H
