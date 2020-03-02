#include "bitmaskstorage.h"

BitMaskStorage::BitMaskStorage(QObject *parent)
    :QAbstractListModel(parent), storage_({})
{
    storage_.push_back(qMakePair(BitMaskStorage::DEFAULT_NAME, Mask()));
}

int
BitMaskStorage::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : storage_.size();
}

Qt::ItemFlags
BitMaskStorage::
flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    return index.isValid() ? flags | Qt::ItemIsEditable : flags;
}

QVariant
BitMaskStorage::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= storage_.size()) return QVariant();
    if (role == Qt::DisplayRole) {
        return storage_[index.row()].first;
    }

    if (role == BitMaskRoles::MaskViewRole) {
        QVariant value;
        value.setValue(storage_[index.row()].second);
        return value;
    }

    return QVariant();
}

bool
BitMaskStorage::setData(const QModelIndex &index, const QVariant& value, int role) {
    if (index.isValid()) {
        if (role == Qt::EditRole) {
           storage_[index.row()].first = value.value<QString>();
        }
        if (role == BitMaskRoles::MaskEditRole) {
           storage_[index.row()].second = value.value<Mask>();
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool
BitMaskStorage::addNewMask(QString name, uint16_t w, uint16_t h) {
    // TODO: name check
    beginInsertRows(QModelIndex(), storage_.size(), storage_.size());
    storage_.push_back(qMakePair(std::move(name), Mask({10,10,{0x80100200,0x40080100,0x20040080,0x10000000}})));
    endInsertRows();
    return true;
}
