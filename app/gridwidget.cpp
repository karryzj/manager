#include "gridwidget.h"
#include <QPainter>

GridWidget::GridWidget(int type, QWidget *parent)
    : QWidget(parent), m_type(type)
{

}

GridWidget::~GridWidget()
{

}

void GridWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 设置画笔样式
    painter.setPen(Qt::black);

    int gridSize = 20; // 网格大小
    int width = this->width();
    int height = this->height();
    int numLines = qMax( width, height)  / gridSize; // 计算线的数量，取宽高中的最大值

    switch (m_type) {
        case 0:

            break;
        case 1:
            // 绘制水平线条
            for (int y = 0; y <= height; y += gridSize) {
                painter.drawLine(0, y, width, y);
            }
            break;
        case 2:
            // 绘制垂直线条
            for (int x = 0; x <= width; x += gridSize) {
                painter.drawLine(x, 0, x, height);
            }
            break;
        case 3:
            // 绘制垂直线条
            for (int x = 0; x <= width; x += gridSize) {
                painter.drawLine(x, 0, x, height);
            }

            // 绘制水平线条
            for (int y = 0; y <= height; y += gridSize) {
                painter.drawLine(0, y, width, y);
            }
            break;
        case 4:
            // int numLines = qMax( width,height)  / gridSize; // 计算线的数量，取宽高中的最大值
            for (int i = 0; i <= numLines * 2; ++i) {
                int x1 = i * gridSize;
                int y1 = 0;
                int x2 = 0;
                int y2 = i * gridSize;

                painter.drawLine(x1, y1, x2, y2); // 绘制从左上到右下的斜线
            }
            break;
        case 5:
            // int numLines = qMax( width,height)  / gridSize; // 计算线的数量，取宽高中的最大值
            for (int i = 0; i <= numLines * 2; ++i) {
                int x3 = 0;
                int y3 = height - i * gridSize;
                int x4 = i * gridSize;
                int y4 = height;
                painter.drawLine(x3, y3, x4, y4);
            }
            break;
        case 6:
            // int numLines = qMax( width,height)  / gridSize; // 计算线的数量，取宽高中的最大值
            for (int i = 0; i <= numLines * 2; ++i) {
                int x1 = i * gridSize;
                int y1 = 0;
                int x2 = 0;
                int y2 = i * gridSize;

                painter.drawLine(x1, y1, x2, y2); // 绘制从左上到右下的斜线
                int x3 = 0;
                int y3 = height - i * gridSize;
                int x4 = i * gridSize;
                int y4 = height;
                painter.drawLine(x3, y3, x4, y4);
            }
            break;
        default:
            break;
    }
}
