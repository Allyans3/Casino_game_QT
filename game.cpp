#include "game.h"
#include "ui_game.h"


game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    //MAIN
    connect(ui->dicegame,&QPushButton::clicked,this,[this]{ui->stackedWidget->setCurrentWidget(ui->Main);});
    connect(ui->slot,&QPushButton::clicked,this,[this]{ui->stackedWidget->setCurrentWidget(ui->Slot);});
    connect(ui->crash,&QPushButton::clicked,this,[this]{ui->stackedWidget->setCurrentWidget(ui->Crash);});
    connect(ui->deposit,&QPushButton::clicked,this,[this]{ui->stackedWidget->setCurrentWidget(ui->Deposit);});
    connect(ui->withdraw,&QPushButton::clicked,this,[this]{ui->stackedWidget->setCurrentWidget(ui->Widthraw);});
    this->setWindowFlags(Qt::FramelessWindowHint);

    //GAME
    QRegExp for_betline("^[0-9]*[.][0-9]+$");
    ui->betline->setValidator(new QRegExpValidator(for_betline, parent));
    connect(ui->Clear,&QPushButton::clicked,this,[this]{ui->betline->setText("0.01");});
    connect(ui->zero5,&QPushButton::clicked,this,[this]
    {
        QString cnt = ui->betline->text();
        float cntfloat = cnt.toFloat();
        cntfloat = cntfloat/2;
        if(cntfloat < 0.01)
            cntfloat = 0.01;
        cnt = QString::number(cntfloat);
        ui->betline->setText(cnt);
    });
    connect(ui->X2,&QPushButton::clicked,this,[this]
    {
        QString cnt = ui->betline->text();
        float cntfloat = cnt.toFloat();
        cntfloat = cntfloat*2;
        if(cntfloat > 9999)
            cntfloat = 9999;
        cnt = QString::number(cntfloat);
        ui->betline->setText(cnt);
    });
    connect(ui->min,&QPushButton::clicked,this,[this]{ui->betline->setText("0.01");});
    connect(ui->max,&QPushButton::clicked,this,[this]{ui->betline->setText("9999");});
    connect(ui->betline,&QLineEdit::textChanged,this,[this]{ui->profit->setText(QString::number(ui->betline->text().toFloat()*ui->multiplier->text().toFloat()));});
    connect(ui->editslider,&QLineEdit::textChanged,this,[this]{
            ui->slider->setValue(ui->editslider->text().toFloat()*100);
            if(ui->editslider->text().toFloat() >95)
                ui->editslider->setText(QString::number(95));
            else if(ui->editslider->text().toFloat() <0)
                ui->editslider->setText(QString::number(0.01));
    });

    //SLOT
    connect(ui->betlinne_2,&QLineEdit::textChanged,this,[this]{
        ui->total->clear();
        if(ui->but1->property("currentState").toInt() == 1)
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
        if(ui->but2->property("currentState").toInt() == 1)
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
        if(ui->but3->property("currentState").toInt() == 1)
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
    });
    connect(ui->but1,&QPushButton::clicked,this,[this]{
        QPushButton *button = static_cast<QPushButton*>(sender());
        int state = button->property("currentState").toInt();
        if(state == 0)
        {
            button->setStyleSheet("border-radius:11px;border: 2px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 1);
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
        }
        else
        {
            button->setStyleSheet("border-radius:11px;border: 0px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 0);
            ui->total->setText(QString::number(ui->total->text().toFloat()-ui->betlinne_2->text().toFloat()));
        }
    });
    connect(ui->but2,&QPushButton::clicked,this,[this]{
        QPushButton *button = static_cast<QPushButton*>(sender());
        int state = button->property("currentState").toInt();
        if(state == 0)
        {
            button->setStyleSheet("border-radius:11px;border: 2px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 1);
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
        }
        else
        {
            button->setStyleSheet("border-radius:11px;border: 0px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 0);
            ui->total->setText(QString::number(ui->total->text().toFloat()-ui->betlinne_2->text().toFloat()));
        }
    });
    connect(ui->but3,&QPushButton::clicked,this,[this]{
        QPushButton *button = static_cast<QPushButton*>(sender());
        int state = button->property("currentState").toInt();
        if(state == 0)
        {
            button->setStyleSheet("border-radius:11px;border: 2px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 1);
            ui->total->setText(QString::number(ui->betlinne_2->text().toFloat()+ui->total->text().toFloat()));
        }
        else
        {
            button->setStyleSheet("border-radius:11px;border: 0px solid yellow;background-color:rgb(0,199,77);color:#ffffff;");
            button->setProperty("currentState", 0);
            ui->total->setText(QString::number(ui->total->text().toFloat()-ui->betlinne_2->text().toFloat()));
        }
    });
    connect(ui->questbut,&QPushButton::clicked,this,[this]{
        window = new wining(this);
        window->show();
    });

    //CRASH
    game::makePlot();

    //DEPOSIT
    connect(ui->popolnit,&QPushButton::clicked,this,[this]{
        ui->balance->setText(QString::number(ui->balance->text().toFloat()+ui->suma->text().toFloat()));
        ui->suma->clear();
        ui->lineEdit->clear();
    });

    //WITHDRAW
    connect(ui->vivod,&QPushButton::clicked,this,[this]{
        ui->balance->setText(QString::number(ui->balance->text().toFloat()-ui->suma_2->text().toFloat()));
        ui->suma_2->clear();
        ui->lineEdit_2->clear();
    });
}


game::~game()
{
    delete ui;
}

void game::on_roll_clicked()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime())+qrand());
    if((ui->balance->text().toFloat()-ui->betline->text().toFloat()) < 0)
    {
        ui->stackedWidget->setCurrentWidget(ui->Deposit);
        return;
    }
    float num = qrand() %100;
    float num2 = qrand() %100;
    num = num+(num2/100);
    QEventLoop loop;
    QTimer::singleShot(150,&loop,SLOT(quit()));
    loop.exec();
    ui->lcdNumber->display(num);
    if(num>= ui->winchance->text().toFloat())
    {
        ui->balance->setText(QString::number(ui->balance->text().toFloat()-ui->betline->text().toFloat()));
    }
    else
    {
        ui->balance->setText(QString::number(ui->balance->text().toFloat()+ui->profit->text().toFloat()-ui->betline->text().toFloat()));
    }
}

void game::on_slider_valueChanged(int value)
{
    float val = value;
    val = val/100;
    ui->winchance->setText(QString::number(val));
    val = 95/val;
    ui->multiplier->setText(QString::number(val));
    ui->profit->setText(QString::number(ui->betline->text().toFloat()*ui->multiplier->text().toFloat()));
}

void game::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void game::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void game::mouseReleaseEvent(QMouseEvent *)
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}

