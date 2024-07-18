#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(int type, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    int m_type;

};

#endif // GRIDWIDGET_H
