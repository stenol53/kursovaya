#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <Q3DSurface>
#include <QObject>
#include <QThread>

#include "surfacegraph.h"
#include "genalg.h"

using namespace QtDataVisualization;

class Window : public QObject
{

    Q_OBJECT
public:
    explicit Window(QObject *parent = nullptr);
    ~Window();
    void createWindow();

public slots:
    void on_startBrn_clicked();
    void on_GenAlg_finished();
    void on_iterationCountSB_valueChanged(int value);
    void increaseItieration(int i);
    void updateInfo(QVector<QVector3D> list);
    void setMinPoint(QVector3D point);

private:
    bool hasContex;
    QWidget *window;
    QFrame *leftFrame, *rightFrame;
    QVBoxLayout *mainLayout;
    QRadioButton *HimmelbauRBtn, *EkliRBtn, *RastriginRBtn, *SinCosRBtn;
    QPushButton *startBtn;
    QSpinBox *chromosomeCountSB, *iterationCountSB, *crossoverChance, *mutationChance, *timeOutSB;
    QLabel *iterationsPassed;
    QTextEdit *info;
    QLineEdit *minPoint;
    QCheckBox *leaveMinPoint;

    SurfaceGraph *surfaceGraph;

    quint16 seed;
};

#endif // MAINWINDOW_H
