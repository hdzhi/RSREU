#include "imageprocessor.h"
#include <QtMath>
#include <vector>
#include <algorithm>
#include <cmath>

//using namespace ImageProcessor;

inline int clamp_i(int v, int a=0, int b=255){ return v < a ? a : (v > b ? b : v); }

template <typename T>
static T clampValue(T v, T lo, T hi)
{
    return (v < lo) ? lo : (v > hi) ? hi : v;
}


// helper to ensure ARGB32
static QImage toARGB32(const QImage &in){
    if(in.format() == QImage::Format_ARGB32) return in;
    return in.convertToFormat(QImage::Format_ARGB32);
}

// bilinear sample (with clamp)
static QRgb sampleBilinear(const QImage &img, double fx, double fy, QRgb bg = qRgba(255,255,255,255)){
    int w = img.width(), h = img.height();
    if(fx < 0 || fy < 0 || fx >= w-1 || fy >= h-1){
        int nx = std::max(0, std::min(w-1, int(std::round(fx))));
        int ny = std::max(0, std::min(h-1, int(std::round(fy))));
        if(nx>=0 && ny>=0 && nx<w && ny<h) return img.pixel(nx,ny);
        return bg;
    }
    int x0 = int(std::floor(fx));
    int y0 = int(std::floor(fy));
    double dx = fx - x0;
    double dy = fy - y0;
    QRgb p00 = img.pixel(x0,y0);
    QRgb p10 = img.pixel(x0+1,y0);
    QRgb p01 = img.pixel(x0,y0+1);
    QRgb p11 = img.pixel(x0+1,y0+1);
    auto lerp = [](double t, int a, int b)->double{ return a + t*(b-a); };
    int a = int(lerp(dy, lerp(dx, qAlpha(p00), qAlpha(p10)), lerp(dx, qAlpha(p01), qAlpha(p11))));
    int r = int(lerp(dy, lerp(dx, qRed(p00), qRed(p10)), lerp(dx, qRed(p01), qRed(p11))));
    int g = int(lerp(dy, lerp(dx, qGreen(p00), qGreen(p10)), lerp(dx, qGreen(p01), qGreen(p11))));
    int b = int(lerp(dy, lerp(dx, qBlue(p00), qBlue(p10)), lerp(dx, qBlue(p01), qBlue(p11))));
    return qRgba(clamp_i(r), clamp_i(g), clamp_i(b), clamp_i(a));
}

// Exposure
QImage ImageProcessor::changeExposure(const QImage &src, double factor){
    QImage img = toARGB32(src);
    int w=img.width(), h=img.height();
    QImage out(w,h,QImage::Format_ARGB32);
    for(int y=0;y<h;++y){
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        QRgb *oline = reinterpret_cast<QRgb*>(out.scanLine(y));
        for(int x=0;x<w;++x){
            QRgb p = sline[x];
            int a = qAlpha(p);
            int r = clamp_i(int(qRed(p) * factor));
            int g = clamp_i(int(qGreen(p) * factor));
            int b = clamp_i(int(qBlue(p) * factor));
            oline[x] = qRgba(r,g,b,a);
        }
    }
    return out;
}

QImage ImageProcessor::adjustBrightness(const QImage &src, int brightness)
{
    QImage img = toARGB32(src);
    int w = img.width(), h = img.height();
    QImage out(w, h, QImage::Format_ARGB32);

    for (int y = 0; y < h; ++y) {
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        QRgb *oline = reinterpret_cast<QRgb*>(out.scanLine(y));

        for (int x = 0; x < w; ++x) {
            QRgb p = sline[x];
            int r = clamp_i(qRed(p) + brightness);
            int g = clamp_i(qGreen(p) + brightness);
            int b = clamp_i(qBlue(p) + brightness);
            int a = qAlpha(p);
            oline[x] = qRgba(r, g, b, a);
        }
    }

    return out;
}

