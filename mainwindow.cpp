#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    timer = new QTimer(this);
    ui->saTitle->setWidget(ui->lTitle);
    connectSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bPlay_clicked()
{
    player->play();
    ui->bPlay->setDisabled(true);
    ui->bPause->setDisabled(false);
}

void MainWindow::on_bPause_clicked()
{
    player->pause();
    ui->bPause->setDisabled(true);
    ui->bPlay->setDisabled(false);
}

void MainWindow::on_sVolume_sliderMoved(int position)
{
    player->setVolume(position);
    changeVolIco();
}

void MainWindow::on_sProgres_sliderMoved(int position)
{
    player->setPosition(qint64(position));
}

void MainWindow::on_Position_change(qint64 position)
{
    ui->sProgres->setValue(position);
}

void MainWindow::on_Duration_change(qint64 position)
{
    ui->sProgres->setMaximum(position);
}

void MainWindow::on_bOpenFile_clicked()
{
    file = new QFileDialog;
    QString dict =file->getOpenFileName(this,tr("Open file"),"\\",tr("All Files (*.*)"));
    if(dict.length())
    {
        QStringList name = dict.split("/");
        ui->lTitle->setText(name.last());
        player->setMedia(QUrl::fromLocalFile(dict));
        player->play();
        ui->bPlay->setDisabled(true);
        ui->bPause->setDisabled(false);
    }else return;
}

void MainWindow::connectSlots()
{
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::on_Position_change);
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::on_Duration_change);
    connect(ui->bExit,&QPushButton::clicked,this,&MainWindow::close);
    connect(ui->bMin,&QPushButton::clicked,this,&MainWindow::showMinimized);
    connect(timer,&QTimer::timeout,this,&MainWindow::on_Timer_timeout);
}

void MainWindow::changeVolIco()
{
    if(ui->sVolume->value()>=50)
        ui->bMute->setIcon(QIcon(":/new/prefix1/IMG/volMax.png"));

    if((ui->sVolume->value()<50) &&(ui->sVolume->value() !=0) )
        ui->bMute->setIcon(QIcon(":/new/prefix1/IMG/volMid.png"));

    if(ui->sVolume->value()==0)
        ui->bMute->setIcon(QIcon(":/new/prefix1/IMG/volMuted.png"));
}

void MainWindow::on_bMute_clicked()
{
    if(!(player->isMuted()))
    {
        pVol =ui->sVolume->value();
        player->setMuted(true);
        ui->sVolume->setValue(0);
        changeVolIco();
    }
    else
    {
        player->setMuted(false);
        ui->sVolume->setValue(pVol);
        changeVolIco();
    }
}

void MainWindow::on_Timer_timeout()
{
    timer->start(5000);
}

void MainWindow::on_Timer_isActive()
{

}
