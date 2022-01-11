#include "tools.h"
#include <QtMath>
#include <QSize>

QImage Tools::GaussianFilter(const QImage &origin, int radius, int sigma)
{
    if(origin.isNull())
        return QImage();

    //CreateConvolutionMatrix
    vector<float> mConvolutionMatrix;
    int x = 0;
    size_t matrixSize_t, halfMatrixSize_t;

    matrixSize_t = (size_t)(2*radius + 1);
    halfMatrixSize_t = matrixSize_t / 2;

    mConvolutionMatrix.resize(matrixSize_t);

    vector<float>::iterator begin = mConvolutionMatrix.begin();
    vector<float>::iterator end = mConvolutionMatrix.end();

    x = -(int)halfMatrixSize_t;
    std::for_each(begin, end,
                [&] (float& val) mutable
                {
                    val = GaussFunc(x,sigma);
                    x++;
                });

    // normalize the values in the convolution matrix
    float sum = std::accumulate(begin, end, 0.0f);

    std::for_each(begin, end, [&] (float& val) { val /= sum; });

    QImage image(origin.size(), origin.format());

    int matrixSize = mConvolutionMatrix.size();
    int halfMatrixSize = matrixSize / 2;

    float sumRed = 0.0f;
    float sumBlue = 0.0f;
    float sumGreen = 0.0f;
    float matrixValue = 0.0f;
    int x1 = 0, y1 = 0;

    for (int x = 0; x < origin.width(); ++x)
    {
        for (int y = 0; y < origin.height(); ++y)
        {
            for (int kx = -halfMatrixSize; kx <= halfMatrixSize; ++kx)
            {
                x1 = ReflectIndex(x - kx, origin.width());

                QColor color(origin.pixel(x1, y));

                matrixValue = mConvolutionMatrix[kx + halfMatrixSize];

                sumRed += color.red() * matrixValue;
                sumBlue += color.blue() * matrixValue;
                sumGreen += color.green() * matrixValue;
            }

            QRgb finalColor = qRgb(sumRed, sumGreen, sumBlue);
            image.setPixel(x, y, finalColor);

            sumRed = sumGreen = sumBlue = 0.0f;
        }
    }

    for (int x = 0; x < origin.width(); ++x)
    {
        for (int y = 0; y < origin.height(); ++y)
        {
            for (int ky = -halfMatrixSize; ky <= halfMatrixSize; ++ky)
            {
                y1 = ReflectIndex(y - ky, origin.height());

                QColor color(image.pixel(x, y1));
                matrixValue = mConvolutionMatrix[ky + halfMatrixSize];

                sumRed += color.red() * matrixValue;
                sumBlue += color.blue() * matrixValue;
                sumGreen += color.green() * matrixValue;
            }

            QRgb finalColor = qRgb(sumRed, sumGreen, sumBlue);
            image.setPixel(x, y, finalColor);

            sumRed = sumGreen = sumBlue = 0.0f;
        }
    }

    return image;
}

QImage Tools::AverageFilter(const QImage &origin, int radius)
{
    if(origin.isNull())
        return QImage();

    //CreateConvolutionMatrix
    vector<float> mConvolutionMatrix;
    int x = 0;
    size_t matrixSize_t, halfMatrixSize_t;

    matrixSize_t = (size_t)(2*radius + 1);
    halfMatrixSize_t = matrixSize_t / 2;

    mConvolutionMatrix.resize(matrixSize_t);

    vector<float>::iterator begin = mConvolutionMatrix.begin();
    vector<float>::iterator end = mConvolutionMatrix.end();

    x = -(int)halfMatrixSize_t;
    std::for_each(begin, end,
                [&] (float& val) mutable
                {
                    val = 1;
                    x++;
                });

    // normalize the values in the convolution matrix
    float sum = std::accumulate(begin, end, 0.0f);

    std::for_each(begin, end, [&] (float& val) { val /= sum; });

    QImage image(origin.size(), origin.format());

    int matrixSize = mConvolutionMatrix.size();
    int halfMatrixSize = matrixSize / 2;

    float sumRed = 0.0f;
    float sumBlue = 0.0f;
    float sumGreen = 0.0f;
    float matrixValue = 0.0f;
    int x1 = 0, y1 = 0;

    for (int x = 0; x < origin.width(); ++x)
    {
        for (int y = 0; y < origin.height(); ++y)
        {
            for (int kx = -halfMatrixSize; kx <= halfMatrixSize; ++kx)
            {
                x1 = ReflectIndex(x - kx, origin.width());

                QColor color(origin.pixel(x1, y));

                matrixValue = mConvolutionMatrix[kx + halfMatrixSize];

                sumRed += color.red() * matrixValue;
                sumBlue += color.blue() * matrixValue;
                sumGreen += color.green() * matrixValue;
            }

            QRgb finalColor = qRgb(sumRed, sumGreen, sumBlue);
            image.setPixel(x, y, finalColor);

            sumRed = sumGreen = sumBlue = 0.0f;
        }
    }

    for (int x = 0; x < origin.width(); ++x)
    {
        for (int y = 0; y < origin.height(); ++y)
        {
            for (int ky = -halfMatrixSize; ky <= halfMatrixSize; ++ky)
            {
                y1 = ReflectIndex(y - ky, origin.height());

                QColor color(image.pixel(x, y1));
                matrixValue = mConvolutionMatrix[ky + halfMatrixSize];

                sumRed += color.red() * matrixValue;
                sumBlue += color.blue() * matrixValue;
                sumGreen += color.green() * matrixValue;
            }

            QRgb finalColor = qRgb(sumRed, sumGreen, sumBlue);
            image.setPixel(x, y, finalColor);

            sumRed = sumGreen = sumBlue = 0.0f;
        }
    }

    return image;
}

