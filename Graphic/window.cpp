#include "window.h"

Window::Window(QObject *parent)
{
    QTime time(0,0,0);
    seed = static_cast<quint16>(time.secsTo(QTime::currentTime()));
    qDebug() << seed;
    srand(seed);
}

Window::~Window()
{

}

void Window::createWindow()
{
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    hasContex = graph->hasContext();
    if (!hasContex) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    } else {
        QSize screenSize = graph->screen()->size();
        container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
        container->setMaximumSize(screenSize);
        container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        container->setFocusPolicy(Qt::StrongFocus);

        window = new QWidget;
        mainLayout = new QVBoxLayout(window);
        leftFrame = new QFrame(window);
        leftFrame->setFixedWidth(300);
        rightFrame = new QFrame(window);
        rightFrame->setFixedWidth(300);

        info = new QTextEdit;
        info->setReadOnly(true);
        QBoxLayout *leftFrameLt = new QBoxLayout(QBoxLayout::TopToBottom);
        leftFrameLt->addWidget(info);
        leftFrame->setLayout(leftFrameLt);



        startBtn = new QPushButton("Старт", window);
        connect(startBtn,&QPushButton::clicked,this,&Window::on_startBrn_clicked);

        HimmelbauRBtn = new QRadioButton("Функция Химмельблау", window);
        EkliRBtn = new QRadioButton("Функция Экли", window);
        RastriginRBtn = new QRadioButton("Функция Растригина", window);
        SinCosRBtn = new QRadioButton("Функция Sin(x)*Cos(y)", window);

        QHBoxLayout *hLayoutForRBtns = new QHBoxLayout;
        hLayoutForRBtns->addItem(new QSpacerItem(0,20,QSizePolicy::Expanding,QSizePolicy::Expanding));
        hLayoutForRBtns->addWidget(HimmelbauRBtn);
        hLayoutForRBtns->addWidget(EkliRBtn);
        hLayoutForRBtns->addWidget(RastriginRBtn);
        hLayoutForRBtns->addWidget(SinCosRBtn);
        hLayoutForRBtns->addItem(new QSpacerItem(0,20,QSizePolicy::Expanding,QSizePolicy::Expanding));

        QVBoxLayout *vLayout_0 = new QVBoxLayout;
        vLayout_0->addLayout(hLayoutForRBtns,0);
        vLayout_0->addWidget(container,1);

        QHBoxLayout *hLayout_0 = new QHBoxLayout;
        hLayout_0->addWidget(leftFrame);
        hLayout_0->addLayout(vLayout_0);
        hLayout_0->addWidget(rightFrame);

        mainLayout->addLayout(hLayout_0);
        mainLayout->addWidget(startBtn);


        QBoxLayout *rightFrameLt = new QBoxLayout(QBoxLayout::TopToBottom);
        QLabel *chromosomeLbl = new QLabel("Число хромосом:", window);
        chromosomeLbl->setAlignment(Qt::AlignHCenter);
        chromosomeCountSB = new QSpinBox(window);
        chromosomeCountSB->setRange(0,500);
        chromosomeCountSB->setValue(100);
        chromosomeCountSB->setAlignment(Qt::AlignHCenter);
        QLabel *iterationLbl = new QLabel("Число итераций:", window);
        iterationLbl->setAlignment(Qt::AlignHCenter);
        iterationCountSB = new QSpinBox(window);
        iterationCountSB->setRange(0,5000);
        iterationCountSB->setValue(200);
        iterationCountSB->setAlignment(Qt::AlignHCenter);
        QLabel *timeOutLbl = new QLabel("Задержка между итерациями в мс:", window);
        timeOutLbl->setAlignment(Qt::AlignHCenter);
        timeOutSB = new QSpinBox(window);
        timeOutSB->setRange(0,1000);
        timeOutSB->setValue(50);
        timeOutSB->setAlignment(Qt::AlignHCenter);
        iterationsPassed = new QLabel("Итерация: 0/200",window);
        iterationsPassed->setAlignment(Qt::AlignHCenter);
        connect(iterationCountSB,QOverload<int>::of(&QSpinBox::valueChanged),this,&Window::on_iterationCountSB_valueChanged);

        QLabel *crossoverChanceLbl = new QLabel("Вероятность кроссовера:", window);
        crossoverChanceLbl->setAlignment(Qt::AlignHCenter);
        crossoverChance = new QSpinBox(window);
        crossoverChance->setRange(0,100);
        crossoverChance->setValue(50);
        crossoverChance->setAlignment(Qt::AlignHCenter);

        QLabel *mutationChanceLbl = new QLabel("Вероятность мутации:", window);
        mutationChanceLbl->setAlignment(Qt::AlignHCenter);
        mutationChance = new QSpinBox(window);
        mutationChance->setRange(0,100);
        mutationChance->setValue(10);
        mutationChance->setAlignment(Qt::AlignHCenter);

        QLabel *intervalLbl = new QLabel("Интервал:", window);
        intervalLbl->setAlignment(Qt::AlignHCenter);

        QBoxLayout *hLt_1 = new QBoxLayout(QBoxLayout::LeftToRight);
        QLabel *fromLbl = new QLabel("От", window);
        QLineEdit *fromEdit = new QLineEdit(window);
        fromEdit->setText("-5");
        fromEdit->setReadOnly(true);
        fromEdit->setAlignment(Qt::AlignHCenter);
        hLt_1->addWidget(fromLbl);
        hLt_1->addWidget(fromEdit);

        QBoxLayout *hLt_2 = new QBoxLayout(QBoxLayout::LeftToRight);
        QLabel *toLbl = new QLabel("До", window);
        QLineEdit *toEdit = new QLineEdit(window);
        toEdit->setText("5");
        toEdit->setReadOnly(true);
        toEdit->setAlignment(Qt::AlignHCenter);
        hLt_2->addWidget(toLbl);
        hLt_2->addWidget(toEdit);

        leaveMinPoint = new QCheckBox("Показать только точку минимума", window);

        QLabel *minPointLbl = new QLabel("Точка минимума:", window);
        minPointLbl->setAlignment(Qt::AlignHCenter);
        minPoint = new QLineEdit(window);
        minPoint->setAlignment(Qt::AlignHCenter);
        minPoint->setReadOnly(true);

        rightFrameLt->addWidget(chromosomeLbl);
        rightFrameLt->addWidget(chromosomeCountSB);
        rightFrameLt->addWidget(iterationLbl);
        rightFrameLt->addWidget(iterationCountSB);
        rightFrameLt->addWidget(timeOutLbl);
        rightFrameLt->addWidget(timeOutSB);
        rightFrameLt->addWidget(crossoverChanceLbl);
        rightFrameLt->addWidget(crossoverChance);
        rightFrameLt->addWidget(mutationChanceLbl);
        rightFrameLt->addWidget(mutationChance);
        rightFrameLt->addWidget(intervalLbl);
        rightFrameLt->addLayout(hLt_1);
        rightFrameLt->addLayout(hLt_2);
        rightFrameLt->addWidget(leaveMinPoint);
        rightFrameLt->addItem(new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        rightFrameLt->addWidget(minPointLbl);
        rightFrameLt->addWidget(minPoint);
        rightFrameLt->addWidget(iterationsPassed);
        rightFrameLt->addItem(new QSpacerItem(0,20,QSizePolicy::Expanding,QSizePolicy::Expanding));

        rightFrame->setLayout(rightFrameLt);

        surfaceGraph = new SurfaceGraph(graph);
        connect(SinCosRBtn,&QCheckBox::clicked, surfaceGraph,&SurfaceGraph::drawSinCos);
        connect(HimmelbauRBtn,&QCheckBox::clicked, surfaceGraph,&SurfaceGraph::drawHimmelblau);
        connect(EkliRBtn,&QCheckBox::clicked, surfaceGraph,&SurfaceGraph::drawEkli);
        connect(RastriginRBtn,&QCheckBox::clicked,surfaceGraph,&SurfaceGraph::drawRastrigin);

        connect(leaveMinPoint,&QCheckBox::clicked,surfaceGraph,&SurfaceGraph::leaveMinPointOnly);


        SinCosRBtn->setChecked(true);
        surfaceGraph->drawSinCos();


        window->show();
    }
}