QImage ImageProcessor::adjustContrast(const QImage &src, int contrast)
{
    QImage img = toARGB32(src);
    int w = img.width(), h = img.height();
    QImage out(w, h, QImage::Format_ARGB32);

    // коэффициент контраста
    double c = contrast;
    double f = (259 * (c + 255)) / (255 * (259 - c));

    for (int y = 0; y < h; ++y) {
        const QRgb *srcLine = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        QRgb *dstLine = reinterpret_cast<QRgb*>(out.scanLine(y));

        for (int x = 0; x < w; ++x) {
            QRgb p = srcLine[x];

            int r = clamp_i(int(f * (qRed(p)   - 128) + 128));
            int g = clamp_i(int(f * (qGreen(p) - 128) + 128));
            int b = clamp_i(int(f * (qBlue(p)  - 128) + 128));

            dstLine[x] = qRgba(r, g, b, qAlpha(p));
        }
    }

    return out;
}


// Gray world WB
QImage ImageProcessor::autoWhiteBalanceGrayWorld(const QImage &src){
    QImage img = toARGB32(src);
    int w=img.width(), h=img.height();
    quint64 sumR=0,sumG=0,sumB=0;
    quint64 cnt=0;
    for(int y=0;y<h;++y){
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        for(int x=0;x<w;++x){
            QRgb p = sline[x];
            sumR += qRed(p);
            sumG += qGreen(p);
            sumB += qBlue(p);
            ++cnt;
        }
    }
    if(cnt==0) return img;
    double avgR = double(sumR)/cnt;
    double avgG = double(sumG)/cnt;
    double avgB = double(sumB)/cnt;
    double avgAll = (avgR + avgG + avgB)/3.0;
    double kR = avgAll/avgR;
    double kG = avgAll/avgG;
    double kB = avgAll/avgB;
    QImage out(w,h,QImage::Format_ARGB32);
    for(int y=0;y<h;++y){
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        QRgb *oline = reinterpret_cast<QRgb*>(out.scanLine(y));
        for(int x=0;x<w;++x){
            QRgb p = sline[x];
            int a=qAlpha(p);
            int r=clamp_i(int(qRed(p)*kR));
            int g=clamp_i(int(qGreen(p)*kG));
            int b=clamp_i(int(qBlue(p)*kB));
            oline[x]=qRgba(r,g,b,a);
        }
    }
    return out;
}

// Gaussian (separable)
static std::vector<double> gaussianKernel1D(double sigma){
    int radius = int(std::ceil(3.0*sigma));
    int size = radius*2 + 1;
    std::vector<double> k(size);
    double sum=0;
    for(int i=-radius;i<=radius;++i){
        double v = std::exp(-(i*i)/(2*sigma*sigma));
        k[i+radius]=v;
        sum += v;
    }
    for(double &v: k) v /= sum;
    return k;
}

QImage ImageProcessor::gaussianBlur(const QImage &src, double sigma){
    if(sigma <= 0.0001) return src;
    QImage img = toARGB32(src);
    int w=img.width(), h=img.height();
    auto k = gaussianKernel1D(sigma);
    int radius = (k.size()-1)/2;
    QImage tmp(w,h,QImage::Format_ARGB32);
    // horizontal
    for(int y=0;y<h;++y){
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        QRgb *tline = reinterpret_cast<QRgb*>(tmp.scanLine(y));
        for(int x=0;x<w;++x){
            double ar=0, ag=0, ab=0, aa=0;
            for(int i=-radius;i<=radius;++i){
                int sx = clampValue(x+i, 0, w-1);
                QRgb p = sline[sx];
                double kval = k[i+radius];
                ar += qRed(p)*kval;
                ag += qGreen(p)*kval;
                ab += qBlue(p)*kval;
                aa += qAlpha(p)*kval;
            }
            tline[x] = qRgba(clamp_i(int(ar+0.5)), clamp_i(int(ag+0.5)), clamp_i(int(ab+0.5)), clamp_i(int(aa+0.5)));
        }
    }
    QImage out(w,h,QImage::Format_ARGB32);
    // vertical
    for(int x=0;x<w;++x){
        for(int y=0;y<h;++y){
            double ar=0, ag=0, ab=0, aa=0;
            for(int j=-radius;j<=radius;++j){
                int sy = clampValue(y+j, 0, h-1);
                QRgb p = reinterpret_cast<const QRgb*>(tmp.constScanLine(sy))[x];
                double kval = k[j+radius];
                ar += qRed(p)*kval;
                ag += qGreen(p)*kval;
                ab += qBlue(p)*kval;
                aa += qAlpha(p)*kval;
            }
            reinterpret_cast<QRgb*>(out.scanLine(y))[x] = qRgba(clamp_i(int(ar+0.5)), clamp_i(int(ag+0.5)), clamp_i(int(ab+0.5)), clamp_i(int(aa+0.5)));
        }
    }
    return out;
}

