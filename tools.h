#ifndef TOOLS_H
#define TOOLS_H
#include <QImage>
#include <vector>
#include <math.h>
using std::vector;

namespace Tools{
/**************************Grayscale transformation*********************/
QImage PowerLevelTransformation(const QImage &origin, double gamma);
QImage WindowLevelTransformation(const QImage &origin, double wl, double ww);

/**************************Filter***************************************/
QImage GaussianFilter(const QImage &origin, int radius, int sigma);
QImage AverageFilter(const QImage &origin, int radius);
QImage MeidanFilter(const QImage &origin, int radius);
QImage SobelFilter(const QImage &origin, bool dx_flag);
QImage LaplaceFilter(const QImage &origin);

/**************************Geometric transformation*********************/
QImage FlipVertical(const QImage &origin);
QImage FlipHorizontal(const QImage &origin);
QImage ClockwiseRotation(const QImage &origin);
QImage CounterclockwiseRotation(const QImage &origin);

/**************************Morphology***********************************/
QImage Erode(const QImage &origin, int kshape, int radius);
QImage Dilate(const QImage &origin, int kshape, int radius);
QImage Opening(const QImage &origin, int kshape, int radius);
QImage Closing(const QImage &origin, int kshape, int radius);
QImage MorphEdge(const QImage &origin, int kshape, int radius);

/**************************Segment**************************************/
QImage BinarySegment(const QImage &origin, int a, int b);
QImage OtsuThresholdSegment(const QImage &origin);

/**************************Utils**************************************/
float GaussFunc(float x, int sigma);
int ReflectIndex(int x, int length);
}

#endif // TOOLS_H
