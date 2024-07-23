#include "customlistdelegate.h"
#include <QColorDialog>

CustomListDelegate::CustomListDelegate(QObject *parent) : QStyledItemDelegate (parent)
{}

void CustomListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QColor color = index.data(Qt::DecorationRole).value<QColor>();

        // 绘制Frame
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawRect(option.rect.left(), option.rect.top(), 20, option.rect.height());
        painter->restore();

        // 绘制文本
        QStyledItemDelegate::paint(painter, option, index);
    }
}

bool CustomListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            // 更改颜色
            QColor newColor = QColorDialog::getColor(Qt::white, nullptr, "Select Color");
            if (newColor.isValid())
            {
                model->setData(index, newColor, Qt::DecorationRole);
            }
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
