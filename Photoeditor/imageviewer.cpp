#include "imageviewer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent),
    m_zoom(1.0), m_selecting(false), m_tool(Tool_None), m_brushRadius(40), m_brushActive(false)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

void ImageViewer::setImage(const QImage &img, bool /*keepHistory*/){
    m_image = img;
    updateGeometry();
    update();
}

void ImageViewer::setTool(Tool t){
    m_tool = t;
    m_selecting = false;
    m_brushActive = false;
    update();
}

void ImageViewer::clearSelection(){
    m_selection = QRect();
    update();
    emit selectionChanged(m_selection);
}

QSize ImageViewer::sizeHint() const{
    if(m_image.isNull()) return {600,400};
    return QSize(int(m_image.width()*m_zoom), int(m_image.height()*m_zoom));
}

void ImageViewer::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(rect(), palette().color(QPalette::Base));
    if(m_image.isNull()) return;
    QImage disp = m_image.scaled(int(m_image.width()*m_zoom), int(m_image.height()*m_zoom), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    p.drawImage(0,0, disp);
    if(!m_selection.isNull()){
        QRect r = m_selection;
        QRect drawR(int(r.left()*m_zoom), int(r.top()*m_zoom), int(r.width()*m_zoom), int(r.height()*m_zoom));
        QPen pen(Qt::red);
        pen.setWidth(2);
        p.setPen(pen);
        p.setBrush(Qt::NoBrush);
        p.drawRect(drawR);
    }
    if(m_tool == Tool_Clone || m_tool == Tool_Heal || m_tool == Tool_Liquify){
        QPoint pos = mapFromGlobal(QCursor::pos());
        if(rect().contains(pos)){
            QPen pen(Qt::yellow);
            pen.setWidth(2);
            p.setPen(pen);
            p.setBrush(Qt::NoBrush);
            int r = int(m_brushRadius * m_zoom);
            p.drawEllipse(QPoint(pos.x(), pos.y()), r, r);
        }
    }
}

void ImageViewer::wheelEvent(QWheelEvent *ev){
    const double factor = 1.15;
    if(ev->angleDelta().y() > 0) m_zoom *= factor;
    else m_zoom /= factor;
    if(m_zoom < 0.05) m_zoom = 0.05;
    if(m_zoom > 40.0) m_zoom = 40.0;
    updateGeometry();
    update();
}

void ImageViewer::mousePressEvent(QMouseEvent *ev){
    if(m_image.isNull()) return;
    QPoint imgPos(int(ev->pos().x() / m_zoom), int(ev->pos().y() / m_zoom));
    if(ev->button() == Qt::LeftButton){
        if(m_tool == Tool_Select){
            m_selecting = true;
            m_dragStart = ev->pos();
        } else if(m_tool == Tool_Clone || m_tool == Tool_Heal || m_tool == Tool_Liquify){
            m_brushActive = true;
            m_lastBrushPos = imgPos;
            emit brushStarted(imgPos, ev->buttons(), ev->modifiers());
        }
    } else if(ev->button() == Qt::RightButton){
        if(m_tool == Tool_Clone || m_tool == Tool_Heal){
            emit brushStarted(imgPos, ev->buttons(), ev->modifiers());
        }
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *ev){
    if(m_image.isNull()) return;
    QPoint imgPos(int(ev->pos().x() / m_zoom), int(ev->pos().y() / m_zoom));
    if(m_selecting){
        QPoint p1 = QPoint(int(m_dragStart.x()/m_zoom), int(m_dragStart.y()/m_zoom));
        QPoint p2 = QPoint(int(ev->pos().x()/m_zoom), int(ev->pos().y()/m_zoom));
        QRect r(p1,p2);
        r = r.normalized().intersected(m_image.rect());
        m_selection = r;
        update();
        emit selectionChanged(m_selection);
    } else if(m_brushActive){
        emit brushMoved(imgPos, ev->buttons(), ev->modifiers());
        m_lastBrushPos = imgPos;
    } else {
        update();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *ev){
    if(m_image.isNull()) return;
    QPoint imgPos(int(ev->pos().x() / m_zoom), int(ev->pos().y() / m_zoom));
    if(ev->button() == Qt::LeftButton){
        if(m_selecting){
            m_selecting = false;
            emit selectionChanged(m_selection);
        } else if(m_brushActive){
            emit brushFinished(imgPos, ev->buttons(), ev->modifiers());
            m_brushActive = false;
        }
    }
}
