#include "bitmaskstorage.h"

#include <QFile>
#include <QTextStream>

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
    storage_.push_back(qMakePair(std::move(name), Mask(w, h)));
    endInsertRows();
    return true;
}

bool
BitMaskStorage::removeMask(int index) {
    if (index < 0 || index >= storage_.size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), index, index);
    storage_.remove(index);
    endRemoveRows();
    return true;
}

QString
BitMaskStorage::loadFromFile(const QString &fileName) {
    auto file = QFile(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Cannot open file!";
    QTextStream in(&file);
    beginRemoveRows(QModelIndex(), 0, storage_.size());
    storage_.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, 0);
    while(!in.atEnd()) {
        QString string = in.readLine();
        if (string.length() == 0) break;
        QTextStream ss(&string);
        QString name;
        ss >> name;
        ss >> name;
        ss >> name;
        Mask mask;
        ss >> mask;
        storage_.push_back(qMakePair(std::move(name), std::move(mask)));
    }
    endInsertRows();
    return "";
}

QString
BitMaskStorage::saveToFile(const QString &fileName) const {
    auto file = QFile(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return "Cannot open file to save!";
    QTextStream out(&file);
    for(const auto& item: storage_) {
        out << "const McuGui::Mask " << item.first << " " << item.second.toString() << ";" << '\n';
    }
    return "";
}
