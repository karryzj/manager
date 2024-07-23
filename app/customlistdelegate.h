#ifndef CUSTOMLISTDELEGATE_H
#define CUSTOMLISTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>

class CustomListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

};

#endif // CUSTOMLISTDELEGATE_H