void game::on_roll_2_clicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    int state = button->property("currentState").toInt();
    if(state == 0)
    {
        button->setStyleSheet("border-radius: 20px;background-color:rgb(0,199,77);color:white");
        button->setProperty("currentState", 1);
        for(;ui->editslider_2->text().toInt()>0;)
        {
            ui->editslider_2->setText(QString::number(ui->editslider_2->text().toInt()-1));
            ui->roll->click();
        }
        button->setStyleSheet("border-radius: 20px;background-color:red;color:white");
        button->setProperty("currentState", 0);
        ui->editslider_2->setText(QString::number(0));
    }
    else
    {
        button->setStyleSheet("border-radius: 20px;background-color:red;color:white");
        button->setProperty("currentState", 0);
        ui->editslider_2->setText(QString::number(0));
    }
}

void game::colorlcd(int ar[])
{
    QEventLoop loop;
    QLCDNumber *numb = ui->lcd_1;
    for(int b = 0;b<=8;b++)
    {
        if(b == 1)
            numb = ui->lcd_4;
        else if(b == 2)
            numb = ui->lcd_7;
        else if(b == 3)
            numb = ui->lcd_2;
        else if(b == 4)
            numb = ui->lcd_5;
        else if(b == 5)
            numb = ui->lcd_8;
        else if(b == 6)
            numb = ui->lcd_3;
        else if(b == 7)
            numb = ui->lcd_6;
        else if(b == 8)
            numb = ui->lcd_9;
        QTimer::singleShot(150,&loop,SLOT(quit()));
        loop.exec();
        numb->display(ar[b]);
        if(ar[b] == 3)
            numb->setStyleSheet("background-color:rgb(53,66,146)");
        else if(ar[b] == 4)
            numb->setStyleSheet("background-color:rgb(87,46,142)");
        else if(ar[b] == 5)
            numb->setStyleSheet("background-color:rgb(120,27,118)");
        else if(ar[b] == 6)
            numb->setStyleSheet("background-color:rgb(188,74,79)");
        else if(ar[b] == 7)
            numb->setStyleSheet("background-color:rgb(255,192,41)");
    }
}

