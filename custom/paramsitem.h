#ifndef PARAMSITEM_H
#define PARAMSITEM_H


class ParamsItem
{
private:
    int _kind;
    int _ksize;
    int _ksigma;
    int _ww;
    int _wl;
    int _kshape;
    int _thres1;
    int _thres2;
    double _gamma;
public:
    ParamsItem();
    void setKindValue(int kind) {_kind = kind;}
    void setKsizeValue(int ksize) {_ksize = ksize;}
    void setKsigmaValue(int ksigma) {_ksigma = ksigma;}
    void setWwValue(int ww) {_ww = ww;}
    void setWlValue(int wl) {_wl = wl;}
    void setKshapeValue(int kshape) {_kshape = kshape;}
    void setThres1Value(int thres1) {_thres1 = thres1;}
    void setThres2Value(int thres2) {_thres2 = thres2;}
    void setGammaValue(double gamma) {_gamma = gamma;}
    int getKindValue() {return _kind;}
    int getKsizeValue() {return _ksize;}
    int getKsigmaValue() {return _ksigma;}
    int getWwValue() {return _ww;}
    int getWlValue() {return _wl;}
    int getKshapeValue() {return _kshape;}
    int getThres1Value() {return _thres1;}
    int getThres2Value() {return _thres2;}
    double getGammaValue() {return _gamma;}
};

#endif // PARAMSITEM_H
