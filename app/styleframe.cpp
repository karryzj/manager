#include "styleframe.h"
#include "styledialog.h"
#include "pdk_info.h"
#include <QDebug>
#include <QPainter>

StyleFrame::StyleFrame(QWidget *parent, Qt::WindowFlags f) : QFrame(parent)
{
    setGeometry(50, 50, 200, 200);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Plain);
    setLineWidth(2);
    setFrameStyle(QFrame::Box | QFrame::Plain);
}

StyleFrame::StyleFrame(BorderStyle style, QWidget *parent, Qt::WindowFlags f):QFrame(parent), m_style(style)
{
    setGeometry(50, 50, 200, 200);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Plain);
    setLineWidth(2);
    setFrameStyle(QFrame::Box | QFrame::Plain);
    update();
}

void StyleFrame::mouseDoubleClickEvent(QMouseEvent *event)
{
    StyleDialog dialog(m_style);
    if (dialog.exec() == QDialog::Accepted)
    {
        BorderStyle custom_style = dialog.GetData();
        if (m_style != custom_style)
        {
            update();
            m_style = custom_style;
            emit dataChanged(custom_style);
        }
    }
}

void StyleFrame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter border_painter(this);
    border_painter.setRenderHint(QPainter::Antialiasing);

    // 设置虚线的画笔
    // 获取颜色的RGB值
    int r = (m_style.border_color >> 16) & 0xff;
    int g = (m_style.border_color >> 8) & 0xff;
    int b = (m_style.border_color) & 0xff;

    QPen pen(QColor(r, g, b));  // 设置颜色
    switch (m_style.border_line)
    {
    case 0:
        pen.setStyle(Qt::SolidLine);
        break;
    case 1:
        pen.setStyle(Qt::DashLine);
        break;
    case 2:
        pen.setStyle(Qt::DotLine);
        break;
    case 3:
        pen.setStyle(Qt::DashDotLine);
        break;
    case 4:
        pen.setStyle(Qt::DashDotDotLine);
        break;
    default:
        break;
    }
    border_painter.setPen(pen);

    // 绘制矩形的边框
    border_painter.drawRect(rect());

    QPainter painter(this);

    // 设置画笔样式
    // 获取颜色的RGB值
    int red = (m_style.fill_color >> 16) & 0xff;
    int green = (m_style.fill_color >> 8) & 0xff;
    int blue = (m_style.fill_color) & 0xff;

    painter.setPen(QColor(red, green, blue));

    int gridSize = 10; // 网格大小
    int width = this->width();
    int height = this->height();
    int numLines = qMax( width,height)  / gridSize; // 计算线的数量，取宽高中的最大值

    switch (m_style.fill_line)
    {
    case 0:

        break;
    case 1:
        // 绘制水平线条
        for (int y = 0; y <= height; y += gridSize)
        {
            painter.drawLine(0, y, width, y);
        }
        break;
    case 2:
        // 绘制垂直线条
        for (int x = 0; x <= width; x += gridSize)
        {
            painter.drawLine(x, 0, x, height);
        }
        break;
    case 3:
        // 绘制垂直线条
        for (int x = 0; x <= width; x += gridSize)
        {
            painter.drawLine(x, 0, x, height);
        }

        // 绘制水平线条
        for (int y = 0; y <= height; y += gridSize)
        {
            painter.drawLine(0, y, width, y);
        }
        break;
    case 4:
        // int numLines = qMax( width,height)  / gridSize;
        for (int i = 0; i <= numLines*2; ++i)
        {
            int x1 = i * gridSize;
            int y1 = 0;
            int x2 = 0;
            int y2 = i * gridSize;

            painter.drawLine(x1, y1, x2, y2); // 绘制从左上到右下的斜线
        }
        break;
    case 5:
        // int numLines = qMax( width,height)  / gridSize;
        for (int i = 0; i <= numLines*2; ++i)
        {
            int x3 = 0;
            int y3 = height - i * gridSize;
            int x4 = i * gridSize;
            int y4 = height;
            painter.drawLine(x3, y3, x4, y4);
        }
        break;
    case 6:
        // int numLines = qMax( width,height)  / gridSize;
        for (int i = 0; i <= numLines*2; ++i)
        {
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
