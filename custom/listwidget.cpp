#include "listwidget.h"
#include "mainwindow.h"
#include "tools.h"
#include <QMenu>

UsedListWidget::UsedListWidget(QWidget *parent)
{
    mainwindow = parent;
    setDragEnabled(true);
    setFocusPolicy(Qt::NoFocus);
    setAcceptDrops(true);
    setFlow(QListView::TopToBottom);
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::InternalMove);
    setMinimumWidth(200);
    connect(this, &QListWidget::itemClicked, this, &UsedListWidget::show_attr);
}

void UsedListWidget::contextMenuEvent(QContextMenuEvent *)
{
    MyItem *item;
    item = (MyItem *)this->itemAt(this->mapFromGlobal(QCursor::pos()));
    if (item == NULL) {return;}
    QMenu *menu = new QMenu(this);
    QAction *delete_action = new QAction("删除",this);
    connect(delete_action,&QAction::triggered,this,[item,this]{ delete_item(item);});
    menu->addAction(delete_action);
    menu->move(cursor().pos());
    menu->show();
}

void UsedListWidget::delete_item(MyItem *item)
{
    this->takeItem(this->row(item));
    MainWindow *window;
    window = (MainWindow *)mainwindow;
    window->update_image();
    window->close_attr();
}

void UsedListWidget::show_attr()
{
//    item = (MyItem *)this->itemAt(this->mapFromGlobal(QCursor::pos()));//另一种方法
    MyItem *item;
    item = (MyItem *)this->currentItem();
    int index = item->get_index();
    MainWindow *window;
    window = (MainWindow *)mainwindow;
    window->stacked_widget->setCurrentIndex(index);
    ParamsItem p;
    p = item->get_params();
    TableWidget *table_widget;
    table_widget = (TableWidget *)window->stacked_widget->currentWidget();
    table_widget->update_params(p);
    window->show_attr();
}

MyItem::MyItem(const QString &text, QListWidget *parent)
    :QListWidgetItem(text,parent)
{

}

SmoothItem::SmoothItem(const QString &text, QListWidget *parent)
    :MyItem(text, parent)
{
    this->setIcon(QIcon(":/images/blur.png"));
    params.setKindValue(0);
    params.setKsizeValue(1);
    params.setKsigmaValue(1);
}

QImage SmoothItem::item_process_img(QImage img)
{
    if (params.getKindValue() == 0) {
        img = Tools::GaussianFilter(img,params.getKsizeValue(),params.getKsigmaValue());
    } else if (params.getKindValue() == 1) {
        img = Tools::AverageFilter(img,params.getKsizeValue());
    } else {
        img = Tools::MeidanFilter(img,params.getKsizeValue());
    }
    return img;
}

SharpenItem::SharpenItem(const QString &text, QListWidget *parent)
    :MyItem(text, parent)
{
    this->setIcon(QIcon(":/images/sharpen.png"));
    params.setKindValue(0);
}

QImage SharpenItem::item_process_img(QImage img)
{
    if(params.getKindValue() == 0) {
        img = Tools::SobelFilter(img, true);
    } else if (params.getKindValue() == 1) {
        img = Tools::SobelFilter(img, false);
    } else {
        img = Tools::LaplaceFilter(img);
    }
    return img;
}

GrayscaleItem::GrayscaleItem(const QString &text, QListWidget *parent)
    :MyItem(text,parent)
{
    this->setIcon(QIcon(":/images/intensity.png"));
    params.setKindValue(0);
    params.setWlValue(113);
    params.setWwValue(100);
    params.setGammaValue(1);
}

QImage GrayscaleItem::item_process_img(QImage img)
{
    if(params.getKindValue() == 0) {
        img = Tools::WindowLevelTransformation(img, params.getWlValue(), params.getWwValue());
    } else {
        img = Tools::PowerLevelTransformation(img, params.getGammaValue());
    }
    return img;
}

GeometricItem::GeometricItem(const QString &text, QListWidget *parent)
    :MyItem(text,parent)
{
    this->setIcon(QIcon(":/images/trans.png"));
    params.setKindValue(0);
}

QImage GeometricItem::item_process_img(QImage img)
{
    if (params.getKindValue() == 0) {

    }
    else if (params.getKindValue() == 1) {
        img = Tools::FlipHorizontal(img);
    }
    else if (params.getKindValue() == 2) {
        img = Tools::FlipVertical(img);
    }
    else if (params.getKindValue() == 3) {
        img = Tools::ClockwiseRotation(img);
    }
    else {
        img = Tools::CounterclockwiseRotation(img);
    }
    return img;
}

MorphItem::MorphItem(const QString &text, QListWidget *parent)
    :MyItem(text,parent)
{
    this->setIcon(QIcon(":/images/morph.png"));
    params.setKindValue(0);
    params.setKshapeValue(0);
    params.setKsizeValue(1);
}

QImage MorphItem::item_process_img(QImage img)
{
    if (params.getKindValue() == 0) {
        img = Tools::Erode(img, params.getKshapeValue(), params.getKsizeValue());
    }
    else if (params.getKindValue() == 1) {
        img = Tools::Dilate(img, params.getKshapeValue(), params.getKsizeValue());
    }
    else if (params.getKindValue() == 2) {
        img = Tools::Opening(img, params.getKshapeValue(), params.getKsizeValue());
    }
    else if (params.getKindValue() == 3) {
        img = Tools::Closing(img, params.getKshapeValue(), params.getKsizeValue());
    }
    else {
        img = Tools::MorphEdge(img, params.getKshapeValue(), params.getKsizeValue());
    }
    return img;
}

SegItem::SegItem(const QString &text, QListWidget *parent)
    :MyItem(text,parent)
{
    this->setIcon(QIcon(":/images/seg.png"));
    params.setKindValue(0);
    params.setThres1Value(100);
    params.setThres2Value(200);
}

QImage SegItem::item_process_img(QImage img)
{
    if (params.getKindValue() == 0) {
        img = Tools::BinarySegment(img, params.getThres1Value(), params.getThres2Value());
    } else {
        img = Tools::OtsuThresholdSegment(img);
    }
    return img;
}
