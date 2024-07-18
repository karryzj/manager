#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLabel>

class GraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
            : QGraphicsView(scene, parent) {}

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void showPopupWindow();

signals:
    void mouseMoved(const QPointF &message);
    void mouseLeaveRightArea();
};

#endif // GRAPHICSVIEW_H
