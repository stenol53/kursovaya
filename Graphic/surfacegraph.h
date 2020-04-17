#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QObject>
#include <QtDataVisualization>
#include <QVector3D>
#include <QCustom3DItem>
#include <QDebug>

#include "functions.h"

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface);

signals:

public slots:
    void drawSinCos();
    void drawHimmelblau();
    void drawEkli();
    void drawRastrigin();
    void setItem(QVector<QVector3D> arr);
    void leaveMinPointOnly(bool isChecked);

private:
    Q3DSurface *graph;
    QSurface3DSeries *currentSeries = nullptr;

    QSurfaceDataProxy *SinCosDataProxy;
    QSurface3DSeries *SinCosSeries;

    QSurfaceDataProxy *HimmelblauDataProxy;
    QSurface3DSeries *HimmelblauSeries;

    QSurfaceDataProxy *EkliDataProxy;
    QSurface3DSeries *EkliSeries;

    QSurfaceDataProxy *RastriginDataProxy;
    QSurface3DSeries *RastriginSeries;

    QImage redSphere, blueSphere;

    const float axisMin = -5.0f, axisMax = 5.0f, step = 0.1f;
    int pointsCount;
    float *arrX, *arrY;
    QVector<QVector3D> pointsToDraw;
    bool minPointOnly = false;

    void fillSinCosProxy();
    void fillHimmelblauProxy();
    void fillEkliProxy();
    void fillRastrigin();
};

#endif // SURFACEGRAPH_H
