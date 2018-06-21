#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QDialog>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bPlay_clicked();

    void on_bPause_clicked();

    void on_sVolume_sliderMoved(int position);

    void on_sProgres_sliderMoved(int position);

    void on_Position_change(qint64 position);

    void on_Duration_change(qint64 position);

    void on_bOpenFile_clicked();

    void on_bMute_clicked();

    void on_Timer_timeout();

    void on_Timer_isActive();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QFileDialog* file;
    QTimer* timer;
    int pVol;

    void connectSlots();
    void changeVolIco();
};

#endif // MAINWINDOW_H
