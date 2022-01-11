#include "tablewidget.h"
#include "mainwindow.h"

TableWidget::TableWidget(QWidget *parent)
{
    mainwindow = parent;
    setShowGrid(true);
    setAlternatingRowColors(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->sectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setStretchLastSection(true);
    setFocusPolicy(Qt::NoFocus);
}

void TableWidget::update_item()
{
    ParamsItem p;
    p = get_params();
    MainWindow *window;
    window = (MainWindow *)mainwindow;
    MyItem *item;
    item = (MyItem *)window->useListWidget->currentItem();
    item->update_params(p);
    window->update_image();
}

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = { "高斯滤波","均值滤波","中值滤波" };
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");

    ksize_spinBox = new QSpinBox;
    ksize_spinBox->setObjectName("ksize");
    ksize_spinBox->setMinimum(1);
    ksize_spinBox->setSingleStep(1);

    ksigma_spinBox = new QSpinBox;
    ksigma_spinBox->setObjectName("ksigma");
    ksigma_spinBox->setMinimum(1);
    ksigma_spinBox->setSingleStep(1);

    this->setColumnCount(2);
    this->setRowCount(3);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);
    QTableWidgetItem *title_ksize;
    title_ksize = new QTableWidgetItem("核半径");
    this->setItem(1,0,title_ksize);
    this->setCellWidget(1,1,ksize_spinBox);
    QTableWidgetItem *title_ksigma;
    title_ksigma = new QTableWidgetItem("高斯模糊sigma");
    this->setItem(2,0,title_ksigma);
    this->setCellWidget(2,1,ksigma_spinBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
    connect(ksize_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
    connect(ksigma_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
}

void SmoothTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
    ksize_spinBox->setValue(p.getKsizeValue());
    ksigma_spinBox->setValue(p.getKsigmaValue());
}

ParamsItem SmoothTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    p.setKsizeValue(ksize_spinBox->value());
    p.setKsigmaValue(ksigma_spinBox->value());
    return p;
}

SharpenTableWidget::SharpenTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = { "Sobel滤波x方向","Sobel滤波y方向","Laplace滤波" };
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");

    this->setColumnCount(2);
    this->setRowCount(1);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
}

void SharpenTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
}

ParamsItem SharpenTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    return p;
}

GrayscaleTableWidget::GrayscaleTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = {"设置窗位窗宽", "gamma变换"};
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");//maybe useless

    wl_spinBox = new QSpinBox;
    wl_spinBox->setObjectName("wl");
    wl_spinBox->setMinimum(0);
    wl_spinBox->setMaximum(255);
    wl_spinBox->setSingleStep(1);

    ww_spinBox = new QSpinBox;
    ww_spinBox->setObjectName("ww");
    ww_spinBox->setMinimum(1);
    ww_spinBox->setMaximum(255);
    ww_spinBox->setSingleStep(1);

    gamma_dspinBox = new QDoubleSpinBox;
    gamma_dspinBox->setObjectName("gamma");
    gamma_dspinBox->setMinimum(0);
    gamma_dspinBox->setSingleStep(0.1);
    gamma_dspinBox->setDecimals(3);

    this->setColumnCount(2);
    this->setRowCount(4);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);
    QTableWidgetItem *title_wl;
    title_wl = new QTableWidgetItem("窗位");
    this->setItem(1,0,title_wl);
    this->setCellWidget(1,1,wl_spinBox);
    QTableWidgetItem *title_ww;
    title_ww = new QTableWidgetItem("窗宽");
    this->setItem(2,0,title_ww);
    this->setCellWidget(2,1,ww_spinBox);
    QTableWidgetItem *title_gamma;
    title_gamma = new QTableWidgetItem("gamma");
    this->setItem(3,0,title_gamma);
    this->setCellWidget(3,1,gamma_dspinBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
    connect(wl_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
    connect(ww_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
    connect(gamma_dspinBox, SIGNAL(valueChanged(double)), this, SLOT(update_item()));
}

void GrayscaleTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
    wl_spinBox->setValue(p.getWlValue());
    ww_spinBox->setValue(p.getWwValue());
    gamma_dspinBox->setValue(p.getGammaValue());
}

ParamsItem GrayscaleTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    p.setWlValue(wl_spinBox->value());
    p.setWwValue(ww_spinBox->value());
    p.setGammaValue(gamma_dspinBox->value());
    return p;
}