QImage Tools::MeidanFilter(const QImage &origin, int radius)
{
    if(origin.isNull())
        return QImage();
    int n = (2*radius+1)*(2*radius+1);
    vector<int> filter_number(n);
    int k,j,c;

    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int i = 0;
            for (int x1 = -radius; x1 <= radius; ++x1) {
                for (int y1 = -radius; y1 <= radius; ++y1) {
                    int x2 = ReflectIndex(x + x1,origin.width());
                    int y2 = ReflectIndex(y + y1,origin.height());
                    QRgb color = origin.pixel(x2,y2);
                    filter_number[i] = qGray(color);
                    i++;
                }
            }
            for (int i1 = 0;i1<n;i1++)
                {
                    k = i1;
                    for(j = k +1;j<n;j++)
                    {
                    if (filter_number[i1]>filter_number[j])
                    {
                        c = filter_number[j];
                        filter_number[j] = filter_number[i1];
                        filter_number[i1] = c;
                    }
                    }
                }
            int fColor_int = filter_number[n/2];
            QRgb fColor = qRgb(fColor_int,fColor_int,fColor_int);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::SobelFilter(const QImage &origin, bool dx_flag)
{
    if(origin.isNull())
        return QImage();
    int kernel[9] = {
        -1,-2,-1,
        0,0,0,
        1,2,1
    };
    if (!dx_flag) {
        kernel[0] = -1; kernel[1] = 0; kernel[2] = 1;
        kernel[3] = -2; kernel[4] = 0; kernel[5] = 2;
        kernel[6] = -1; kernel[7] = 0; kernel[8] = 1;
    }
    int min_value = 255;
    int max_value = 0;
    int i,color_sum;
    vector<int> image_array(origin.width()*origin.height());
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            i = 0;
            color_sum = 0;
            for (int y1 = -1; y1 <= 1; ++y1) {
                for (int x1 = -1; x1 <= 1; ++x1) {
                    int x2 = ReflectIndex(x + x1,origin.width());
                    int y2 = ReflectIndex(y + y1,origin.height());
                    QRgb color = origin.pixel(x2,y2);
                    color_sum += qGray(color) * kernel[i];
                    i++;
                }
            }
            image_array[x*origin.height()+y] = color_sum;
            if (color_sum < min_value) {min_value = color_sum;}
            if (color_sum > max_value) {max_value = color_sum;}
        }
    }
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y <origin.height(); ++y) {
            int fColor_int = (image_array[x*origin.height()+y] - min_value)*255/(max_value - min_value);
            QRgb fColor = qRgb(fColor_int,fColor_int,fColor_int);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::LaplaceFilter(const QImage &origin)
{
    if(origin.isNull())
        return QImage();
    int kernel[9] = {
        0,1,0,
        1,-4,1,
        0,1,0
    };
    int min_value = 255;
    int max_value = 0;
    int i,color_sum;
    vector<int> image_array(origin.width()*origin.height());
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            i = 0;
            color_sum = 0;
            for (int y1 = -1; y1 <= 1; ++y1) {
                for (int x1 = -1; x1 <= 1; ++x1) {
                    int x2 = ReflectIndex(x + x1,origin.width());
                    int y2 = ReflectIndex(y + y1,origin.height());
                    QRgb color = origin.pixel(x2,y2);
                    color_sum += qGray(color) * kernel[i];
                    i++;
                }
            }
            image_array[x*origin.height()+y] = color_sum;
            if (color_sum < min_value) {min_value = color_sum;}
            if (color_sum > max_value) {max_value = color_sum;}
        }
    }
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y <origin.height(); ++y) {
            int fColor_int = (image_array[x*origin.height()+y] - min_value)*255/(max_value - min_value);
            QRgb fColor = qRgb(fColor_int,fColor_int,fColor_int);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::PowerLevelTransformation(const QImage &origin, double gamma)
{
    if(origin.isNull())
        return QImage();
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x, y);
            int color_int = qGray(color);
            color_int = qPow(double(color_int)/255, gamma) * 255;
            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    return image;
}

