#ifndef PDKITEMMODEL_H
#define PDKITEMMODEL_H

#include <QStandardItemModel>
#include <QAbstractListModel>
#include <QMenu>
#include "pdk_info.h"

class PdkItemModel final: public QStandardItemModel
{
public:
    PdkItemModel(int rows, int columns, QObject *parent = nullptr);
    ~PdkItemModel(void) override;

public:
    QMenu *getContextMenu(int row, int col) const;

private:
    void createContextMenu(int row, int col);

private:
    QMap<QPair<int, int>, QMenu *> m_context_menus;
    QList<PdkInfo*> m_pdk_manage;
};

#endif // PDKITEMMODEL_H
