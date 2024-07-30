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
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsView(void) override;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void showPopupWindow(void);

private:
    double m_scaleFactor;

signals:
    void mouseMoved(const QPointF &message);
    void mouseLeaveRightArea(void);
};

#endif // GRAPHICSVIEW_H
