#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "paramsitem.h"
#include <QImage>
#include <QListWidget>
#include <QContextMenuEvent>

class MyItem;

class UsedListWidget: public QListWidget
{
    Q_OBJECT
private:
    QWidget *mainwindow;
public:
    UsedListWidget(QWidget *parent);
    void contextMenuEvent(QContextMenuEvent *event);
private slots:
    void show_attr();
    void delete_item(MyItem *item);
};

class MyItem: public QListWidgetItem
{
private:
    ParamsItem params;
public:
    MyItem(const QString &text, QListWidget *parent = nullptr);
    virtual QImage item_process_img(QImage) = 0;
    virtual ParamsItem get_params() = 0;
    virtual int get_index() = 0;
    virtual void update_params(ParamsItem p) = 0;
};

class SmoothItem: public MyItem
{
private:
    ParamsItem params;
public:
    SmoothItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 0;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};

class SharpenItem: public MyItem
{
private:
    ParamsItem params;
public:
    SharpenItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 1;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};

class GrayscaleItem: public MyItem
{
private:
    ParamsItem params;
public:
    GrayscaleItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 2;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};

class GeometricItem: public MyItem
{
private:
    ParamsItem params;
public:
    GeometricItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 3;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};

class MorphItem: public MyItem
{
private:
    ParamsItem params;
public:
    MorphItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 4;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};

class SegItem: public MyItem
{
private:
    ParamsItem params;
public:
    SegItem(const QString &text, QListWidget *parent = nullptr);
    int get_index() {return 5;}
    ParamsItem get_params() {return params;}
    void update_params(ParamsItem p) {params = p;}
    QImage item_process_img(QImage);
};
#endif // LISTWIDGET_H
