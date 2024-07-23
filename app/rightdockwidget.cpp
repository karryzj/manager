#include "rightdockwidget.h"
#include <QMouseEvent>
#include <QListWidget>
#include <QTimer>

RightDockWidget::RightDockWidget (const QString &title, QWidget *parent)
    : QDockWidget(title, parent), mp_tab_widget(new QTabWidget(this))
{
    setWidget(mp_tab_widget);
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    mp_tab_widget->setTabPosition(QTabWidget::East);

    // 添加两个Tab
    QListWidget *listRightWidget1 = new QListWidget(mp_tab_widget);
    listRightWidget1->addItem("Tab1 项目1");
    listRightWidget1->addItem("Tab1 项目2");
    mp_tab_widget->addTab(listRightWidget1, "Tab1");

    QListWidget *listRightWidget2 = new QListWidget(mp_tab_widget);
    listRightWidget2->addItem("Tab2 项目1");
    listRightWidget2->addItem("Tab2 项目2");
    mp_tab_widget->addTab(listRightWidget2, "Tab2");

    // 安装事件过滤器
    this->installEventFilter(this);
    mp_tab_widget->tabBar()->installEventFilter(this);

    // 使用定时器来检测鼠标是否离开Dock区域
    mp_timer = new QTimer(this);
    mp_timer->setInterval(1000);
    connect(mp_timer, &QTimer::timeout, this, &RightDockWidget::hideDock);
    mp_timer->start(200);
}

bool RightDockWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == mp_tab_widget->tabBar())
    {
        if (event->type() == QEvent::Enter)
        {
            showDock();
        }
        else if (event->type() == QEvent::Leave)
        {
            mp_timer->start();
        }
    }
    return QDockWidget::eventFilter(obj, event);
}

void RightDockWidget::enterEvent(QEvent *event)
{
    showDock();
    QDockWidget::enterEvent(event);
}

void RightDockWidget::leaveEvent(QEvent *event)
{
    mp_timer->start();
    QDockWidget::leaveEvent(event);
}

void RightDockWidget::hideDock()
{
    if (!rect().contains(mapFromGlobal(QCursor::pos())))
    {
        setFixedWidth(mp_tab_widget->tabBar()->width());
    }
}

void RightDockWidget::showDock()
{
    setFixedWidth(300);
    mp_timer->stop();
}