QImage ImageProcessor::unsharpMask(const QImage &src, double sigma, double amount){
    QImage blurred = gaussianBlur(src, sigma);
    QImage img = toARGB32(src);
    int w=img.width(), h=img.height();
    QImage out(w,h,QImage::Format_ARGB32);
    for(int y=0;y<h;++y){
        const QRgb *sline = reinterpret_cast<const QRgb*>(img.constScanLine(y));
        const QRgb *bline = reinterpret_cast<const QRgb*>(blurred.constScanLine(y));
        QRgb *oline = reinterpret_cast<QRgb*>(out.scanLine(y));
        for(int x=0;x<w;++x){
            QRgb p = sline[x];
            QRgb b = bline[x];
            int r = clamp_i(int(qRed(p) + amount*(qRed(p) - qRed(b))));
            int g = clamp_i(int(qGreen(p) + amount*(qGreen(p) - qGreen(b))));
            int bb = clamp_i(int(qBlue(p) + amount*(qBlue(p) - qBlue(b))));
            int a = qAlpha(p);
            oline[x] = qRgba(r,g,bb,a);
        }
    }
    return out;
}

// Simple bilateral (slow)
QImage ImageProcessor::bilateralFilter(const QImage &src, int radius, double sigmaSpace, double sigmaColor){
    QImage img = toARGB32(src);
    int w=img.width(), h=img.height();
    QImage out(w,h,QImage::Format_ARGB32);
    if(radius <=0) return img;
    std::vector<double> sp(2*radius+1);
    for(int d=-radius; d<=radius; ++d) sp[d+radius] = std::exp(-(d*d)/(2*sigmaSpace*sigmaSpace));
    for(int y=0;y<h;++y){
        for(int x=0;x<w;++x){
            double sumR=0,sumG=0,sumB=0,sumW=0;
            QRgb p = img.pixel(x,y);
            int rc=qRed(p), gc=qGreen(p), bc=qBlue(p);
            for(int dy=-radius; dy<=radius; ++dy){
                int ny=y+dy;
                if(ny<0||ny>=h) continue;
                for(int dx=-radius; dx<=radius; ++dx){
                    int nx=x+dx;
                    if(nx<0||nx>=w) continue;
                    QRgb q = img.pixel(nx,ny);
                    double ds = sp[dy+radius]*sp[dx+radius];
                    double dc = (qRed(q)-rc)*(qRed(q)-rc) + (qGreen(q)-gc)*(qGreen(q)-gc) + (qBlue(q)-bc)*(qBlue(q)-bc);
                    double wc = std::exp(-dc/(2*sigmaColor*sigmaColor));
                    double wtot = ds*wc;
                    sumR += qRed(q)*wtot; sumG += qGreen(q)*wtot; sumB += qBlue(q)*wtot; sumW += wtot;
                }
            }
            if(sumW < 1e-6) out.setPixel(x,y,p);
            else{
                int r = clamp_i(int(sumR/sumW + 0.5));
                int g = clamp_i(int(sumG/sumW + 0.5));
                int b = clamp_i(int(sumB/sumW + 0.5));
                out.setPixel(x,y, qRgba(r,g,b,qAlpha(p)));
            }
        }
    }
    return out;
}

