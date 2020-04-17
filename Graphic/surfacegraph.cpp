#include "surfacegraph.h"

SurfaceGraph::SurfaceGraph(Q3DSurface *surface)
    : graph(surface)
{
    graph->setAxisX(new QValue3DAxis);
    graph->setAxisY(new QValue3DAxis);
    graph->setAxisZ(new QValue3DAxis);

    SinCosDataProxy = new QSurfaceDataProxy;
    SinCosSeries = new QSurface3DSeries(SinCosDataProxy);

    HimmelblauDataProxy = new QSurfaceDataProxy;
    HimmelblauSeries = new QSurface3DSeries(HimmelblauDataProxy);

    EkliDataProxy = new QSurfaceDataProxy;
    EkliSeries = new QSurface3DSeries(EkliDataProxy);

    RastriginDataProxy = new QSurfaceDataProxy;
    RastriginSeries = new QSurface3DSeries(RastriginDataProxy);

    pointsCount = static_cast<int>((axisMax - axisMin) / step + 1);
    arrX = new float[pointsCount];
    arrY = new float[pointsCount];

    float startPoint = axisMin;
    for(int i = 0; i < pointsCount; i++)
    {
        arrX[i] = startPoint;
        arrY[i] = startPoint;
        startPoint += step;
    }

    fillSinCosProxy();
    fillHimmelblauProxy();
    fillEkliProxy();
    fillRastrigin();

    redSphere = QImage(2,2, QImage::Format_RGB32);
    redSphere.fill(Qt::red);

    blueSphere = QImage(10,10, QImage::Format_RGB32);
    blueSphere.fill(Qt::blue);
}

void SurfaceGraph::fillSinCosProxy()
{
    QSurfaceDataArray *dataArr = new QSurfaceDataArray;
    for(int i = 0; i < pointsCount; i++)
    {
        int index = 0;
        QSurfaceDataRow* dataRow = new QSurfaceDataRow(pointsCount);
        for(int j = 0; j < pointsCount; j++)
        {
            float x = arrX[i];
            float y = arrY[j];
            float z = Functions::SinCos(x, y);
            (*dataRow)[index++].setPosition(QVector3D(x, z, y));
        }
        *dataArr << dataRow;
    }
    SinCosDataProxy->resetArray(dataArr);
}

void SurfaceGraph::fillHimmelblauProxy()
{
    QSurfaceDataArray *dataArr = new QSurfaceDataArray;
    for(int i = 0; i < pointsCount; i++)
    {
        int index = 0;
        QSurfaceDataRow* dataRow = new QSurfaceDataRow(pointsCount);
        for(int j = 0; j < pointsCount; j++)
        {
            float x = arrX[i];
            float y = arrY[j];
            float z = Functions::Himmelblau(x, y);
            (*dataRow)[index++].setPosition(QVector3D(x, z, y));
        }
        *dataArr << dataRow;
    }
    HimmelblauDataProxy->resetArray(dataArr);
}

void SurfaceGraph::fillEkliProxy()
{
    QSurfaceDataArray *dataArr = new QSurfaceDataArray;
    for(int i = 0; i < pointsCount; i++)
    {
        int index = 0;
        QSurfaceDataRow* dataRow = new QSurfaceDataRow(pointsCount);
        for(int j = 0; j < pointsCount; j++)
        {
            float x = arrX[i];
            float y = arrY[j];
            float z = Functions::Ekli(x, y);
            (*dataRow)[index++].setPosition(QVector3D(x, z, y));
        }
        *dataArr << dataRow;
    }
    EkliDataProxy->resetArray(dataArr);
}

void SurfaceGraph::fillRastrigin()
{
    QSurfaceDataArray *dataArr = new QSurfaceDataArray;
    for(int i = 0; i < pointsCount; i++)
    {
        int index = 0;
        QSurfaceDataRow* dataRow = new QSurfaceDataRow(pointsCount);
        for(int j = 0; j < pointsCount; j++)
        {
            float x = arrX[i];
            float y = arrY[j];
            float z = Functions::Rastrigin(x, y);
            (*dataRow)[index++].setPosition(QVector3D(x, z, y));
        }
        *dataArr << dataRow;
    }
    RastriginDataProxy->resetArray(dataArr);
}

void SurfaceGraph::drawSinCos()
{
    graph->removeCustomItems();
    SinCosSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    SinCosSeries->setFlatShadingEnabled(true);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(-10.0, 10.0);
    graph->axisZ()->setRange(-10.0, 10.0);

    if(currentSeries != nullptr)
        graph->removeSeries(currentSeries);
    currentSeries = SinCosSeries;
    graph->addSeries(SinCosSeries);
}

void SurfaceGraph::drawHimmelblau()
{
    graph->removeCustomItems();
    HimmelblauSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    HimmelblauSeries->setFlatShadingEnabled(true);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(-10.0, 10.0);
    graph->axisZ()->setRange(-10.0, 10.0);

    if(currentSeries != nullptr)
        graph->removeSeries(currentSeries);
    currentSeries = HimmelblauSeries;
    graph->addSeries(HimmelblauSeries);
}

void SurfaceGraph::drawEkli()
{
    graph->removeCustomItems();
    EkliSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    EkliSeries->setFlatShadingEnabled(true);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(-10.0, 10.0);
    graph->axisZ()->setRange(-10.0, 10.0);

    if(currentSeries != nullptr)
        graph->removeSeries(currentSeries);
    currentSeries = EkliSeries;
    graph->addSeries(EkliSeries);
}

void SurfaceGraph::drawRastrigin()
{
    graph->removeCustomItems();
    RastriginSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    RastriginSeries->setFlatShadingEnabled(true);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(-10.0, 10.0);
    graph->axisZ()->setRange(-10.0, 10.0);

    if(currentSeries != nullptr)
        graph->removeSeries(currentSeries);
    currentSeries = RastriginSeries;
    graph->addSeries(RastriginSeries);
}

void SurfaceGraph::setItem(QVector<QVector3D> arr)
{
    pointsToDraw = arr;

    graph->removeCustomItems();
    if(!minPointOnly) {
        for(int i = 0; i < arr.count(); i++) {
            if(i == 0)
            {
                QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", arr[i],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                        QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), redSphere);
                graph->addCustomItem(item);
            } else {
                QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", arr[i],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                        QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), blueSphere);
                graph->addCustomItem(item);
            }
        }
    } else {
        QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", arr[0],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), redSphere);
        graph->addCustomItem(item);
    }
}

void SurfaceGraph::leaveMinPointOnly(bool isChecked)
{
    graph->removeCustomItems();
    if(isChecked) {
        minPointOnly = true;
        QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", pointsToDraw[0],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), redSphere);
        graph->addCustomItem(item);
    } else {
        minPointOnly = false;
        for(int i = 0; i < pointsToDraw.count(); i++) {
            if(i == 0)
            {
                QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", pointsToDraw[i],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                        QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), redSphere);
                graph->addCustomItem(item);
            } else {
                QCustom3DItem* item = new QCustom3DItem(":/mesh/spheres.obj", pointsToDraw[i],QVector3D(0.000025f, 0.000025f, 0.000025f),
                                                        QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f), blueSphere);
                graph->addCustomItem(item);
            }
        }
    }
}
