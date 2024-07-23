#include "pdkitemmodel.h"
#include <QContextMenuEvent>
#include <QDebug>

PdkItemModel::PdkItemModel(int rows, int columns, QObject *parent)
    : QStandardItemModel(rows, columns, parent)
{
    // 初始化模型数据和右键菜单
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QStandardItem *item = new QStandardItem(QString("Item %1,%2").arg(row).arg(col));
            setItem(row, col, item);
            createContextMenu(row, col);
        }
    }
}

PdkItemModel::~PdkItemModel()
{

}

void PdkItemModel::createContextMenu(int row, int col)
{
    QMenu *menu = new QMenu();
    QAction *action1 = new QAction("Action 1", this);
    QAction *action2 = new QAction("Action 2", this);

    connect(action1, &QAction::triggered, [=](){
        qDebug() << "Action 1 triggered for cell" << row << col;
    });

    connect(action2, &QAction::triggered, [=](){
        qDebug() << "Action 2 triggered for cell" << row << col;
    });

    menu->addAction(action1);
    menu->addAction(action2);

    m_context_menus[qMakePair(row, col)] = menu;
}

QMenu *PdkItemModel::getContextMenu(int row, int col) const
{
    return m_context_menus.value(qMakePair(row, col), nullptr);
}