// Rotate bilinear
QImage ImageProcessor::rotateBilinear(const QImage &src, double angleDeg, const QColor &bg){
    QImage img = toARGB32(src);
    double angle = qDegreesToRadians(angleDeg);
    double c = std::cos(angle), s = std::sin(angle);
    int w=img.width(), h=img.height();
    double cx=(w-1)/2.0, cy=(h-1)/2.0;
    QPointF corners[4] = { {-cx,-cy}, {w-1-cx,-cy}, {-cx,h-1-cy}, {w-1-cx,h-1-cy} };
    double minx=1e9,maxx=-1e9,miny=1e9,maxy=-1e9;
    for(int i=0;i<4;++i){
        double rx = corners[i].x()*c - corners[i].y()*s;
        double ry = corners[i].x()*s + corners[i].y()*c;
        minx = std::min(minx, rx); maxx = std::max(maxx, rx);
        miny = std::min(miny, ry); maxy = std::max(maxy, ry);
    }
    int outW = int(std::floor(maxx - minx)) + 1;
    int outH = int(std::floor(maxy - miny)) + 1;
    QImage out(outW, outH, QImage::Format_ARGB32);
    out.fill(bg);
    double ox = (outW-1)/2.0, oy=(outH-1)/2.0;
    for(int y=0;y<outH;++y){
        QRgb *oline = reinterpret_cast<QRgb*>(out.scanLine(y));
        for(int x=0;x<outW;++x){
            double rx = x - ox;
            double ry = y - oy;
            double sx = rx*c + ry*s;
            double sy = -rx*s + ry*c;
            double srcx = sx + cx;
            double srcy = sy + cy;
            QRgb p = sampleBilinear(img, srcx, srcy, qRgba(bg.red(), bg.green(), bg.blue(), bg.alpha()));
            oline[x] = p;
        }
    }
    return out;
}

QImage ImageProcessor::crop(const QImage &src, const QRect &rect){
    QRect r = rect.intersected(src.rect());
    if(r.isEmpty()) return QImage();
    return src.copy(r);
}
QImage ImageProcessor::flipHorizontal(const QImage &src){ return src.mirrored(true,false); }
QImage ImageProcessor::flipVertical(const QImage &src){ return src.mirrored(false,true); }

// Utility: RGB → HSV
static void rgb2hsv(int R, int G, int B, double &H, double &S, double &V)
{
    double r = R / 255.0;
    double g = G / 255.0;
    double b = B / 255.0;

    double maxv = std::max(r, std::max(g, b));
    double minv = std::min(r, std::min(g, b));
    double delta = maxv - minv;

    V = maxv;

    if (delta < 1e-6) {
        H = 0;
        S = 0;
        return;
    }

    S = delta / maxv;

    if (maxv == r)
        H = 60 * fmod(((g - b) / delta), 6.0);
    else if (maxv == g)
        H = 60 * (((b - r) / delta) + 2.0);
    else
        H = 60 * (((r - g) / delta) + 4.0);

    if (H < 0) H += 360;
}

// Utility: HSV → RGB
static void hsv2rgb(double H, double S, double V, int &R, int &G, int &B)
{
    double C = V * S;
    double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    double m = V - C;

    double r, g, b;

    if (H < 60)      { r=C; g=X; b=0; }
    else if (H <120){ r=X; g=C; b=0; }
    else if (H <180){ r=0; g=C; b=X; }
    else if (H <240){ r=0; g=X; b=C; }
    else if (H <300){ r=X; g=0; b=C; }
    else            { r=C; g=0; b=X; }

    R = int((r+m)*255);
    G = int((g+m)*255);
    B = int((b+m)*255);
}

