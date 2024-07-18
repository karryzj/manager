#ifndef STYLEFRAME_H
#define STYLEFRAME_H

#include <QFrame>
#include <QObject>
#include "pdk_info.h"

class StyleFrame : public QFrame
{
    Q_OBJECT
public:
    explicit StyleFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    StyleFrame(BorderStyle style, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void SetStyle(const BorderStyle &style)
    {
        m_style = style;
    }

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    BorderStyle m_style;

signals:
    void dataChanged(const BorderStyle &style);
};

#endif // STYLEFRAME_H
