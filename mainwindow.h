#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDockWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QLabel>
#include "./custom/graphicsview.h"
#include "./custom/tablewidget.h"
#include "./custom/paramsitem.h"
#include "./custom/listwidget.h"

#define WINDOW_CRITICAL "Error~"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsScene *scene;
    GraphicsView *view;
    QFileInfo *info;
    QToolBar *toolbar;
    QAction *action_open;
    QAction *action_save;
    QAction *action_saveas;
    QAction *action_hist;
    QAction *action_smooth;
    QAction *action_sharpen;
    QAction *action_grayscale;
    QAction *action_geometric;
    QAction *action_morph;
    QAction *action_seg;
    QDockWidget *dock_used;
    QDockWidget *dock_func;
    QDockWidget *dock_attr;
    QDockWidget *dock_hist;
    HistLabel *hist_label;
    SmoothTableWidget *smooth_table_widget;
    SharpenTableWidget *sharpen_table_widget;
    GrayscaleTableWidget *grayscale_table_widget;
    GeometricTableWidget *geometric_table_widget;
    MorphTableWidget *morph_table_widget;
    SegTableWidget *seg_table_widget;
    QImage src_img;
    QImage cur_img;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getUserPath();
    void clean_image();
    void show_attr() { dock_attr->setVisible(true);}
    void close_attr() {dock_attr->setVisible(false);}
    QStackedWidget *stacked_widget;
    UsedListWidget *useListWidget;
    void update_image();
    QImage get_cur_img() {return cur_img;}
public slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionHist_triggered();
    void on_actionSmooth_triggered();
    void on_actionSharpen_triggered();
    void on_actionGrayscale_triggered();
    void on_actionGeometric_triggered();
    void on_actionMorph_triggered();
    void on_actionSeg_triggered();
};

#endif // MAINWINDOW_H