QImage ImageProcessor::adjustSkinTone_HSV(const QImage &src, double hueShift, double satFactor)
{
    QImage img = toARGB32(src);
    int w = img.width(), h = img.height();
    QImage out = img.copy();

    for (int y = 0; y < h; ++y) {
        QRgb *dst = reinterpret_cast<QRgb*>(out.scanLine(y));
        const QRgb *srcLine = reinterpret_cast<const QRgb*>(img.constScanLine(y));

        for (int x = 0; x < w; ++x) {
            QRgb p = srcLine[x];

            int R = qRed(p);
            int G = qGreen(p);
            int B = qBlue(p);

            // STEP 1: YCbCr skin detection (from your doc)
            double Y  = 0.299*R + 0.587*G + 0.114*B;
            double Cr = (R - Y)*0.713 + 128;
            double Cb = (B - Y)*0.564 + 128;

            bool isSkin =
                (Cr >= 135 && Cr <= 180) &&
                (Cb >=  85 && Cb <= 135);

            if (!isSkin) {
                dst[x] = p;
                continue;
            }

            // STEP 2: Convert to HSV
            double H, S, V;
            rgb2hsv(R, G, B, H, S, V);

            // STEP 3: apply modifications
            H += hueShift;      // degrees
            if (H >= 360) H -= 360;
            if (H <   0)  H += 360;

            S *= satFactor;
            if (S > 1) S = 1;

            // STEP 4: back to RGB
            int r2, g2, b2;
            hsv2rgb(H, S, V, r2, g2, b2);

            dst[x] = qRgba(clamp_i(r2), clamp_i(g2), clamp_i(b2), qAlpha(p));
        }
    }

    return out;
}


// --- Clone/Heal/Liquify implementations

static std::vector<double> generateRadialWeights(int radius){
    int size = radius*2 + 1;
    std::vector<double> w(size*size);
    double sigma = std::max(1.0, radius / 3.0);
    double twoSigma2 = 2.0 * sigma * sigma;
    double maxv = 0;
    for(int j=-radius;j<=radius;++j){
        for(int i=-radius;i<=radius;++i){
            double r2 = double(i*i + j*j);
            double v = std::exp(-r2 / twoSigma2);
            w[(j+radius)*size + (i+radius)] = v;
            if(v > maxv) maxv = v;
        }
    }
    if(maxv > 0) for(double &v: w) v /= maxv;
    return w;
}

static QRgb blendWeighted(QRgb dst, QRgb src, double w){
    int r = clamp_i(int((1.0-w)*qRed(dst) + w*qRed(src) + 0.5));
    int g = clamp_i(int((1.0-w)*qGreen(dst) + w*qGreen(src) + 0.5));
    int b = clamp_i(int((1.0-w)*qBlue(dst) + w*qBlue(src) + 0.5));
    int a = clamp_i(int((1.0-w)*qAlpha(dst) + w*qAlpha(src) + 0.5));
    return qRgba(r,g,b,a);
}

void ImageProcessor::applyCloneStamp(QImage &image, const QPoint &srcCenter, const QPoint &dstCenter, int radius, double hardness){
    if(image.format() != QImage::Format_ARGB32) image = image.convertToFormat(QImage::Format_ARGB32);
    int w=image.width(), h=image.height();
    if(radius<=0) return;
    auto weights = generateRadialWeights(radius);
    int size = radius*2 + 1;
    for(int j=-radius;j<=radius;++j){
        int y = dstCenter.y() + j;
        int sy = srcCenter.y() + j;
        if(y<0||y>=h||sy<0||sy>=h) continue;
        for(int i=-radius;i<=radius;++i){
            int x = dstCenter.x() + i;
            int sx = srcCenter.x() + i;
            if(x<0||x>=w||sx<0||sx>=w) continue;
            int idx = (j+radius)*size + (i+radius);
            double mask = weights[idx];
            double m = std::pow(mask, 1.0 / std::max(0.001, hardness));
            QRgb s = image.pixel(sx, sy);
            QRgb d = image.pixel(x, y);
            QRgb out = blendWeighted(d, s, m);
            image.setPixel(x,y,out);
        }
    }
}

