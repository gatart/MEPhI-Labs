#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLabel>
#include "bigint.h"
#include "big_arithmetic_errors.h"
using namespace big_arithmetic;

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    bigint Ans;
    bigint negative();
    bigint operand(const QLabel *tmp);

private slots:
    void digits_numbers();
    void set_action();
    void sign_change();
    void clear_calc();
    void calculate();
    void ans();
    void del();


};

#endif // CALCULATOR_H
