#include "graphicsview.h"
#include "mainwindow.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    _zoom = 0;
    _empty = true;
    this->setScene(scene);
    this->setAlignment(Qt::AlignCenter);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setBackgroundBrush(QColor::fromRgb(255,255,255));//设置背景颜色
    this->setMinimumSize(640,480);
}

void GraphicsView::show_photo(QPixmap pixmap)
{
    _photo = this->scene()->addPixmap(pixmap);
    fitInView();
    _empty = false;
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (has_photo()) {
        float factor;
        if (event->angleDelta().y() > 0) {
            factor = 1.25;
            _zoom += 1;
        } else {
            factor = 0.8;
            _zoom -= 1;
        }
        if (_zoom > 0) {
            scale(factor,factor);
        } else if(_zoom == 0){
            fitInView();
        } else {
            _zoom = 0;
        }
    }
}

void GraphicsView::fitInView() {
    QRectF rect = QRectF(_photo->pixmap().rect());
    if(not rect.isNull()) {
        setSceneRect(rect);
        if(has_photo()) {
            QRectF unity = transform().mapRect(QRectF(0,0,1,1));
            scale(1/unity.width(),1/unity.height());
            QRect viewrect = viewport()->rect();
            QRectF scenerect = transform().mapRect(rect);
            float factor = qMin(viewrect.width()/scenerect.width()
                                ,viewrect.height()/scenerect.height());
            scale(factor,factor);
        }
        _zoom = 0;
    }
}

void GraphicsView::show_image(QImage img) {

    QPixmap pixmap = QPixmap::fromImage(img);
    this->scene()->clear();
    _photo = this->scene()->addPixmap(pixmap);
    fitInView();
    _empty = false;
}

void HistLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //calculate histogram
    MainWindow *window;
    window = (MainWindow *)mainwindow;
    QImage img;
    img = window->get_cur_img();
    int data[256]{0};
    for(int i = 0;i<img.height();i++)
    {
        for(int j = 0;j<img.width();j++)
        {
            int bwValue = qGray(img.pixel(j, i));
            data[bwValue]++;
        }
    }
    int max_value = 0;
    for(int i = 0; i < 256; i++){
        if(data[i] > max_value){
            max_value = data[i];
        }
    }

    //plot the histogram
    int label_w = this->width();
    int label_h = this->height();

    QPainter painter(this);
    painter.setPen(QColor(0,0,0));

    painter.drawLine(0.1*label_w,0.9*label_h,0.92*label_w,0.9*label_h);     //x轴
    painter.drawLine(0.1*label_w,0.9*label_h,0.1*label_w,0.1*label_h);      //y轴
    painter.drawLine(0.1*label_w,0.1*label_h,0.09*label_w,0.11*label_h);      //上箭头
    painter.drawLine(0.1*label_w,0.1*label_h,0.11*label_w,0.11*label_h);      //上箭头
    painter.drawLine(0.91*label_w,0.89*label_h,0.92*label_w,0.9*label_h);    //右箭头
    painter.drawLine(0.91*label_w,0.91*label_h,0.92*label_w,0.9*label_h);    //右箭头

    painter.setPen(Qt::darkGray);
    for(int i = 0;i<256;i++)
    {
        painter.drawLine(0.1*label_w+(1+i)*0.0028*label_w, 0.9*label_h, 0.1*label_w+(1+i)*0.0028*label_w,
            0.9*label_h-(float)(0.7/max_value)*(float)data[i]*label_h);
    }
//画刻度效果不好
//    painter.setPen(QColor(0,0,0));
//    for(int i = 25; i < 250; i+=25){//x刻度
//        painter.drawLine(0.1*label_w + i*0.07*label_w, 0.9*label_h, 0.1*label_w + i*0.07*label_w, 0.92*label_h);
//        painter.drawPoint(0.1*label_w + i*0.07*label_w, 0.9*label_h);
//    }
//    painter.drawText(0.1*label_w, 0.95*label_h, tr("0"));
//    painter.drawText(0.8*label_w, 0.95*label_h, tr("250"));
}
