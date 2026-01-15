#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QVector>

class ImageViewer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpen();
    void onSaveAs();
    void onExit();

    void onRotate();
    void onFlipH();
    void onFlipV();
    void onCrop();
    void onExposure();
    void onAutoWB();
    void onGaussian();
    void onUnsharp();
    void onBilateral();


    void onUndo();
    void onRedo();

    void onToolSelect();
    void onToolClone();
    void onToolHeal();
    void onToolLiquify();

    void onBrushStarted(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);
    void onBrushMoved(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);
    void onBrushFinished(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods);

    //void selectionChanged(const QRect &r);

    void onBrushSizeChanged(int v);
    void onApplyExposure();
    void onApplyGaussian();
    void onApplyUnsharp();
    void onSkinTone();
    void selectionChanged(const QRect &r);

    void onBrightness();
    void onContrast();
    void onHueShift();



private:
    ImageViewer *viewer;
    QImage currentImage;
    QString currentPath;

    QVector<QImage> history;
    int historyIndex;

    void setImage(const QImage &img, bool pushHistory = true);
    void pushHistoryState();
    void trimHistoryAfterCurrent();
    void updateWindowTitle();
    void updateUndoRedoActions();

    QPoint cloneSourcePoint;
    int brushRadius;

    QAction *undoAct;
    QAction *redoAct;
};

#endif // MAINWINDOW_H
