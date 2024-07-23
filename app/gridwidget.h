#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidget final : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(int type, QWidget *parent = nullptr);
    ~GridWidget(void) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_type;
};

#endif // GRIDWIDGET_H