void game::on_spin_clicked()
{
    ui->line->setStyleSheet("background-color: gray");
    ui->line_2->setStyleSheet("background-color: gray");
    ui->line_3->setStyleSheet("background-color: gray");
    if((ui->balance->text().toFloat()-ui->total->text().toFloat()) < 0)
    {
        ui->stackedWidget->setCurrentWidget(ui->Deposit);
        return;
    }
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime())+qrand());
    int ar[8];
    int cnt;
    for(int i=0;i<=8;i++)
    {
        cnt = 1+ qrand() %100;
        if(cnt >= 1 && cnt <=9)
            ar[i] = 7;
        else if(cnt >= 10 && cnt <=22)
            ar[i] = 6;
        else if(cnt >= 23 && cnt <=40)
            ar[i] = 5;
        else if(cnt >= 41 && cnt <=65)
            ar[i] = 4;
        else if(cnt >= 66 && cnt <=100)
            ar[i] = 3;
    }
    ui->balance->setText(QString::number(ui->balance->text().toFloat()-ui->total->text().toFloat()));
    colorlcd(ar);
    comb(ar);
}

void game::comb(int ar[])
{
    if(ui->but1->property("currentState").toInt() == 1)
    {
        if(ar[0]==3 && ar[3]==3 && ar[6]==3)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*2)));
        }
        else if(ar[0]==3 && ar[3]==3)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1.5)));
        }
        else if(ar[0]==3)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*0.5)));
        }
        else if(ar[0]==4 && ar[3]==4 && ar[6]==4)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*5)));
        }
        else if(ar[0]==4 && ar[3]==4)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*3)));
        }
        else if(ar[0]==4)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1)));
        }
        else if(ar[0]==5 && ar[3]==5 && ar[6]==5)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*6)));
        }
        else if(ar[0]==5 && ar[3]==5)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*4)));
        }
        else if(ar[0]==6 && ar[3]==6 && ar[6]==6)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*25)));
        }
        else if(ar[0]==7 && ar[3]==7 && ar[6]==7)
        {
            ui->line->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*50)));
        }
    }
    if(ui->but2->property("currentState").toInt() == 1)
    {
        if(ar[1]==3 && ar[4]==3 && ar[7]==3)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*2)));
        }
        else if(ar[1]==3 && ar[4]==3)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1.5)));
        }
        else if(ar[1]==3)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*0.5)));
        }
        else if(ar[1]==4 && ar[4]==4 && ar[7]==4)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*5)));
        }
        else if(ar[1]==4 && ar[4]==4)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*3)));
        }
        else if(ar[1]==4)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1)));
        }
        else if(ar[1]==5 && ar[4]==5 && ar[7]==5)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*6)));
        }
        else if(ar[1]==5 && ar[4]==5)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*4)));
        }
        else if(ar[1]==6 && ar[4]==6 && ar[7]==6)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*25)));
        }
        else if(ar[1]==7 && ar[4]==7 && ar[7]==7)
        {
            ui->line_2->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*50)));
        }
    }
    if(ui->but3->property("currentState").toInt() == 1)
    {
        if(ar[2]==3 && ar[5]==3 && ar[8]==3)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*2)));
        }
        else if(ar[2]==3 && ar[5]==3)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1.5)));
        }
        else if(ar[2]==3)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*0.5)));
        }
        else if(ar[2]==4 && ar[5]==4 && ar[8]==4)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*5)));
        }
        else if(ar[2]==4 && ar[5]==4)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*3)));
        }
        else if(ar[2]==4)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*1)));
        }
        else if(ar[2]==5 && ar[5]==5 && ar[8]==5)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*6)));
        }
        else if(ar[2]==5 && ar[5]==5)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*4)));
        }
        else if(ar[2]==6 && ar[5]==6 && ar[8]==6)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*25)));
        }
        else if(ar[2]==7 && ar[5]==7 && ar[8]==7)
        {
            ui->line_3->setStyleSheet("background-color:rgb(255,192,41)");
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_2->text().toFloat()*50)));
        }
    }
}

