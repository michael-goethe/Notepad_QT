#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonbox()));
//    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttonbox()));

}

void Dialog::buttonbox(){
   // if (ui->pushButton->clicked())
    emit textsent(ui->lineEdit->text());

}


Dialog::~Dialog()
{
    delete ui;
}
