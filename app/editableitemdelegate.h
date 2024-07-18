#ifndef EDITABLEITEMDELEGATE_H
#define EDITABLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class EditableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    EditableItemDelegate(QObject *parent = nullptr);

    // Override editing functions
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // EDITABLEITEMDELEGATE_H
