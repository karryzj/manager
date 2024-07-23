#include "pdklistmodel.h"

PdkListModel::PdkListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // Populate m_data with your data
    m_data << "Item 1" << "Item 2" << "Item 3";
}

PdkListModel::~PdkListModel()
{

}

void PdkListModel::setData(const QStringList &data)
{
    m_data = data;
}

int PdkListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}

QVariant PdkListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return m_data[index.row()];
    }

    return QVariant();
}

void PdkListModel::removeItem(int row)
{
    if (row < 0 || row >= m_data.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void PdkListModel::addItem()
{
    int row;
    row = m_data.size();

    beginInsertRows(QModelIndex(), row, row);
    m_data.append("item " + QString(row + 1));
    endInsertRows();
}

bool PdkListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_data.size()) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_data.insert(row, QString()); // Insert empty string, you can modify as needed
    }
    endInsertRows();
    return true;
}

bool PdkListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

// Qt::ItemFlags PdkListModel::flags(const QModelIndex &index) const
// {
//     Qt::ItemFlags flags = QAbstractItemModel::flags(index);
//     if (index.isValid()) {
//         flags |= Qt::ItemIsEditable;
//     }
//     return flags;
// }
