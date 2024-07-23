#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QListWidget>
#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include "pdk_manage_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mp_ui(new Ui::MainWindow)
{
    mp_ui->setupUi(this);
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("文件");
    QMenu *editMenu = menuBar->addMenu("编辑");

    QAction *newAction = new QAction(QIcon(":/img/1.png"), "新建", this);
    QAction *openAction = new QAction(QIcon(":/img/2.png"), "打开", this);
    QAction *saveAction = new QAction(QIcon(":/img/3.png"), "保存", this);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    QAction *copyAction = new QAction(QIcon(":/img/4.png"), "复制", this);
    QAction *pasteAction = new QAction(QIcon(":/img/5.png"),"粘贴", this);
    QAction *pdkAction = new QAction(QIcon(":/img/6.png"),"图层管理", this);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(pdkAction);

    setMenuBar(menuBar);

    // 创建工具栏
    QToolBar *toolBar = addToolBar("工具栏");
    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(copyAction);
    toolBar->addAction(pasteAction);
    toolBar->addAction(pdkAction);

    // 设置工具栏图标大小
    toolBar->setIconSize(QSize(32, 32));
    // 设置工具按钮样式，使文字显示在图标下方
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 创建状态栏
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    // 创建用于显示坐标的标签
    mp_mouse_pos_label = new QLabel("坐标：", this);
    statusBar->addPermanentWidget(mp_mouse_pos_label);
//    statusBar->showMessage("就绪");

    QDockWidget *dockWidgetTop = new QDockWidget("左侧框1", this);
    QTabWidget *tabWidget = new QTabWidget(dockWidgetTop);
    tabWidget->setTabPosition(QTabWidget::South);

    QListWidget *listWidget1 = new QListWidget(tabWidget);
    listWidget1->addItem("Tab1 项目1");
    listWidget1->addItem("Tab1 项目2");
    tabWidget->addTab(listWidget1, "Tab1");

    QListWidget *listWidget2 = new QListWidget(tabWidget);
    listWidget2->addItem("Tab2 项目1");
    listWidget2->addItem("Tab2 项目2");
    tabWidget->addTab(listWidget2, "Tab2");

    dockWidgetTop->setWidget(tabWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidgetTop);

    // 创建左侧下方框（Dock Widget）
    QDockWidget *dockWidgetBottom = new QDockWidget("左侧框2", this);
    QListWidget *listWidgetBottom = new QListWidget(dockWidgetBottom);
    listWidgetBottom->addItem("选项A");
    listWidgetBottom->addItem("选项B");
    listWidgetBottom->addItem("选项C");
    dockWidgetBottom->setWidget(listWidgetBottom);

    // 将第二个框放置在第一个框下面
    splitDockWidget(dockWidgetTop, dockWidgetBottom, Qt::Vertical);
//    tabifyDockWidget(dockWidgetTop1, dockWidgetTop2); // 将第二个框和第一个框合并为选项卡式布局

    // 创建右侧框（Dock Widget）
    mp_dockwidget_right = new RightDockWidget("右侧框", this);

    addDockWidget(Qt::RightDockWidgetArea, mp_dockwidget_right);

    // 创建主界面的图形视图（Graphics View）
    QGraphicsScene *scene = new QGraphicsScene(this);
    mp_graphics_view = new GraphicsView(scene, this);

    // 向场景中添加示例项目
    QGraphicsTextItem *textItem = scene->addText("Hello, QGraphicsView!");
    textItem->setPos(50, 50); // 设置文本位置

    // 设置中央小部件
    setCentralWidget(mp_graphics_view);

    // 设置主窗口标题
    setWindowTitle("主窗口示例");

    connect(openAction, &QAction::triggered, this, &MainWindow::OpenFile);
    connect(pdkAction, &QAction::triggered, this, &MainWindow::PdkManage);
    // 连接图形视图的鼠标移动信号到更新状态栏的槽函数
    connect(mp_graphics_view, &GraphicsView::mouseMoved, this, &MainWindow::UpdateMousePosition);

    // 最大化主窗口
    showMaximized();

    // 设置主窗口的图标
    setWindowIcon(QIcon(":/img/12.png"));

}

void MainWindow::UpdateMousePosition(const QPointF &scenePos)
{
    // 更新状态栏显示鼠标位置信息
    QString statusMsg = QString("鼠标位置：(%1, %2)").arg(scenePos.x()).arg(scenePos.y());
    mp_mouse_pos_label->setText(statusMsg);
}

void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       "打开文本文件",
                       QDir::homePath(),
                       "文本文件 (*.gds);;所有文件 (*.*)");

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString fileContent = in.readAll();
            file.close();

            // 在这里可以根据需要处理文件内容，例如显示在 QGraphicsView 中
            QMessageBox::information(this, "文件内容", fileContent);
        }
        else
        {
            QMessageBox::warning(this, "错误", "无法打开文件: " + file.errorString());
        }
    }
}

void MainWindow::PdkManage()
{
    PdkManageDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        // 如果需要处理对话框关闭后的逻辑，可以在这里添加
    }
}

MainWindow::~MainWindow()
{
    delete mp_ui;
}

