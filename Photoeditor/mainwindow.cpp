#include "mainwindow.h"
#include "imageviewer.h"
#include "imageprocessor.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), historyIndex(-1), brushRadius(40)
{
    viewer = new ImageViewer(this);
    setCentralWidget(viewer);

    //
    // FILE MENU
    //
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, SLOT(onOpen()));
    fileMenu->addAction(tr("&Save As..."), this, SLOT(onSaveAs()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("E&xit"), this, SLOT(onExit()));

    //
    // EDIT MENU
    //
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    undoAct = editMenu->addAction(tr("&Undo"), this, SLOT(onUndo()));
    redoAct = editMenu->addAction(tr("&Redo"), this, SLOT(onRedo()));
    editMenu->addSeparator();

    editMenu->addAction(tr("Rotate..."), this, SLOT(onRotate()));
    editMenu->addAction(tr("Flip Horizontal"), this, SLOT(onFlipH()));
    editMenu->addAction(tr("Flip Vertical"), this, SLOT(onFlipV()));
    editMenu->addAction(tr("Crop to selection"), this, SLOT(onCrop()));
    editMenu->addSeparator();

    editMenu->addAction(tr("Exposure..."), this, SLOT(onExposure()));
    editMenu->addAction(tr("Auto White Balance"), this, SLOT(onAutoWB()));
    editMenu->addAction(tr("Brightness..."), this, SLOT(onBrightness()));
    editMenu->addAction(tr("Contrast..."), this, SLOT(onContrast()));
    editMenu->addSeparator();

    editMenu->addAction(tr("Gaussian Blur..."), this, SLOT(onGaussian()));
    editMenu->addAction(tr("Unsharp Mask..."), this, SLOT(onUnsharp()));
    editMenu->addAction(tr("Bilateral Filter..."), this, SLOT(onBilateral()));
    editMenu->addAction(tr("Skin Tone Correction..."), this, SLOT(onSkinTone()));

    //
    // TOOLBAR
    //
    QToolBar *tb = addToolBar(tr("Tools"));
    QAction *selAct   = tb->addAction(tr("Select"));
    QAction *cloneAct = tb->addAction(tr("Clone"));
    QAction *healAct  = tb->addAction(tr("Heal"));
    QAction *liqAct   = tb->addAction(tr("Liquify"));

    tb->addSeparator();
    tb->addAction(tr("Undo"), this, SLOT(onUndo()));
    tb->addAction(tr("Redo"), this, SLOT(onRedo()));

    connect(selAct,   &QAction::triggered, this, &MainWindow::onToolSelect);
    connect(cloneAct, &QAction::triggered, this, &MainWindow::onToolClone);
    connect(healAct,  &QAction::triggered, this, &MainWindow::onToolHeal);
    connect(liqAct,   &QAction::triggered, this, &MainWindow::onToolLiquify);

    //
    // DOCK (right panel)
    //
    QDockWidget *dock = new QDockWidget(tr("Tools & Adjustments"), this);
    QWidget *dockContent = new QWidget(dock);
    QVBoxLayout *vlay = new QVBoxLayout(dockContent);

    // Brush radius
    QLabel *lblBrush = new QLabel(tr("Brush size"));
    QSlider *sBrush = new QSlider(Qt::Horizontal);
    sBrush->setRange(4, 300);
    sBrush->setValue(brushRadius);
    connect(sBrush, &QSlider::valueChanged, this, &MainWindow::onBrushSizeChanged);
    vlay->addWidget(lblBrush);
    vlay->addWidget(sBrush);

    // Quick Exposure
    QLabel *lblExp = new QLabel(tr("Exposure multiplier"));
    QSlider *sExp = new QSlider(Qt::Horizontal);
    sExp->setRange(10, 400);  // 0.1–4.0
    sExp->setValue(100);
    QPushButton *bApplyExp = new QPushButton(tr("Apply Exposure"));
    connect(bApplyExp, &QPushButton::clicked, this, &MainWindow::onApplyExposure);
    vlay->addWidget(lblExp);
    vlay->addWidget(sExp);
    vlay->addWidget(bApplyExp);

    // Quick Gaussian
    QLabel *lblG = new QLabel(tr("Gaussian sigma (x10)"));
    QSlider *sG = new QSlider(Qt::Horizontal);
    sG->setRange(1, 500);
    sG->setValue(20);
    QPushButton *bApplyG = new QPushButton(tr("Apply Gaussian"));
    connect(bApplyG, &QPushButton::clicked, this, &MainWindow::onApplyGaussian);
    vlay->addWidget(lblG);
    vlay->addWidget(sG);
    vlay->addWidget(bApplyG);

    // Quick Unsharp
    QLabel *lblU = new QLabel(tr("Unsharp amount (x100)"));
    QSlider *sU = new QSlider(Qt::Horizontal);
    sU->setRange(0, 1000);
    sU->setValue(100);
    QPushButton *bApplyU = new QPushButton(tr("Apply Unsharp"));
    connect(bApplyU, &QPushButton::clicked, this, &MainWindow::onApplyUnsharp);
    vlay->addWidget(lblU);
    vlay->addWidget(sU);
    vlay->addWidget(bApplyU);

    vlay->addStretch(1);
    dockContent->setLayout(vlay);
    dock->setWidget(dockContent);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    statusBar()->showMessage(tr("Ready"));

    connect(viewer, &ImageViewer::selectionChanged, this, &MainWindow::selectionChanged);
    connect(viewer, &ImageViewer::brushStarted, this, &MainWindow::onBrushStarted);
    connect(viewer, &ImageViewer::brushMoved, this, &MainWindow::onBrushMoved);
    connect(viewer, &ImageViewer::brushFinished, this, &MainWindow::onBrushFinished);

    resize(1100,800);
    updateWindowTitle();
    updateUndoRedoActions();
}