void game::makePlot()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(0,199,77));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setBrush(QBrush(QColor(36,255,118,70)));
    ui->customPlot->setBackground(QBrush(QColor(29,33,38)));
    QPen pen1;
    pen.setColor(QColor(37, 43, 49));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    ui->customPlot->yAxis->grid()->setPen(pen1);
    ui->customPlot->yAxis->setSubTickPen(pen1);
    ui->customPlot->yAxis->setTickPen(pen1);
    ui->customPlot->yAxis->setTickLabelColor(QColor(255,255,255));

    // axis configurations:
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->xAxis->grid()->setVisible(false);
    ui->customPlot->xAxis->setRange(1, 0.8,Qt::AlignLeft);
    ui->customPlot->yAxis->setRange(10, 10,Qt::AlignLeft);
}

void randforcrash(int &num)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime())+qrand());
    int col = 1+  qrand() %100;
    if(col >= 26 && col <= 100)
        num =  qrand() %200 +1;
    else if(col >= 12 && col <= 25)
        num = qrand() %500 +201;
    else if(col >= 7 && col <= 11)
        num = qrand() %500 +701;
    else if(col >= 3 && col <= 6)
        num = qrand() %600 +1201;
    else if(col >= 1 && col <= 2)
        num = qrand() %600 +1801;
}
void game::on_placebet_clicked()
{
    if((ui->balance->text().toFloat()-ui->betlinne_3->text().toFloat()) < 0)
    {
        ui->stackedWidget->setCurrentWidget(ui->Deposit);
        return;
    }
    QEventLoop loop;
    QPen pen1;
    pen1.setColor(QColor(0,199,77));
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen1);
    ui->customPlot->graph()->setBrush(QBrush(QColor(36,255,118,70)));
    ui->customPlot->xAxis->setRange(1, 0.8,Qt::AlignLeft);
    ui->customPlot->yAxis->setRange(10, 10,Qt::AlignLeft);
    ui->customPlot->replot();
    ui->xvalue->setStyleSheet("color:rgb(0,199,77);background-color:rgba(0,199,77,0);border:0px;");
    ui->placebet->setVisible(false);
    ui->cashout->setVisible(true);
    ui->balance->setText(QString::number(ui->balance->text().toFloat()-ui->betlinne_3->text().toFloat()));
    int num = 0,tim = 115;
    randforcrash(num);
    QVector<double> x(num+1), y(num+1);
    double yy = 9.9, xx = 100,tim1 = 1.5;
    for (int i=0; i< x.size(); i++)
    {
        QTimer::singleShot(tim,&loop,SLOT(quit()));
        loop.exec();
        yy += 0.1;
        y[i] = yy;
        x[i] = (xx++)/100;
        ui->customPlot->graph()->setData(x, y);
        if(ui->cashout->isHidden())
            tim = 5;
        else if(x[i] == tim1 && tim != 10)
        {
            tim = tim - 7;
            tim1 = tim1 + 0.5;
        }
        if((ui->customPlot->xAxis->range().size()+1) < x[i])
            ui->customPlot->xAxis->setRange(1, (x[i]-1),Qt::AlignLeft);
        if((ui->customPlot->yAxis->range().size()+10) < y[i])
            ui->customPlot->yAxis->setRange(10, (y[i]-10),Qt::AlignLeft);
        ui->customPlot->replot();
        ui->xvalue->setText(QString::number(x[i]));
        if(ui->autocashout->text().toDouble() == x[i])
        {
            ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_3->text().toFloat()*ui->autocashout->text().toFloat())));
            ui->cashout->setVisible(false);
        }
    }

    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setBrush(QBrush(QColor(255,0,0,70)));
    ui->customPlot->replot();

    ui->xvalue->setText("Crashed at "+QString::number(x[num])+"x");
    ui->xvalue->setStyleSheet("color:red;background-color:rgba(0,199,77,0);border:0px;");
    ui->placebet->setVisible(true);
    ui->placebet->setEnabled(false);
    QTimer::singleShot(1000,&loop,SLOT(quit()));
    loop.exec();
    ui->placebet->setEnabled(true);
}

void game::on_cashout_clicked()
{
    ui->balance->setText(QString::number(ui->balance->text().toFloat()+(ui->betlinne_3->text().toFloat()*ui->xvalue->text().toFloat())));
    ui->cashout->setVisible(false);
}
