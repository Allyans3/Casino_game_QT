#include "wining.h"
#include "ui_wining.h"

wining::wining(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wining)
{
    ui->setupUi(this);
}

wining::~wining()
{
    delete ui;
}