void Window::on_startBrn_clicked()
{
    SinCosRBtn->setEnabled(false);
    RastriginRBtn->setEnabled(false);
    EkliRBtn->setEnabled(false);
    HimmelbauRBtn->setEnabled(false);

    timeOutSB->setEnabled(false);
    chromosomeCountSB->setEnabled(false);
    iterationCountSB->setEnabled(false);
    crossoverChance->setEnabled(false);
    mutationChance->setEnabled(false);
    startBtn->setEnabled(false);



    GenAlg *ALG = new GenAlg;
    QThread *thread = new QThread;
    ALG->moveToThread(thread);

    connect(ALG,&GenAlg::finished,this,&Window::on_GenAlg_finished);
    connect(thread,&QThread::started,ALG,&GenAlg::startAlg);
    connect(ALG,&GenAlg::finished,thread,&QThread::quit);
    connect(ALG,&GenAlg::finished,ALG,&GenAlg::deleteLater);
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    connect(ALG,&GenAlg::drawPointSignal,surfaceGraph,&SurfaceGraph::setItem);
    connect(ALG,&GenAlg::increaseIteration,this,&Window::increaseItieration);
    connect(ALG,&GenAlg::updateInfo,this,&Window::updateInfo);
    connect(ALG,&GenAlg::updateMinPoint,this,&Window::setMinPoint);


    ALG->setSeed(seed);
    ALG->setTimeOut(timeOutSB->value());
    ALG->setPopulationCount(chromosomeCountSB->value());
    ALG->setIterationCount(iterationCountSB->value());
    ALG->setOC_chance(crossoverChance->value());
    ALG->setMutation_chance(mutationChance->value());
    if(SinCosRBtn->isChecked())
        ALG->setFunc(0);
    else if(RastriginRBtn->isChecked())
        ALG->setFunc(1);
    else if(EkliRBtn->isChecked())
        ALG->setFunc(3);
    else if(HimmelbauRBtn->isChecked())
        ALG->setFunc(4);


    thread->start();
}

