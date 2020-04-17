#include "genalg.h"

GenAlg::GenAlg(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QVector<QVector3D>>("QVector<QVector3D>");
}

void GenAlg::startAlg()
{
    for(int i = 0; i < populationCount; i++)
    {
        Chromosome chrom;
        for(int j = 0; j < genLenght; j++) {
            chrom.locus1 = createRandomLokus();
            chrom.locus2 = createRandomLokus();
        }
        chrom.adaptability = countAdaptability(toDec(chrom.locus1),toDec(chrom.locus2));
        populationList.append(chrom);
    }

    for(int i = 0; i < iterationCount; i++) {
        emit increaseIteration(i+1);

        pointsToDraw.clear();
        for(int j = 0; j < populationCount; j++) {
            pointsToDraw.append(QVector3D(toDec(populationList[j].locus1),populationList[j].adaptability,toDec(populationList[j].locus2)));
        }
        emit drawPointSignal(pointsToDraw);
        emit updateInfo(pointsToDraw);
        emit updateMinPoint(pointsToDraw[0]);

        QVector<Chromosome> children = selectionMethod();
        populationList.append(children);
        populationList = sort(populationList);
        populationList.remove(populationCount, populationList.count() - populationCount);
        densityGenMutation();

      QThread::msleep(static_cast<unsigned long>(timeOut));
    }

    qDebug() << populationList[0].locus1 << populationList[0].locus2;

    emit finished();
}

float GenAlg::toDec(QString binNum)
{
    float decNum = 0;
    float st = 4;

    for(int i = 1; i < binNum.count(); i++) {
        decNum += QString(binNum[i]).toInt() * st;
        st /= 2;
    }
    if(binNum[0] == "1")
        decNum *= -1;

    return decNum;
}

QVector<GenAlg::Chromosome> GenAlg::OnePointCrossover(Chromosome H1, Chromosome H2)
{
    QVector<Chromosome> list;

    int j = 1 + rand() % (2*genLenght - 1);
    QString Chromo_1 = H1.locus1 + H1.locus2, Chromo_2 = H2.locus1 + H2.locus2,
            newChromo_1 = Chromo_1, newChromo_2 = Chromo_2;

    for(int i = j; i < Chromo_1.count(); i++) {
        newChromo_1[i] = Chromo_2[i];
        newChromo_2[i] = Chromo_1[i];
    }
    Chromosome newH1, newH2;
    newH1.locus1 = newChromo_1.left(genLenght);
    newH1.locus2 = newChromo_1.right(genLenght);
    newH2.locus1 = newChromo_2.left(genLenght);
    newH2.locus2 = newChromo_2.right(genLenght);

    list.append(newH1);
    list.append(newH2);

    return list;
}

void GenAlg::densityGenMutation()
{
    int needMutationCount = static_cast<int>(populationCount * mutation_chance / 100.0f);
    QSet<int> ignoreList;
    int k = 0;
    while(k < needMutationCount){
        int needMutation = rand() % populationCount;
        if(!ignoreList.contains(needMutation)) {
            ignoreList.insert(needMutation);

            QString H = populationList[needMutation].locus1 + populationList[needMutation].locus2;
            int x = rand() % genLenght;
            H[x] == "1" ? H.replace(x,1,"0") : H.replace(x,1,"1");

            if(toDec(H.left(genLenght)) > 5.0f || toDec(H.left(genLenght)) < -5.0f ||
                    toDec(H.right(genLenght)) > 5.0f || toDec(H.right(genLenght)) < -5.0f) {
                populationList[needMutation].locus1 = createRandomLokus();
                populationList[needMutation].locus2 = createRandomLokus();
                populationList[needMutation].adaptability = countAdaptability(toDec(populationList[needMutation].locus1),
                                                                              toDec(populationList[needMutation].locus2));
            } else {
                populationList[needMutation].locus1 = H.left(genLenght);
                populationList[needMutation].locus2 = H.right(genLenght);
                populationList[needMutation].adaptability = countAdaptability(toDec(populationList[needMutation].locus1),
                                                                              toDec(populationList[needMutation].locus2));
            }
            k++;
        }
    }
}

void GenAlg::setFunc(int value)
{
    func = value;
}

void GenAlg::setPopulationCount(int value)
{
    populationCount = value;
}

void GenAlg::setIterationCount(int value)
{
    iterationCount = value;
}

QVector<GenAlg::Chromosome> GenAlg::selectionMethod()
{
    float avgAdapt = 0.0f;
    for(int i = 0; i < populationCount; i++) {
        avgAdapt += populationList[i].adaptability;
    }
    avgAdapt /= populationCount;

    QVector <Chromosome> selected;
    for(int i = 0; i < populationCount; i++) {
        if(populationList[i].adaptability >= avgAdapt)
            selected.append(populationList[i]);
    }
    int parentCount =  static_cast<int>(selected.count() * OC_chance / 100.0f);

    selected = sort(selected);

    QVector <Chromosome> newPopulation;
    for(int i = 0; i < parentCount; i++) {
        int parent_1 = rand() % parentCount,
                parent_2 = rand() % parentCount;
        newPopulation.append(OnePointCrossover(selected[parent_1], selected[parent_2]));
    }

    for(int i = 0; i < newPopulation.count(); i++) {
        newPopulation[i].adaptability = countAdaptability(toDec(newPopulation[i].locus1), toDec(newPopulation[i].locus2));
    }

    return newPopulation;
}

QVector<GenAlg::Chromosome> GenAlg::sort(QVector<GenAlg::Chromosome> list)
{
    for(int i = 0; i < list.count()-1; i++) {
        for(int j = 0; j < list.count() - i - 1; j++) {
            if(list[j].adaptability > list[j+1].adaptability) {
                Chromosome temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
    return list;
}

float GenAlg::countAdaptability(float x, float y)
{
    float result;
    switch (func) {
    case 0:
        result = Functions::SinCos(x, y);
        break;
    case 1:
        result = Functions::Rastrigin(x, y);
        break;
    case 3:
        result = Functions::Ekli(x, y);
        break;
    case 4:
        result = Functions::Himmelblau(x, y);
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

QString GenAlg::createRandomLokus()
{
    QString result = "";
    QStringList integerPart = {"000", "001", "010", "011", "100", "101"},
            floatPart = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001",
                        "1010", "1011", "1100", "1101", "1110", "1111"},
            posOrNeg = {"0", "1"};

    int randomNum = rand() % 2;
    result += posOrNeg[randomNum];
    randomNum = rand() % integerPart.count();
    if(integerPart[randomNum] == "101") {
        result += integerPart[randomNum] + floatPart[0] + floatPart[0] + floatPart[0] + floatPart[0];
    } else {
        result += integerPart[randomNum];
        for(int i = 0; i < 4; i++) {
            randomNum = rand() % floatPart.count();
            result += floatPart[randomNum];
        }
    }
    return result;
}

void GenAlg::setTimeOut(int value)
{
    timeOut = value;
}

void GenAlg::setMutation_chance(int value)
{
    mutation_chance = value;
}

void GenAlg::setSeed(quint16 value)
{
    seed = value;
}

void GenAlg::setOC_chance(int value)
{
    OC_chance = value;
}























