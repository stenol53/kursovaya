#ifndef GENALG_H
#define GENALG_H

#include <QObject>
#include <cmath>
#include <QDebug>
#include <QTime>
#include <QVector3D>
#include <QThread>

#include "functions.h"

#define PI 3.14f

class GenAlg : public QObject
{
    Q_OBJECT
public:
    explicit GenAlg(QObject *parent = nullptr);

signals:
    void finished();
    void drawPointSignal(QVector<QVector3D>);
    void increaseIteration(int);
    void updateInfo(QVector<QVector3D>);
    void updateMinPoint(QVector3D);

public slots:
    void startAlg();

public:
    float toDec(QString binNum);
    void densityGenMutation();
    void setFunc(int value);
    void setPopulationCount(int value);
    void setIterationCount(int value);
    void setOC_chance(int value);
    void setSeed(quint16 value);
    void setMutation_chance(int value);
    void setTimeOut(int value);

private:
    struct Chromosome
    {
        Chromosome() {}
        float adaptability;
        QString locus1 = "";
        QString locus2 = "";
    };
    QVector<Chromosome> populationList;

    QVector<Chromosome> OnePointCrossover(Chromosome H1, Chromosome H2);
    QVector<Chromosome> selectionMethod();
    QVector<Chromosome> sort(QVector<Chromosome> list);
    float countAdaptability(float x, float y);
    QString createRandomLokus();

    const int genLenght = 20;
    int populationCount, iterationCount, OC_chance, mutation_chance, timeOut;
    int func;
    quint16 seed;
    QVector<QVector3D> pointsToDraw;
};

#endif // GENALG_H