void Window::on_GenAlg_finished()
{
    SinCosRBtn->setEnabled(true);
    RastriginRBtn->setEnabled(true);
    EkliRBtn->setEnabled(true);
    HimmelbauRBtn->setEnabled(true);

    timeOutSB->setEnabled(true);
    chromosomeCountSB->setEnabled(true);
    iterationCountSB->setEnabled(true);
    crossoverChance->setEnabled(true);
    mutationChance->setEnabled(true);
    startBtn->setEnabled(true);
}

void Window::on_iterationCountSB_valueChanged(int value)
{
    iterationsPassed->setText(QString("Итерация: 0/%1").arg(QString::number(value)));
}

void Window::increaseItieration(int i)
{
    iterationsPassed->setText(QString("Итерация: %1/%2").arg(QString::number(i),QString::number(iterationCountSB->value())));
}

void Window::updateInfo(QVector<QVector3D> list)
{
    info->clear();
    for(int i = 0; i < list.count(); i++) {
        float x = list[i].x();
        float y = list[i].y();
        float z = list[i].z();

        info->append(QString("%1: (%2, %3, %4)").arg(QString::number(i+1),QString::number(x), QString::number(z), QString::number(y)));
    }
}

void Window::setMinPoint(QVector3D point)
{
    minPoint->setText(QString("(%1, %2, %3)").arg(QString::number(point.x()),QString::number(point.z()),QString::number(point.y())));
}
