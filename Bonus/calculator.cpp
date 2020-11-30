#include "calculator.h"
#include "ui_calculator.h"
#include <QMessageBox>
#include <sstream> // for fixing

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    Ans = bigint(0l);

    connect(ui->zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->three, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->seven, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->eight, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->changeSign, SIGNAL(clicked()), this, SLOT(sign_change()));

    connect(ui->LShift, SIGNAL(clicked()), this, SLOT(set_action()));
    connect(ui->RShift, SIGNAL(clicked()), this, SLOT(set_action()));
    connect(ui->Plus, SIGNAL(clicked()), this, SLOT(set_action()));
    connect(ui->Minus, SIGNAL(clicked()), this, SLOT(set_action()));

    connect(ui->equal, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->Answer, SIGNAL(clicked()), this, SLOT(ans()));
    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear_calc()));
    connect(ui->Del, SIGNAL(clicked()), this, SLOT(del()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digits_numbers(){
    try {
        QPushButton *button = static_cast<QPushButton *>(sender());
        QString number = ui->workspace->text();
        if (number == "Ans"){
            return;
        }
        if (number == "0"){
            number = "";
        }
        number = number + button->text();
        ui->workspace->setText(number);
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }
}

void Calculator::sign_change(){
    try {
        QString number = ui->workspace->text();
        if (number == "0"){
            return;
        }
        if (number[0] == '-'){
            number.replace(0, 1, "");
        }else{
            number = "-" + ui->workspace->text();
        }
        ui->workspace->setText(number);
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }

}

void Calculator::set_action(){
    try {
        QPushButton *button = static_cast<QPushButton *>(sender());
        if (ui->last->text() == ""){
            ui->last->setText(ui->workspace->text());
            ui->workspace->setText("0");
        }
        ui->action->setText(button->text());
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }
}

bigint Calculator::negative(){
    QString tmp = Ans.to_string();
    if (tmp[0] == '-'){
        tmp.replace(0, 1, "");
    }else{
        tmp = "-" + tmp;
    }
    return bigint(std::stol(tmp.toStdString().c_str()));
}

bigint Calculator::operand(const QLabel *tmp){
    if (tmp->text() == "Ans"){
        return Ans;
    }else if (tmp->text() == "-Ans"){
        return negative();
    }
    return bigint (std::stol(tmp->text().toStdString().c_str()));
}

void Calculator::calculate(){
    if (ui->last->text() == ""){ //no first operand
        Ans = operand(ui->workspace);
        ui->workspace->setText(Ans.to_string());
        return;
    }

    try{
        bigint A = operand(ui->last);;
        bigint B = operand(ui->workspace);;

        /*bigint A = "134";
        bigint B = "21";
        A = A - B;
        QString kek = static_cast<QString>(A.to_string());
        QMessageBox::warning(this, "Exception", kek);
        */
    //-------------------------------------
    /*{
        QString kek = static_cast<QString>(A.to_string());
        QMessageBox::warning(this, "Exception", kek);
        kek = static_cast<QString>(B.to_string());
        QMessageBox::warning(this, "Exception", kek);

        kek = "";
        for (size_t i = 0; i < strlen(A.to_string()); ++i){
            kek = kek +" " + QString::number(static_cast<int>(A.to_string()[i]));
        }
        QMessageBox::warning(this, "Exception", kek);

        kek = "";
        for (size_t i = 0; i < strlen(B.to_string()); ++i){
            kek = kek +" " + QString::number(static_cast<int>(B.to_string()[i]));
        }
        QMessageBox::warning(this, "Exception", kek);

    }*/
    //-------------------------------------------

    QString action = ui->action->text();
    if (action == "+"){
        QMessageBox::warning(this, "Exception", "тут");
        A = A + B;
        QString kek = static_cast<QString>(A.to_string());
        QMessageBox::warning(this, "Exception", kek);
    }else if (action == "-"){
        QMessageBox::warning(this, "Exception", "тут");
        A = A - B;
        QString kek = static_cast<QString>(A.to_string());
        QMessageBox::warning(this, "Exception", kek);
    }else{
        long long second = ui->workspace->text().toLongLong();
        if (second >= 2147483647l){
            QMessageBox::warning(this, "Warning!", "The second operand must be positive and less than 2147483647.");
            ui->workspace->setText("0");
            return;
        }
        if (action == "<<"){
            A = A << static_cast<int>(second);
        }else if (action == ">>"){
            A = A >> static_cast<int>(second);
        }
    }
    //-------------------------------------
    /*{
        QString kek = static_cast<QString>(A.to_string());
        QMessageBox::warning(this, "Exception", kek);
    }
    {
        QString kek = static_cast<QString>(Ans.to_string());
        QMessageBox::warning(this, "Exception", kek);
    }*/
    //-------------------------------------------

    clear_calc();
    Ans = bigint(A);
    ui->workspace->setText(Ans.to_string());

    }catch(incorrect_number_exception){
        QMessageBox::warning(this, "Warning!", "The second operand must be positive and less than 2147483647.");
        ui->workspace->setText("0");
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }
}

void Calculator::ans(){
    try {
        QString number = ui->workspace->text();
        if (number == "0"){
            ui->workspace->setText("Ans");
        }
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }
}

void Calculator::clear_calc(){
    ui->last->setText("");
    ui->action->setText("");
    ui->workspace->setText("0");
    Ans = bigint(0l);
}

void Calculator::del(){
    try {
        QString number = ui->workspace->text();
        if (number == "Ans" || number == "-Ans" || number.length() == 1 || (number[0] == '-' && number.length() == 2)){
            ui->workspace->setText("0");
        }else{
            number.replace(number.length() - 1, 1, "");
            ui->workspace->setText(number);
        }
    }catch(bad_alloc_exception){
        QMessageBox::critical(this, "Bad allocation!", "There is not enough memory for Calculator work.");
        qApp->quit();
    }catch(...){
        QMessageBox::critical(this, "Unknown error!", "An unknown error occurred. The calculator will be closed");
        qApp->quit();
    }
}
