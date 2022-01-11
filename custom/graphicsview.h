#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QWheelEvent>
#include <QLabel>
class GraphicsView: public QGraphicsView
{
private:
    int _zoom;
    bool _empty;

public:
    QGraphicsPixmapItem *_photo;
    GraphicsView(QGraphicsScene *scene, QWidget *parent);
    bool has_photo() {return not _empty;}
    void show_photo(QPixmap pixmap);
    void show_image(QImage img);
    void fitInView();
    void wheelEvent(QWheelEvent *event);
};

class HistLabel: public QLabel
{
private:
    QWidget *mainwindow;
public:
    HistLabel(QWidget *window):QLabel(nullptr) {mainwindow = window;}
    void paintEvent(QPaintEvent *event);
};

#endif // GRAPHICSVIEW_H
