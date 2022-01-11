#include "paramsitem.h"

ParamsItem::ParamsItem()
{
    //实际上没用，Item初始化时会对用到的params赋值
    _kind = 0;
    _ksize = 1;
    _ksigma = 1;
    _wl = 113;
    _ww = 100;
    _kshape = 0;
    _thres1 = 100;
    _thres2 = 200;
    _gamma = 1;
}
