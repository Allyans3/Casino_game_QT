#ifndef WINING_H
#define WINING_H

#include <QDialog>

namespace Ui {
class wining;
}

class wining : public QDialog
{
    Q_OBJECT

public:
    explicit wining(QWidget *parent = 0);
    ~wining();

private:
    Ui::wining *ui;
};

#endif // WINING_H
