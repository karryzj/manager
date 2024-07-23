#ifndef RIGHTDOCKWIDGET_H
#define RIGHTDOCKWIDGET_H

#include <QDockWidget>
#include <QObject>
#include <QWidget>
#include <QTableWidget>

class RightDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit RightDockWidget (const QString &title, QWidget *parent = nullptr);
    ~RightDockWidget() override {};

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    void setCollapsed(bool collapsed);
    bool isCollapsed() const;

    QTabWidget *mp_tab_widget;
    QTimer *mp_timer;

private slots:
    void hideDock();
    void showDock();
};

#endif // RIGHTDOCKWIDGET_H
