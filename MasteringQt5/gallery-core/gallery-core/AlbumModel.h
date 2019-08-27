#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "Album.h"
#include "DatabaseManager.h"

class GALLERYCORESHARED_EXPORT  AlbumModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles{
      IdRole = Qt::UserRole + 1,
        NameRole,
    };

    AlbumModel(QObject* parent = nullptr);

    QModelIndex addAlbum(const Album& album);

    /**
     * @brief get size of album list
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief get specific info about display data
     * @param index in list
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief update the data
     * @param index
     * @param value
     * @param role
     * @return
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    /**
     * @brief delete row data
     * @param row
     * @param count
     * @param parent
     * @return
     */
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    /**
     * @brief indicate name for each role to framework
     * @return
     */
    QHash<int, QByteArray> roleNames() const override;

private:

    bool isIndexValid(const QModelIndex& index) const;

    //link to database, communicate with data layer through this
    DatabaseManager& mDb;
    //buffer to avoid excessive database access
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> mAlbums;
};

#endif // ALBUMMODEL_H
