#include "changepassjobseek.h"
#include "ui_changepassjobseek.h"
#include <QPixmap>
#include <QMessageBox>
#include <QIcon>
#include "dialog.h"
#include"mainwindow.h"
#include"global.h"


changepassjobseek::changepassjobseek(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepassjobseek)
{
    ui->setupUi(this);
    QPixmap cpwd2(":/resources/image/changepass.png");
    ui->label_cpwd_2->setPixmap(cpwd2.scaled(100,100,Qt::KeepAspectRatio));



    ui->lineEdit_newpwd->setPlaceholderText("New Password");
    ui->lineEdit_cfnewpwd->setPlaceholderText("Confirm New Password");

    QIcon pwd(":/resources/image/password.jpg");

    ui->lineEdit_newpwd->addAction(pwd,QLineEdit::LeadingPosition);
    ui->lineEdit_cfnewpwd->addAction(pwd,QLineEdit::LeadingPosition);



}

changepassjobseek::~changepassjobseek()
{
    delete ui;
}

void changepassjobseek::on_pushButton_setpass_clicked()
{

    QString np =ui->lineEdit_newpwd->text();
    QString cfnw =ui->lineEdit_cfnewpwd->text();

    if(np!="" && cfnw!="")
    {
        if(np==cfnw)
        {


            MainWindow conn;
            conn.connopen();
            QSqlQuery qrychange;
            qrychange.prepare("UPDATE user_account SET password='"+cfnw+"' WHERE username='"+tempid+"'");
            if(qrychange.exec())
            {
                QMessageBox::information(this,tr("Edit"),tr("Password Updated Successfully"));
                conn.connclose();
            }

            else
            {
                QMessageBox::critical(this,tr("ERROR!!!!"),qrychange.lastError().text());


            }
            conn.connclose();
            hide();
            Dialog *secdialog = new Dialog();
            secdialog->show();

        }else
        {
            QMessageBox::critical(this,"Mismatched","New Password and Confirm New Password didn't match. Please check it again");
        }
    }else
    {
        QMessageBox::critical(this,"Empty Field","Please fill the required fields!!");
    }
}


void changepassjobseek::on_pushButton_back_clicked()
{
    hide();
    Dialog *secdialog = new Dialog();
    secdialog->show();
}

