#ifndef BITMASKSTORAGE_H
#define BITMASKSTORAGE_H

#include <QAbstractListModel>
#include <QVector>
#include <QPair>

#include "mask.h"

class BitMaskStorage : public QAbstractListModel
{
    Q_OBJECT

    const QString DEFAULT_NAME = "Mask1";
public:
    enum BitMaskRoles
    {
        MaskEditRole = Qt::UserRole + 1,
        MaskViewRole
    };
    BitMaskStorage(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool addNewMask(QString name, uint16_t w, uint16_t h);

private:
    QVector <QPair<QString, Mask>> storage_;

};

#endif // BITMASKSTORAGE_H
