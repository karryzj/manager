#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#include "pdk_info.h"

class ListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListItemWidget(const BorderStyle &style, const QString &text, QWidget *parent = nullptr);

signals:
};

#endif // LISTITEMWIDGET_H