void ImageProcessor::applyHealPatch(QImage &image, const QPoint &srcCenter, const QPoint &dstCenter, int radius, double hardness){
    if(image.format() != QImage::Format_ARGB32) image = image.convertToFormat(QImage::Format_ARGB32);
    int w=image.width(), h=image.height();
    if(radius<=0) return;
    auto weights = generateRadialWeights(radius);
    int size = radius*2 + 1;
    double sumSr=0,sumSg=0,sumSb=0,cntS=0;
    double sumTr=0,sumTg=0,sumTb=0,cntT=0;
    for(int j=-radius;j<=radius;++j){
        int sy = srcCenter.y()+j;
        int ty = dstCenter.y()+j;
        for(int i=-radius;i<=radius;++i){
            int sx = srcCenter.x()+i;
            int tx = dstCenter.x()+i;
            int idx = (j+radius)*size + (i+radius);
            double mask = weights[idx];
            if(mask < 1e-3) continue;
            if(sx>=0 && sx<w && sy>=0 && sy<h){
                QRgb p = image.pixel(sx, sy);
                sumSr += qRed(p)*mask; sumSg += qGreen(p)*mask; sumSb += qBlue(p)*mask; cntS += mask;
            }
            if(tx>=0 && tx<w && ty>=0 && ty<h){
                QRgb p = image.pixel(tx, ty);
                sumTr += qRed(p)*mask; sumTg += qGreen(p)*mask; sumTb += qBlue(p)*mask; cntT += mask;
            }
        }
    }
    if(cntS < 1e-6 || cntT < 1e-6) return;
    double avgSr = sumSr/cntS; double avgSg = sumSg/cntS; double avgSb = sumSb/cntS;
    double avgTr = sumTr/cntT; double avgTg = sumTg/cntT; double avgTb = sumTb/cntT;
    double addR = avgTr - avgSr;
    double addG = avgTg - avgSg;
    double addB = avgTb - avgSb;
    for(int j=-radius;j<=radius;++j){
        int y = dstCenter.y()+j;
        int sy = srcCenter.y()+j;
        if(y<0||y>=h||sy<0||sy>=h) continue;
        for(int i=-radius;i<=radius;++i){
            int x = dstCenter.x()+i;
            int sx = srcCenter.x()+i;
            if(x<0||x>=w||sx<0||sx>=w) continue;
            int idx = (j+radius)*size + (i+radius);
            double mask = weights[idx];
            if(mask < 1e-3) continue;
            double m = std::pow(mask, 1.0 / std::max(0.001, hardness));
            QRgb s = image.pixel(sx, sy);
            int r = clamp_i(int(qRed(s) + addR + 0.5));
            int g = clamp_i(int(qGreen(s) + addG + 0.5));
            int b = clamp_i(int(qBlue(s) + addB + 0.5));
            QRgb sAdj = qRgba(r,g,b, qAlpha(s));
            QRgb d = image.pixel(x,y);
            QRgb out = blendWeighted(d, sAdj, m);
            image.setPixel(x,y,out);
        }
    }
}