MainWindow::~MainWindow(){}

//
// FILE ACTIONS
//

void MainWindow::onOpen(){
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (fn.isEmpty()) return;

    QImage img;
    if (!img.load(fn)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open image"));
        return;
    }

    currentPath = fn;
    setImage(img, true);
}

void MainWindow::onSaveAs(){
    if (currentImage.isNull()) {
        QMessageBox::warning(this, tr("Error"), tr("No image to save"));
        return;
    }

    QString fn = QFileDialog::getSaveFileName(
                    this, tr("Save image as"),
                    QString(),
                    tr("PNG (*.png);;JPG (*.jpg *.jpeg);;BMP (*.bmp)")
                 );

    if (fn.isEmpty()) return;

    if (!currentImage.save(fn)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save image"));
    } else {
        statusBar()->showMessage(tr("Saved %1").arg(fn), 3000);
    }
}

void MainWindow::onExit(){
    close();
}

//
// IMAGE STATE
//

void MainWindow::setImage(const QImage &img, bool pushHistory){
    currentImage = img.convertToFormat(QImage::Format_ARGB32);
    viewer->setImage(currentImage, false);

    if (pushHistory) pushHistoryState();

    updateWindowTitle();
    updateUndoRedoActions();
}

void MainWindow::pushHistoryState(){
    trimHistoryAfterCurrent();

    history.append(currentImage);
    const int MAX_HIST = 40;
    if (history.size() > MAX_HIST)
        history.remove(0);

    historyIndex = history.size() - 1;
    updateUndoRedoActions();
}

void MainWindow::trimHistoryAfterCurrent(){
    if (historyIndex + 1 < history.size()) {
        history.erase(history.begin() + historyIndex + 1, history.end());
    }
}

void MainWindow::updateWindowTitle(){
    QString title = tr("HdZhi_Editor");
    if (!currentPath.isEmpty()) title += " - " + QFileInfo(currentPath).fileName();
    setWindowTitle(title);
}

void MainWindow::updateUndoRedoActions(){
    if (undoAct) undoAct->setEnabled(historyIndex > 0);
    if (redoAct) redoAct->setEnabled(historyIndex + 1 < history.size());
}

//
// UNDO/REDO
//

void MainWindow::onUndo(){
    if (historyIndex > 0) {
        historyIndex--;
        currentImage = history[historyIndex];
        viewer->setImage(currentImage, false);
    }
    updateUndoRedoActions();
}

void MainWindow::onRedo(){
    if (historyIndex + 1 < history.size()) {
        historyIndex++;
        currentImage = history[historyIndex];
        viewer->setImage(currentImage, false);
    }
    updateUndoRedoActions();
}

//
// BASIC OPERATIONS
//

void MainWindow::onRotate(){
    bool ok;
    double a = QInputDialog::getDouble(
        this, tr("Rotate"), tr("Angle (degrees):"),
        90.0, -3600, 3600, 1, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::rotateBilinear(currentImage, a), true);
}

void MainWindow::onFlipH(){
    setImage(ImageProcessor::flipHorizontal(currentImage), true);
}

void MainWindow::onFlipV(){
    setImage(ImageProcessor::flipVertical(currentImage), true);
}

void MainWindow::selectionChanged(const QRect &r)
{
    if(!r.isNull()) {
        statusBar()->showMessage(
            tr("Selection: %1 × %2").arg(r.width()).arg(r.height()));
    } else {
        statusBar()->showMessage(tr("Ready"));
    }
}


