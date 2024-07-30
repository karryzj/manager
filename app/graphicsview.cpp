#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QMenuBar>
#include <QAction>
#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), m_scaleFactor(1.15)
{

}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    // 将视图中的坐标转换为场景坐标
    QPointF scenePos = mapToScene(pos);
    //QString statusMsg = QString("鼠标位置：(%1, %2)").arg(scenePos.x()).arg(scenePos.y());
    emit mouseMoved(scenePos);

    // 右侧区域的阈值，比如右侧10%区域
    int rightAreaThreshold = width() * 0.1;
    if (event->pos().x() < width() - rightAreaThreshold)
    {
        emit mouseLeaveRightArea();
    }
    //QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu contextMenu(this);
    QAction *popupAction = contextMenu.addAction("弹出悬浮窗");

    connect(popupAction, &QAction::triggered, this, &GraphicsView::showPopupWindow);

    contextMenu.exec(event->globalPos());
}

void GraphicsView::showPopupWindow()
{
    // 创建一个悬浮窗口
    QDialog *popup = new QDialog(this);
    popup->setWindowTitle("悬浮窗");
    popup->resize(200, 100);

    // 添加内容到悬浮窗口
    QLabel *label = new QLabel("这是一个悬浮窗", popup);
    QVBoxLayout *layout = new QVBoxLayout(popup);
    layout->addWidget(label);

    // 设置悬浮窗为非模态
    popup->setWindowModality(Qt::NonModal);
    popup->show();
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        // 放大
        scale(m_scaleFactor, m_scaleFactor);
    }
    else
    {
        // 缩小
        scale(1.0 / m_scaleFactor, 1.0 / m_scaleFactor);
    }
}
