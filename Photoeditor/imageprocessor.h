#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QPainter>
#include <QColor>
#include <QRgb>
#include <QtGlobal>
#include <QPoint>
#include <QRect>


namespace ImageProcessor {

// basic ops
QImage changeExposure(const QImage &src, double factor);
QImage adjustBrightness(const QImage &src, int brightness);
QImage adjustContrast(const QImage &src, int contrast);
QImage autoWhiteBalanceGrayWorld(const QImage &src);
QImage gaussianBlur(const QImage &src, double sigma);
QImage unsharpMask(const QImage &src, double sigma, double amount);
QImage bilateralFilter(const QImage &src, int radius, double sigmaSpace, double sigmaColor);
QImage rotateBilinear(const QImage &src, double angleDeg, const QColor &bg = QColor(255,255,255));
QImage crop(const QImage &src, const QRect &rect);
QImage flipHorizontal(const QImage &src);
QImage flipVertical(const QImage &src);
QImage adjustSkinTone_HSV(const QImage &src, double hueShift, double satFactor);
QImage hueShift(const QImage &src, double degrees);



// clone / heal / liquify (in-place)
void applyCloneStamp(QImage &image, const QPoint &srcCenter, const QPoint &dstCenter, int radius, double hardness);
void applyHealPatch(QImage &image, const QPoint &srcCenter, const QPoint &dstCenter, int radius, double hardness);
void applyLiquifyStroke(QImage &image, const QPoint &pos, const QPointF &displacement, int radius);

} // namespace ImageProcessor

#endif // IMAGEPROCESSOR_H
