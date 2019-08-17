/**
     Album Data access object

    @author Kyle Beebe
*/

#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>

//forward declarations
class QSqlDatabase;
class Album;

class AlbumDao
{
public:
    // database parameter is database connection used for all queries
    AlbumDao(QSqlDatabase& database);

    /**
            Creates albums table, called when mDAtabase is opened
    */
    void init() const;

    /**
        Queries database for album, adds it

        @param album object containing album information for querry
    */
    void addAlbum(Album& album) const;

    /**
        Updates album information stored in database

        @param album object containing album information for query
    */
    void updateAlbum(const Album& album) const;

    /**
        Removes album stored in database

        @param id id corresponding to album to be deleted
    */
    void removeAlbum(int id) const;

    /**
        Returns vector of albums

        @return QVector of Album pointers
    */
    QVector<Album*> albums() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H
