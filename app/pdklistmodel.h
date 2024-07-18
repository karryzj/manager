#ifndef PDKLISTMODEL_H
#define PDKLISTMODEL_H

#include <QAbstractListModel>

class PdkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PdkListModel(QObject *parent = nullptr);
    void SetData(const QStringList &data) {m_data = data;}

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Add method to insert an item
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add method to set data at specific index
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void removeItem(int row);
    void addItem();

private:
    QStringList m_data;
};


#endif // PDKLISTMODEL_H