GeometricTableWidget::GeometricTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = {"保持不变","左右翻转","上下翻转","顺时针旋转90度","逆时针旋转90度"};
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");

    this->setColumnCount(2);
    this->setRowCount(1);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
}

void GeometricTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
}

ParamsItem GeometricTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    return p;
}

MorphTableWidget::MorphTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = {"腐蚀","膨胀","开运算","闭运算","提取边缘"};
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");

    kshape_comBox = new QComboBox;
    QStringList kshape_items = {"方形","圆形"};
    kshape_comBox->addItems(kshape_items);
    kshape_comBox->setObjectName("kshape");

    ksize_spinBox = new QSpinBox;
    ksize_spinBox->setObjectName("ksize");
    ksize_spinBox->setMinimum(1);
    ksize_spinBox->setSingleStep(1);

    this->setColumnCount(2);
    this->setRowCount(3);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);
    QTableWidgetItem *title_kshape;
    title_kshape = new QTableWidgetItem("卷积核");
    this->setItem(1,0,title_kshape);
    this->setCellWidget(1,1,kshape_comBox);
    QTableWidgetItem *title_ksize;
    title_ksize = new QTableWidgetItem("核半径");
    this->setItem(2,0,title_ksize);
    this->setCellWidget(2,1,ksize_spinBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
    connect(kshape_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
    connect(ksize_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
}

void MorphTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
    kshape_comBox->setCurrentIndex(p.getKshapeValue());
    ksize_spinBox->setValue(p.getKsizeValue());
}

ParamsItem MorphTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    p.setKshapeValue(kshape_comBox->currentIndex());
    p.setKsizeValue(ksize_spinBox->value());
    return p;
}

SegTableWidget::SegTableWidget(QWidget *parent)
    :TableWidget(parent)
{
    kind_comBox = new QComboBox;
    QStringList kind_items = {"手动阈值","Otsu阈值"};
    kind_comBox->addItems(kind_items);
    kind_comBox->setObjectName("kind");

    thres1_spinBox = new QSpinBox;
    thres1_spinBox->setObjectName("thres1");
    thres1_spinBox->setMinimum(0);
    thres1_spinBox->setMaximum(255);
    thres1_spinBox->setSingleStep(1);

    thres2_spinBox = new QSpinBox;
    thres2_spinBox->setObjectName("thres2");
    thres2_spinBox->setMinimum(0);
    thres2_spinBox->setMaximum(255);
    thres2_spinBox->setSingleStep(1);

    this->setColumnCount(2);
    this->setRowCount(3);
    QTableWidgetItem *title_kind;
    title_kind = new QTableWidgetItem("类型");
    this->setItem(0,0,title_kind);
    this->setCellWidget(0,1,kind_comBox);
    QTableWidgetItem *title_thres1;
    title_thres1 = new QTableWidgetItem("阈值1");
    this->setItem(1,0,title_thres1);
    this->setCellWidget(1,1,thres1_spinBox);
    QTableWidgetItem *title_thres2;
    title_thres2 = new QTableWidgetItem("阈值2");
    this->setItem(2,0,title_thres2);
    this->setCellWidget(2,1,thres2_spinBox);

    connect(kind_comBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_item()));
    connect(thres1_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
    connect(thres2_spinBox, SIGNAL(valueChanged(int)), this, SLOT(update_item()));
}

void SegTableWidget::update_params(ParamsItem p)
{
    kind_comBox->setCurrentIndex(p.getKindValue());
    thres1_spinBox->setValue(p.getThres1Value());
    thres2_spinBox->setValue(p.getThres2Value());
}

ParamsItem SegTableWidget::get_params()
{
    ParamsItem p;
    p.setKindValue(kind_comBox->currentIndex());
    p.setThres1Value(thres1_spinBox->value());
    p.setThres2Value(thres2_spinBox->value());
    return p;
}
