#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLabel>
#include <QTimer>
#include "graphicsview.h"
#include "rightdockwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void) override;

// protected:
//     bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void OpenFile();
    void PdkManage();
    void ShowPopupWindow();
    void StartAutoHideTimer();
    void AutoHideRightDock();
    void ShowRightDock();

private slots:
    void UpdateMousePosition(const QPointF &scenePos);

private:
    Ui::MainWindow *mp_ui;
    GraphicsView *mp_graphics_view;
    QLabel *mp_mouse_pos_label;
    RightDockWidget *mp_dockwidget_right;
    // QTimer *mp_auto_hide_timer;
};
#endif // MAINWINDOW_H
