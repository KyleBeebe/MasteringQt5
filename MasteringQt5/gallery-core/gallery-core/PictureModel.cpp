#include "PictureModel.h"

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures(new vector<unique_ptr<Picture>>())
{
    // connect signal to deletePicturesForAlbum() slot
    connect(&albumModel, &AlbumModel::rowsRemoved,
                this, &PictureModel::deletePicturesForAlbum);
}


void PictureModel::setAlbumId(int albumId){
    //reload picturemodel when album changes
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();

}

void PictureModel::loadPictures(int albumId){

    // invalid album id, clear pictures
    if(albumId <= 0){
        mPictures.reset(new std::vector<std::unique_ptr<Picture>>());
        return;
    }

    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}
