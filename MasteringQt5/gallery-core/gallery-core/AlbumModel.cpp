#include "AlbumModel.h"

AlbumModel::AlbumModel(QObject* parent) : QAbstractListModel(parent),
    mDb(DatabaseManager::instance()), mAlbums(mDb.albumDao.albums())
{

}

int AlbumModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mAlbums->size();
}

QVariant AlbumModel::data(const QModelIndex& index, int role) const {

    if(!isIndexValid(index))
        return QVariant();

    const Album& album = *mAlbums->at(index.row());

    switch(role){
        case Roles::IdRole:
            return album.id();
        case Roles::NameRole:
        case Qt::DisplayRole:
            return album.name();
        default:
            return QVariant();
    }
}

// allows roles names to be accessed via QML
QHash<int,QByteArray> AlbumModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";
    return roles;
}

QModelIndex AlbumModel::addAlbum(const Album& album){

    int rowIndex = rowCount();

    //wrap data modification, triggers signals for view
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<Album> newAlbum(new Album(album));
    mDb.albumDao.addAlbum(*newAlbum);
    mAlbums->push_back(move(newAlbum));
    endInsertRows();

    return index(rowIndex,0);
}

//called when view want to update data, return if update successful
bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role){

    if(!isIndexValid(index) || role != Roles::NameRole){
        return false;
    }

    Album& album = *mAlbums->at(index.row());

    //update name value
    album.setName(value.toString());
    mDb.albumDao.updateAlbum(album);

    //notify anyone that a row changed for the given indices
    emit dataChanged(index, index);

    return true;
}

//remove row data, starting row , number to delete, parent of row
bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent){

    if(row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()){
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;

    //loop and delete rows left
    while(countLeft--){
        const Album& album = *mAlbums->at(row + countLeft);
        //delete from database
        mDb.albumDao.removeAlbum(album.id());
    }

    mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + row + count);
    endRemoveRows();
    return true;
}