void ImageProcessor::applyLiquifyStroke(QImage &image, const QPoint &pos, const QPointF &displacement, int radius){
    if(image.format() != QImage::Format_ARGB32) image = image.convertToFormat(QImage::Format_ARGB32);
    int w=image.width(), h=image.height();
    if(radius<=0) return;
    int x0 = std::max(0, pos.x() - radius);
    int y0 = std::max(0, pos.y() - radius);
    int x1 = std::min(w-1, pos.x() + radius);
    int y1 = std::min(h-1, pos.y() + radius);
    int rw = x1 - x0 + 1;
    int rh = y1 - y0 + 1;
    QImage srcRegion(rw, rh, QImage::Format_ARGB32);
    for(int yy=0; yy<rh; ++yy){
        const QRgb *sline = reinterpret_cast<const QRgb*>(image.constScanLine(y0 + yy));
        QRgb *dline = reinterpret_cast<QRgb*>(srcRegion.scanLine(yy));
        for(int xx=0; xx<rw; ++xx) dline[xx] = sline[x0 + xx];
    }
    double sigma = std::max(0.5, radius / 2.0);
    double twoSigma2 = 2.0*sigma*sigma;
    for(int yy=0; yy<rh; ++yy){
        int gy = y0 + yy;
        for(int xx=0; xx<rw; ++xx){
            int gx = x0 + xx;
            double dx = gx - pos.x();
            double dy = gy - pos.y();
            double d2 = dx*dx + dy*dy;
            if(d2 > (double)radius*radius) continue;
            double wght = std::exp(-d2 / twoSigma2);
            double shiftX = displacement.x() * wght;
            double shiftY = displacement.y() * wght;
            double srcX = (gx + shiftX) - x0;
            double srcY = (gy + shiftY) - y0;
            int sw = srcRegion.width(), sh = srcRegion.height();
            srcX = clampValue(srcX, 0.0, double(sw-1));
            srcY = clampValue(srcY, 0.0, double(sh-1));
            int x0s = int(std::floor(srcX));
            int y0s = int(std::floor(srcY));
            int x1s = std::min(x0s+1, sw-1);
            int y1s = std::min(y0s+1, sh-1);
            double fx = srcX - x0s;
            double fy = srcY - y0s;
            QRgb p00 = srcRegion.pixel(x0s, y0s);
            QRgb p10 = srcRegion.pixel(x1s, y0s);
            QRgb p01 = srcRegion.pixel(x0s, y1s);
            QRgb p11 = srcRegion.pixel(x1s, y1s);
            auto lerp = [](double t, int a, int b)->double{ return a + t*(b-a); };
            int a = int(lerp(fy, lerp(fx, qAlpha(p00), qAlpha(p10)), lerp(fx, qAlpha(p01), qAlpha(p11))));
            int r = int(lerp(fy, lerp(fx, qRed(p00), qRed(p10)), lerp(fx, qRed(p01), qRed(p11))));
            int g = int(lerp(fy, lerp(fx, qGreen(p00), qGreen(p10)), lerp(fx, qGreen(p01), qGreen(p11))));
            int b = int(lerp(fy, lerp(fx, qBlue(p00), qBlue(p10)), lerp(fx, qBlue(p01), qBlue(p11))));
            image.setPixel(gx, gy, qRgba(clamp_i(r), clamp_i(g), clamp_i(b), clamp_i(a)));
        }
    }
}

// ================== HUE SHIFT =====================
QImage ImageProcessor::hueShift(const QImage &src, double degrees)
{
    QImage img = src.convertToFormat(QImage::Format_ARGB32);
    QImage out = img;

    double shift = degrees / 360.0;   // 30° → 0.0833
    if (shift == 0.0)
        return img;

    int w = img.width();
    int h = img.height();

    for (int y = 0; y < h; ++y)
    {
        QRgb *line = reinterpret_cast<QRgb*>(out.scanLine(y));
        const QRgb *srcLine = reinterpret_cast<const QRgb*>(img.constScanLine(y));

        for (int x = 0; x < w; ++x)
        {
            QColor c(srcLine[x]);

            double h, s, v;
            c.getHsvF(&h, &s, &v);

            h += shift;
            if (h < 0) h += 1.0;
            if (h > 1) h -= 1.0;

            QColor outC;
            outC.setHsvF(h, s, v, c.alphaF());
            line[x] = outC.rgba();
        }
    }

    return out;
}

