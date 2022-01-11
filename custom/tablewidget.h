#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QSpinBox>
#include "paramsitem.h"

class TableWidget: public QTableWidget
{
    Q_OBJECT
public:
    QWidget *mainwindow;
    TableWidget(QWidget *parent);
    virtual void update_params(ParamsItem p) = 0;
    virtual ParamsItem get_params() = 0;
public slots:
    void update_item();
};

class SmoothTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
    QSpinBox *ksize_spinBox;
    QSpinBox *ksigma_spinBox;
public:
    SmoothTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};

class SharpenTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
public:
    SharpenTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};

class GrayscaleTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
    QSpinBox *wl_spinBox;
    QSpinBox *ww_spinBox;
    QDoubleSpinBox *gamma_dspinBox;
public:
    GrayscaleTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};

class GeometricTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
public:
    GeometricTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};

class MorphTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
    QComboBox *kshape_comBox;
    QSpinBox *ksize_spinBox;
public:
    MorphTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};

class SegTableWidget: public TableWidget
{
    Q_OBJECT
private:
    QComboBox *kind_comBox;
    QSpinBox *thres1_spinBox;
    QSpinBox *thres2_spinBox;
public:
    SegTableWidget(QWidget *parent);
    void update_params(ParamsItem p);
    ParamsItem get_params();
};
#endif // TABLEWIDGET_H