QImage Tools::WindowLevelTransformation(const QImage &origin, double wl, double ww)
{
    if(origin.isNull())
        return QImage();
    int min_value = 255;
    int max_value = 0;
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x, y);
            int color_int = qGray(color);
            if ((color_int < wl - ww/2)||(color_int > wl + ww/2)) {
                color_int = 0;
            }
            if (color_int < min_value) {min_value = color_int;}
            if (color_int > max_value) {max_value = color_int;}
            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y <origin.height(); ++y) {
            int color_img_int = qGray(image.pixel(x,y));
            int fColor_int = (color_img_int - min_value)*255/(max_value - min_value);
            QRgb fColor = qRgb(fColor_int,fColor_int,fColor_int);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::Erode(const QImage &origin, int kshape, int radius)
{
    if(origin.isNull())
        return QImage();
    //int n = (2*radius+1)*(2*radius+1);
    //int k,j;

    QImage image(origin.size(), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int min_i=255;
            int c = 0;
            if(kshape==0){
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    for (int y1 = -radius; y1 <= radius; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c<min_i){
                            min_i=c;
                        }
                    }
                }
            }
            else{
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    int d_y = ceil(sqrt(radius*radius-x1*x1));
                    for (int y1 = -d_y; y1 <= d_y; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c<min_i){
                            min_i=c;
                        }
                    }
                }
            }
            QRgb fColor = qRgb(min_i,min_i,min_i);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::Dilate(const QImage &origin, int kshape, int radius)
{
    if(origin.isNull())
        return QImage();

    QImage image(origin.size(), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int max_i=0;
            int c = 0;
            if(kshape==0){
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    for (int y1 = -radius; y1 <= radius; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c>max_i){
                            max_i=c;
                        }
                    }
                }
            }
            else{
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    int d_y = ceil(sqrt(radius*radius-x1*x1));
                    for (int y1 = -d_y; y1 <= d_y; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c>max_i){
                            max_i=c;
                        }
                    }
                }
            }
            QRgb fColor = qRgb(max_i,max_i,max_i);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::Opening(const QImage &origin, int kshape, int radius){
    QImage image(origin.size(), origin.format());
    image=Tools::Erode(origin,kshape,radius);
    image=Tools::Dilate(image,kshape,radius);
    return image;
}

QImage Tools::Closing(const QImage &origin, int kshape, int radius){
    QImage image(origin.size(), origin.format());
    image=Tools::Dilate(origin,kshape,radius);
    image=Tools::Erode(image,kshape,radius);
    return image;
}

QImage Tools::MorphEdge(const QImage &origin, int kshape, int radius){
    if(origin.isNull())
        return QImage();

    QImage image(origin.size(), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int min_i=255;
            int c = 0;
            if(kshape==0){
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    for (int y1 = -radius; y1 <= radius; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c<min_i){
                            min_i=c;
                        }
                    }
                }
            }
            else{
                for (int x1 = -radius; x1 <= radius; ++x1) {
                    int d_y = ceil(sqrt(radius*radius-x1*x1));
                    for (int y1 = -d_y; y1 <= d_y; ++y1) {
                        int x2 = ReflectIndex(x + x1,origin.width());
                        int y2 = ReflectIndex(y + y1,origin.height());
                        QRgb color = origin.pixel(x2,y2);
                        c = qGray(color);
                        if (c<min_i){
                            min_i=c;
                        }
                    }
                }
            }
            QRgb fColor = qRgb(qGray(origin.pixel(x,y))-min_i,qGray(origin.pixel(x,y))-min_i,qGray(origin.pixel(x,y))-min_i);
            image.setPixel(x,y,fColor);
        }
    }
    return image;
}

QImage Tools::BinarySegment(const QImage &origin, int a, int b)
{
    if(origin.isNull())
        return QImage();
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x, y);
            int color_int = qGray(color);
            if ((color_int < a)||(color_int > b)) {
                color_int = 0;
            } else {
                color_int = 255;
            }
            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    return image;
}

