#include "mainwindow.h"

#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    toolbar = new QToolBar(this);
    action_open = toolbar->addAction(QIcon(":/images/open.png"), "导入");
    action_save = toolbar->addAction(QIcon(":/images/save.png"), "保存");
    action_saveas = toolbar->addAction(QIcon(":/images/save_as.png"), "另存为");
    action_hist = toolbar->addAction(QIcon(":/images/hist.png"),"直方图");
    toolbar->addSeparator();
    action_smooth = toolbar->addAction(QIcon(":/images/blur.png"),"平滑");
    action_sharpen = toolbar->addAction(QIcon(":/images/sharpen.png"),"锐化");
    action_grayscale = toolbar->addAction(QIcon(":/images/intensity.png"),"灰度变换");
    action_geometric = toolbar->addAction(QIcon(":/images/trans.png"),"几何变换");
    action_morph = toolbar->addAction(QIcon(":/images/morph.png"),"形态学");
    action_seg = toolbar->addAction(QIcon(":/images/seg.png"),"分割");
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(action_open, SIGNAL(triggered()), this, SLOT(on_actionOpen_triggered()));
    connect(action_saveas, SIGNAL(triggered()), this, SLOT(on_actionSave_As_triggered()));
    connect(action_save, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    connect(action_smooth, SIGNAL(triggered()), this, SLOT(on_actionSmooth_triggered()));
    connect(action_sharpen, SIGNAL(triggered()), this, SLOT(on_actionSharpen_triggered()));
    connect(action_hist, SIGNAL(triggered()), this, SLOT(on_actionHist_triggered()));
    connect(action_grayscale, SIGNAL(triggered()), this, SLOT(on_actionGrayscale_triggered()));
    connect (action_geometric, SIGNAL(triggered()), this, SLOT(on_actionGeometric_triggered()));
    connect(action_morph, SIGNAL(triggered()), this, SLOT(on_actionMorph_triggered()));
    connect(action_seg, SIGNAL(triggered()), this, SLOT(on_actionSeg_triggered()));

    scene = new QGraphicsScene(this);
    view = new GraphicsView(scene, this);
    hist_label = new HistLabel(this);
    hist_label->setMinimumHeight(150);

    dock_used = new QDockWidget(tr("已选操作"));
    dock_func = new QDockWidget(tr("图像操作"));
    dock_attr = new QDockWidget(tr("属性"));
    dock_hist = new QDockWidget(tr("直方图"));
    dock_used->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock_func->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock_func->setTitleBarWidget(new QWidget());
    dock_attr->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock_hist->setFeatures(QDockWidget::AllDockWidgetFeatures);

    useListWidget = new UsedListWidget(this);
    stacked_widget = new QStackedWidget;
    smooth_table_widget = new SmoothTableWidget(this);
    stacked_widget->addWidget(smooth_table_widget);
    sharpen_table_widget = new SharpenTableWidget(this);
    stacked_widget->addWidget(sharpen_table_widget);
    grayscale_table_widget = new GrayscaleTableWidget(this);
    stacked_widget->addWidget(grayscale_table_widget);
    geometric_table_widget = new GeometricTableWidget(this);
    stacked_widget->addWidget(geometric_table_widget);
    morph_table_widget = new MorphTableWidget(this);
    stacked_widget->addWidget(morph_table_widget);
    seg_table_widget = new SegTableWidget(this);
    stacked_widget->addWidget(seg_table_widget);
    stacked_widget->setMinimumWidth(200);
    stacked_widget->setCurrentIndex(-1);

    dock_used->setWidget(useListWidget);
    dock_func->setWidget(toolbar);
    dock_attr->setWidget(stacked_widget);
    dock_attr->setVisible(false);
    dock_hist->setWidget(hist_label);
    dock_hist->setVisible(false);

    setCentralWidget(view);
    addDockWidget(Qt::TopDockWidgetArea, dock_func);
    addDockWidget(Qt::RightDockWidgetArea, dock_used);
    addDockWidget(Qt::RightDockWidgetArea, dock_attr);
    addDockWidget(Qt::RightDockWidgetArea, dock_hist);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_actionOpen_triggered()
{
        // Automatically detects the current user's home directory
        // And then wait the user to select one image
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                 tr("All Files (*);;"
                                                    "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                    "Image BPM (*.bpm);;"
                                                    "Image GIF (*.gif);;"
                                                    "Image JPG (*.jpg);;"
                                                    "Image JPEG (*.jpeg);;"
                                                    "Image PNG (*.png);;"
                                                    "Image PPM (*.ppm);;"
                                                    "Image XBM (*.xbm);;"
                                                    "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL),
                                  tr("Unable to open image."));
            return;
        }

        // delete previous image
        MainWindow:: clean_image();

        // upload image
        info = new QFileInfo(imagePath);

        QPixmap mainpixmap(imagePath);
        src_img = mainpixmap.toImage();
        src_img = src_img.convertToFormat(QImage::Format_Grayscale8,Qt::AutoColor);
        cur_img = src_img.copy();
        update_image();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(src_img.isNull())
        return ;
    QString path = info->filePath();
    if (!path.isEmpty()) {
        view->_photo->pixmap().save(path);
    }
}

void MainWindow::on_actionSave_As_triggered()
{

    QString newPath = QFileDialog::getSaveFileName(this, tr("Save image"), QString(),
            tr("All files (*);;"
               "Image BPM (*.bpm);;"
               "Image GIF (*.gif);;"
               "Image JPG (*.jpg);;"
               "Image JPEG (*.jpeg);;"
               "Image PNG (*.png);;"
               "Image PPM (*.ppm);;"
               "Image XBM (*.xbm);;"
               "Image XPM (*.xpm);;"));

    if (!newPath.isEmpty()) {

        QFile file(newPath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("Unable to save image."));
            return;
        }

        //Save image to new path
        view->_photo->pixmap().save(newPath);
    }
}

/******************************************************************************
 *                              获得当前用户的家目录
 *****************************************************************************/
QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}

void MainWindow::clean_image()
{
    scene->clear();
    view->resetTransform();
}

void MainWindow::on_actionSmooth_triggered()
{
    useListWidget->addItem(new SmoothItem("平滑操作"));
    update_image();
}

void MainWindow::on_actionSharpen_triggered()
{
    useListWidget->addItem(new SharpenItem("锐化操作"));
    update_image();
}

void MainWindow::on_actionGrayscale_triggered()
{
    useListWidget->addItem(new GrayscaleItem("灰度变换"));
    update_image();
}

void MainWindow::on_actionGeometric_triggered()
{
    useListWidget->addItem(new GeometricItem("几何变换"));
    update_image();
}

void MainWindow::on_actionMorph_triggered()
{
    useListWidget->addItem(new MorphItem("形态学"));
    update_image();
}

void MainWindow::on_actionSeg_triggered()
{
    useListWidget->addItem(new SegItem("分割"));
    update_image();
}

void MainWindow::update_image()
{
    if(src_img.isNull()) {return;}
    cur_img = src_img.copy();
    for(int i = 0; i < useListWidget->count(); i++) {
        MyItem *item;
        item = (MyItem *)useListWidget->item(i);
        cur_img = item->item_process_img(cur_img);
    }
    view->show_image(cur_img);
    hist_label->update();
}

void MainWindow::on_actionHist_triggered()
{
    if(cur_img.isNull()) {return;}
    hist_label->update();//maybe useless
    dock_hist->setVisible(true);
}
