#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QRegExpValidator>
#include <QTime>
#include <QLayout>
#include <QMenuBar>
#include "windows.h"
#include <QMouseEvent>
#include <QTimer>
#include <QLCDNumber>
#include "wining.h"

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();
    QPoint mpos;

private slots:
    void on_roll_clicked();
    void on_slider_valueChanged(int value);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void on_roll_2_clicked();
    void colorlcd(int ar[]);
    void comb(int ar[]);
    void on_spin_clicked();    
    void makePlot();
    void on_placebet_clicked();

    void on_cashout_clicked();

private:
    Ui::game *ui;
    wining *window;
};

#endif // GAME_H
