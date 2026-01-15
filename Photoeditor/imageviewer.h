#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QRect>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = nullptr);

    enum Tool { Tool_None=0, Tool_Select, Tool_Clone, Tool_Heal, Tool_Liquify, Tool_Pan };

    void setImage(const QImage &img, bool keepHistory=false);
    QImage image() const { return m_image; }

    void setTool(Tool t);
    Tool tool() const { return m_tool; }
    void setBrushRadius(int r) { m_brushRadius = r; update(); }
    int brushRadius() const { return m_brushRadius; }

    QRect selection() const { return m_selection; }
    void clearSelection();

signals:
    void selectionChanged(const QRect &r);
    void brushStarted(const QPoint &imgPos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);
    void brushMoved(const QPoint &imgPos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);
    void brushFinished(const QPoint &imgPos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);

protected:
    void paintEvent(QPaintEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    QSize sizeHint() const override;

private:
    QImage m_image;
    double m_zoom;
    QRect m_selection;
    bool m_selecting;
    enum Tool m_tool;
    int m_brushRadius;
    bool m_brushActive;
    QPoint m_dragStart;
    QPoint m_lastBrushPos;
};

#endif // IMAGEVIEWER_H