void MainWindow::onCrop(){
    QRect sel = viewer->selection();

    if (sel.isNull() || sel.width() == 0 || sel.height() == 0) {
        QMessageBox::information(this, tr("Crop"),
                                 tr("No selection. Draw a rectangle first."));
        return;
    }

    QImage out = ImageProcessor::crop(currentImage, sel);
    viewer->clearSelection();
    setImage(out, true);
}

//
// ADJUSTMENTS
//

void MainWindow::onExposure(){
    bool ok;
    double mul = QInputDialog::getDouble(
        this, tr("Exposure"),
        tr("Exposure multiplier (1.0 = no change):"),
        1.0, 0.0, 100.0, 3, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::changeExposure(currentImage, mul), true);
}

void MainWindow::onBrightness(){
    bool ok;
    int br = QInputDialog::getInt(
        this, tr("Brightness"),
        tr("Brightness (-255 ... +255):"), 0, -255, 255, 1, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::adjustBrightness(currentImage, br), true);
}

void MainWindow::onContrast(){
    bool ok;
    int c = QInputDialog::getInt(
        this, tr("Contrast"),
        tr("Contrast (-255 ... +255):"), 0, -255, 255, 1, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::adjustContrast(currentImage, c), true);
}

void MainWindow::onHueShift()
{
    bool ok;
    double shift = QInputDialog::getDouble(
        this,
        tr("Hue Shift"),
        tr("Shift (–30 … +30 degrees):"),
        0.0,
        -30.0,
        30.0,
        1,
        &ok
    );
    if(!ok) return;

    pushHistoryState();
    setImage(ImageProcessor::hueShift(currentImage, shift), false);
    updateUndoRedoActions();
}


void MainWindow::onAutoWB(){
    setImage(ImageProcessor::autoWhiteBalanceGrayWorld(currentImage), true);
}

void MainWindow::onGaussian(){
    bool ok;
    double sigma = QInputDialog::getDouble(
        this, tr("Gaussian Blur"), tr("Sigma:"),
        2.0, 0.01, 100.0, 2, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::gaussianBlur(currentImage, sigma), true);
}

void MainWindow::onUnsharp(){
    bool ok;
    double sigma = QInputDialog::getDouble(
        this, tr("Unsharp Mask"), tr("Blur Sigma:"),
        1.5, 0.01, 50.0, 2, &ok
    );
    if (!ok) return;

    double amount = QInputDialog::getDouble(
        this, tr("Unsharp Mask"), tr("Amount (1.0 = normal):"),
        1.0, 0.0, 10.0, 2, &ok
    );
    if (!ok) return;

    setImage(ImageProcessor::unsharpMask(currentImage, sigma, amount), true);
}

void MainWindow::onBilateral(){
    bool ok;
    int radius = QInputDialog::getInt(
        this, tr("Bilateral filter"), tr("Radius (px):"),
        3, 1, 30, 1, &ok
    );
    if (!ok) return;

    double sigmaSpace = QInputDialog::getDouble(
        this, tr("Bilateral filter"), tr("Sigma spatial:"),
        radius, 0.1, 100.0, 1, &ok
    );
    if (!ok) return;

    double sigmaColor = QInputDialog::getDouble(
        this, tr("Bilateral filter"),
        tr("Sigma color (0..255):"), 30.0,
        0.1, 255.0, 1, &ok
    );
    if (!ok) return;

    setImage(
        ImageProcessor::bilateralFilter(currentImage, radius, sigmaSpace, sigmaColor),
        true
    );
}

//
// SKIN TONE CORRECTION
//

void MainWindow::onSkinTone()
{
    if (currentImage.isNull()) {
        QMessageBox::warning(this, tr("Skin Tone Correction"),
                             tr("Load an image first."));
        return;
    }

    bool ok1, ok2;

    int hue = QInputDialog::getInt(
        this,
        tr("Skin Tone Correction – Hue Shift"),
        tr("Hue shift (–30 ... +30 degrees):"),
        0,     // default
        -30, 30,
        1,
        &ok1
    );
    if (!ok1) return;

    double sat = QInputDialog::getDouble(
        this,
        tr("Skin Tone Correction – Saturation"),
        tr("Saturation factor (0.6 ... 1.6):"),
        1.15,
        0.6, 1.6,
        2,
        &ok2
    );
    if (!ok2) return;

    pushHistoryState();
    QImage out = ImageProcessor::adjustSkinTone_HSV(currentImage, hue, sat);
    setImage(out, false);
    updateUndoRedoActions();
}

//
// TOOL SELECTION
//

void MainWindow::onToolSelect(){
    viewer->setTool(ImageViewer::Tool_Select);
}

void MainWindow::onToolClone(){
    viewer->setTool(ImageViewer::Tool_Clone);
}

