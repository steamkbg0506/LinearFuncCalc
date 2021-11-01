//#define __USE_DEBUG__

#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef __USE_DEBUG__
#include <QDebug>
#endif
#include <QMessageBox>
#include <stdlib.h>



typedef struct Fraction{
    int bunja;
    int bunmo;
    bool buho = 0; //0=양수, 1=음수
}Fraction;

typedef struct LinearFunc{
    int gaesu;
    int sangsoohang;
} LinearFunc;

Fraction addFraction(Fraction x, Fraction y);
Fraction subFraction(Fraction x, Fraction y);
Fraction multFraction(Fraction x, Fraction y);
Fraction divFraction(Fraction x, Fraction y);
bool compare(Fraction x, Fraction y);
void trimFraction(Fraction &x);

Fraction addFraction(Fraction x, Fraction y){
    Fraction z;
    z.bunmo = x.bunmo * y.bunmo;
    z.bunja = y.bunmo * x.bunja + x.bunmo * y.bunja;
    return z;
}
Fraction subFraction(Fraction x, Fraction y){
    Fraction z;
    z.bunmo = x.bunmo * y.bunmo;
    z.bunja = y.bunmo * x.bunja - x.bunmo * y.bunja;
    return z;
}
Fraction multFraction(Fraction x, Fraction y){
    Fraction z;
    z.bunmo = x.bunmo * y.bunmo;
    z.bunja = y.bunja * x.bunja;
    return z;
}
Fraction divFraction(Fraction x, Fraction y){
    Fraction z;
    z.bunmo = x.bunmo * y.bunja;
    z.bunja = y.bunmo * x.bunja;
    return z;
}
bool compare(Fraction x, Fraction y){
    if(y.bunmo * x.bunja - x.bunmo * y.bunja > 0)
        return 1;
    else
        return 0;
}
void trimFraction(Fraction &x){
    int down = x.bunja, up = x.bunmo, com;
    if(x.bunja > x.bunmo){
        down = x.bunmo;
        up = x.bunja;
    }

    for(int i=1; i<=down; i++)
        if((down%i)==0 && (up%i)==0)
            com=i;

    x.bunja/=com;
    x.bunmo/=com;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onIntCalcButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onIntCalcButtonClicked(){
    QString int_gs = ui->int_gaesu->text();
    int int_gaesu = 0;
    int_gaesu = int_gs.toInt();

    QString int_ss = ui->int_sangsoohang->text();
    int int_sangsoohang = 0;
    int_sangsoohang = int_ss.toInt();

    LinearFunc x_intercept;
    x_intercept.gaesu = int_gaesu;
    x_intercept.sangsoohang = int_sangsoohang;

    Fraction x_i;

    //X절편 시작

    if(x_intercept.gaesu == 0){
        QMessageBox::information(this, "Alert", "X의 계수는 0이 될 수 없습니다: 상수함수입니다.");
    } else if(x_intercept.gaesu > 0 && x_intercept.sangsoohang >= 0){
#ifdef __USE_DEBUG__
        QMessageBox::information(this, "Alert", "bm > 0, bj >= 0");
        qDebug() << "gaesu: " << x_intercept.gaesu << "\n";
        qDebug() << "sangsoohang: " << x_intercept.sangsoohang << "\n";
#endif
        x_i.buho = 1;
        x_i.bunmo = x_intercept.gaesu;
        x_i.bunja = x_intercept.sangsoohang;
        trimFraction(x_i);
    } else if(x_intercept.gaesu > 0 && x_intercept.sangsoohang <= 0){
#ifdef __USE_DEBUG__
        QMessageBox::information(this, "Alert", "bm > 0, bj <= 0");
        qDebug() << "gaesu: " << x_intercept.gaesu << "\n";
        qDebug() << "sangsoohang: " << x_intercept.sangsoohang << "\n";
#endif
        x_i.buho = 0;
        x_i.bunmo = x_intercept.gaesu;
        x_i.bunja = abs(x_intercept.sangsoohang);
        trimFraction(x_i);
    } else if(x_intercept.gaesu < 0 && x_intercept.sangsoohang >= 0){
#ifdef __USE_DEBUG__
        QMessageBox::information(this, "Alert", "bm < 0, bj >= 0");
        qDebug() << "gaesu: " << x_intercept.gaesu << "\n";
        qDebug() << "sangsoohang: " << x_intercept.sangsoohang << "\n";
#endif
        x_i.buho = 0;
        x_i.bunmo = abs(x_intercept.gaesu);
        x_i.bunja = x_intercept.sangsoohang;
        trimFraction(x_i);
    } else if(x_intercept.gaesu < 0 && x_intercept.sangsoohang <= 0){
#ifdef __USE_DEBUG__
        QMessageBox::information(this, "Alert", "bm < 0, bj <= 0");
        qDebug() << "gaesu: " << x_intercept.gaesu << "\n";
        qDebug() << "sangsoohang: " << x_intercept.sangsoohang << "\n";
#endif
        x_i.buho = 1;
        x_i.bunmo = abs(x_intercept.gaesu);
        x_i.bunja = abs(x_intercept.sangsoohang);
        trimFraction(x_i);
    } else {

        QMessageBox::information(this, "Alert", "X의 계수와 상수항이 유효하지 않은 숫자입니다.");

    }
#ifdef __USE_DEBUG__
    qDebug() << "bunmo: " << x_i.bunmo;
    qDebug() << "bunja: " << x_i.bunja;
    qDebug() << "buho(1 = 음수, 0 = 양수): " << x_i.buho;
#endif
    std::string label5 = "";
    if(x_i.buho == true){
        label5.append("- ");
    }
    if(x_i.bunmo == 1){
        label5.append(std::to_string(x_i.bunmo));
        ui->label_5->setText(QString::fromStdString(label5));
    } else{
        label5.append(std::to_string(x_i.bunja));
        label5.append("/");
        label5.append(std::to_string(x_i.bunmo));
        ui->label_5->setText(QString::fromStdString(label5));
    }
    //X절편 끝
    //Y절편
    ui->label_6->setText(QString::fromStdString(std::to_string(x_intercept.sangsoohang)));
    //Y절편 끝, 기울기 시작
    ui->label_7->setText(QString::fromStdString(std::to_string(x_intercept.gaesu)));
    //기울기 끝
}
