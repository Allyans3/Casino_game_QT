#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("sql7.freemysqlhosting.net:3306");
//    db.setDatabaseName("sql7245083");
//    db.setUserName("sql7245083");
//    db.setPassword("MHxPrJIAFZ");
//    if(!db.open())
//        qDebug() << db.lastError().text();
//    else
//        qDebug() << "Success!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->pass->text();
    game window;
    if((login == "admin" && password == "admin") || (login == "Allyans3" && password == "admin"))
    {
        hide();
        window.setModal(true);
        window.exec();
    }
    else
        QMessageBox::information(this,"Authorization","Incorrect date");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}