void MainWindow::onToolHeal(){
    viewer->setTool(ImageViewer::Tool_Heal);
}

void MainWindow::onToolLiquify(){
    viewer->setTool(ImageViewer::Tool_Liquify);
}

//
// BRUSH WORKFLOW
//

void MainWindow::onBrushSizeChanged(int v){
    brushRadius = v;
    viewer->setBrushRadius(v);
}

void MainWindow::onBrushStarted(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods){
    Q_UNUSED(buttons);

    if (mods & Qt::ControlModifier) {
        cloneSourcePoint = pos;
        statusBar()->showMessage(
            tr("Source set to (%1,%2)").arg(pos.x()).arg(pos.y()), 2000
        );
        return;
    }

    if (viewer->tool() == ImageViewer::Tool_Clone) {
        if (cloneSourcePoint.isNull()) {
            statusBar()->showMessage(tr("Ctrl + click to set clone source."), 3000);
            return;
        }
        pushHistoryState();
        ImageProcessor::applyCloneStamp(currentImage, cloneSourcePoint, pos, brushRadius, 0.6);
        viewer->setImage(currentImage, false);

    } else if (viewer->tool() == ImageViewer::Tool_Heal) {
        if (cloneSourcePoint.isNull()) {
            statusBar()->showMessage(tr("Ctrl + click to set heal source."), 3000);
            return;
        }
        pushHistoryState();
        ImageProcessor::applyHealPatch(currentImage, cloneSourcePoint, pos, brushRadius, 0.6);
        viewer->setImage(currentImage, false);

    } else if (viewer->tool() == ImageViewer::Tool_Liquify) {
        pushHistoryState();
        cloneSourcePoint = pos;
    }
}

void MainWindow::onBrushMoved(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods){
    Q_UNUSED(buttons);
    Q_UNUSED(mods);

    if (viewer->tool() == ImageViewer::Tool_Clone) {
        if (cloneSourcePoint.isNull()) return;
        ImageProcessor::applyCloneStamp(currentImage, cloneSourcePoint, pos, brushRadius, 0.6);
        viewer->setImage(currentImage, false);

    } else if (viewer->tool() == ImageViewer::Tool_Heal) {
        if (cloneSourcePoint.isNull()) return;
        ImageProcessor::applyHealPatch(currentImage, cloneSourcePoint, pos, brushRadius, 0.6);
        viewer->setImage(currentImage, false);

    } else if (viewer->tool() == ImageViewer::Tool_Liquify) {
        QPoint prev = cloneSourcePoint;
        QPoint current = pos;
        QPointF dispF = QPointF(current - prev);

        if (dispF.manhattanLength() == 0) return;

        ImageProcessor::applyLiquifyStroke(currentImage, prev, dispF, brushRadius);
        cloneSourcePoint = current;
        viewer->setImage(currentImage, false);
    }
}

void MainWindow::onBrushFinished(const QPoint &pos, Qt::MouseButtons buttons, Qt::KeyboardModifiers mods){
    Q_UNUSED(pos);
    Q_UNUSED(buttons);
    Q_UNUSED(mods);

    updateUndoRedoActions();
}


void MainWindow::onApplyExposure(){
    bool ok;
    double mul = QInputDialog::getDouble(
        this,
        tr("Quick Exposure"),
        tr("Multiplier (0.1..4.0):"),
        1.0,
        0.1, 4.0,
        2,
        &ok
    );

    if (!ok) return;

    pushHistoryState();
    setImage(ImageProcessor::changeExposure(currentImage, mul), false);
    updateUndoRedoActions();
}

void MainWindow::onApplyGaussian(){
    bool ok;
    double sigma = QInputDialog::getDouble(
        this,
        tr("Quick Gaussian"),
        tr("Sigma:"),
        2.0,
        0.01, 100.0,
        2,
        &ok
    );

    if (!ok) return;

    pushHistoryState();
    setImage(ImageProcessor::gaussianBlur(currentImage, sigma), false);
    updateUndoRedoActions();
}

void MainWindow::onApplyUnsharp(){
    bool ok;
    double sigma = QInputDialog::getDouble(
        this,
        tr("Quick Unsharp"),
        tr("Sigma:"),
        1.0,
        0.01, 50.0,
        2,
        &ok
    );
    if (!ok) return;

    double amount = QInputDialog::getDouble(
        this,
        tr("Quick Unsharp"),
        tr("Amount:"),
        1.0,
        0.0, 10.0,
        2,
        &ok
    );
    if (!ok) return;

    pushHistoryState();
    setImage(ImageProcessor::unsharpMask(currentImage, sigma, amount), false);
    updateUndoRedoActions();
}