QImage Tools::OtsuThresholdSegment(const QImage &origin)
{
    if(origin.isNull())
        return QImage();

    int T=0; //Otsu算法阈值
    double varValue=0; //类间方差中间值保存
    double w0=0; //前景像素点数所占比例
    double w1=0; //背景像素点数所占比例
    double u0=0; //前景平均灰度
    double u1=0; //背景平均灰度
    double Histogram[256]={0}; //灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数
    double totalNum=origin.height()*origin.width(); //像素总数
    //计算灰度直方图分布，Histogram数组下标是灰度值，保存内容是灰度值对应像素点数
    for(int i = 0;i<origin.height();i++)
    {
        for(int j = 0;j<origin.width();j++)
        {
            int bwValue = qGray(origin.pixel(j, i));
            Histogram[bwValue]++;
        }
    }
    for(int i=0;i<255;i++)
    {
        //每次遍历之前初始化各变量
        w1=0;		u1=0;		w0=0;		u0=0;
        //***********背景各分量值计算**************************
        for(int j=0;j<=i;j++) //背景部分各值计算
        {
            w1+=Histogram[j];  //背景部分像素点总数
            u1+=j*Histogram[j]; //背景部分像素总灰度和
        }
        if(w1==0) //背景部分像素点数为0时退出
        {
            continue;
        }
        u1=u1/w1; //背景像素平均灰度
        w1=w1/totalNum; // 背景部分像素点数所占比例
        //***********背景各分量值计算**************************

        //***********前景各分量值计算**************************
        for(int k=i+1;k<255;k++)
        {
            w0+=Histogram[k];  //前景部分像素点总数
            u0+=k*Histogram[k]; //前景部分像素总灰度和
        }
        if(w0==0) //前景部分像素点数为0时退出
        {
            break;
        }
        u0=u0/w0; //前景像素平均灰度
        w0=w0/totalNum; // 前景部分像素点数所占比例
        //***********前景各分量值计算**************************

        //***********类间方差计算******************************
        double varValueI=w0*w1*(u1-u0)*(u1-u0); //当前类间方差计算
        if(varValue<varValueI)
        {
            varValue=varValueI;
            T=i;
        }
    }
    QImage image(origin.size(), origin.format());
    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x, y);
            int color_int = qGray(color);
            if (color_int < T) {
                color_int = 0;
            } else {
                color_int = 255;
            }
            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    return image;
}

QImage Tools::FlipVertical(const QImage &origin)
{
    if(origin.isNull())
        return QImage();
    QImage image(origin.size(), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int y2 = ReflectIndex(origin.height()-y,origin.height());
            QRgb color = origin.pixel(x,y2);
            int color_int = qGray(color);

            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    return image;
}

QImage Tools::FlipHorizontal(const QImage &origin)
{
    if(origin.isNull())
        return QImage();
    QImage image(origin.size(), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            int x2 = ReflectIndex(origin.width()-x,origin.width());
            QRgb color = origin.pixel(x2,y);
            int color_int = qGray(color);

            color = qRgb(color_int, color_int, color_int);
            image.setPixel(x,y,color);
        }
    }
    return image;
}

QImage Tools::ClockwiseRotation(const QImage &origin)
{
    if(origin.isNull())
        return QImage();
    QImage image(QSize(origin.height(),origin.width()), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x,y);
            int color_int = qGray(color);

            color = qRgb(color_int, color_int, color_int);
            image.setPixel(origin.height()-y-1,x,color);
        }
    }
    return image;
}

QImage Tools::CounterclockwiseRotation(const QImage &origin)
{
    if(origin.isNull())
        return QImage();
    QImage image(QSize(origin.height(),origin.width()), origin.format());

    for (int x = 0; x < origin.width(); ++x) {
        for (int y = 0; y < origin.height(); ++y) {
            QRgb color = origin.pixel(x,y);
            int color_int = qGray(color);

            color = qRgb(color_int, color_int, color_int);
            image.setPixel(y,origin.width()-x-1,color);
        }
    }
    return image;
}


float Tools::GaussFunc(float x, int sigma)
{
    float mSigma = sigma;
    // Gaussian function in one dimension
    return (1 / sqrtf(2*M_PI * mSigma * mSigma)) *
            exp(-(x*x)/(2*mSigma*mSigma));
}

int Tools::ReflectIndex(int x, int length)
{
    if (x < 0)
        return -x - 1;
    else if(x >= length)
        return 2*length - x - 1;

    return x;
}
