#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

#include <QPixmap>
#include "global.h"
#include <global.cpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Code for database connection
    if (connopen())
    {
    //ui->label_suces->setText("Successful ");
    connclose();}
    else{
        //ui->label_suces->setText("Failed");
        connclose();
    }
    //Code for inserting and setting size of icons
    QPixmap pix(":/resources/image/jobi.png");
    ui->label_pic->setPixmap(pix.scaled(250,250,Qt::KeepAspectRatio));
    QPixmap pic_1(":/resources/image/pp.png");
    ui->label_2->setPixmap(pic_1.scaled(25,25,Qt::KeepAspectRatio));
    QPixmap pic_2(":/resources/image/pass.jpg");
    ui->label_3->setPixmap(pic_2.scaled(20,20,Qt::KeepAspectRatio));


}

MainWindow::~MainWindow()
{
    delete ui;
}//Destructor of the page

//When login clicked
void MainWindow::on_pushButton_login_clicked()
{

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();//Taking user input to the variable

        if(!connopen())
        {
            qDebug()<<"Failed to  Open Database";
            return;//Checking if the connection is successful.

        }
    connopen();//opening the connection
    QSqlQuery qry("SELECT type FROM user_account where username='"+username+"' and password='"+password+"'");
    //preparing the query
    tempid = username;//storing the id in global variable
    if(qry.exec())//executing the query
    {
        int count=0;
        while(qry.next()){
            count++;//counting the total no of results in query
        }

        qry.previous();
if(count==1) //if only one result is found
{
    //ui->label_suces->setText(qry.value(0).toString());
        if(qry.value(0)=="1"){//checking for jobseeker
    connclose();
     hide();
     secdialog = new Dialog(this);
     secdialog->show();//opening the menu page of jobseeker
   }else if(qry.value(0)=="2"){//checking for employer
         connclose();
         hide();
         emp =new employer(this);
         emp->show();//opening the menu page of employer
    }
}

if (count<1)
{
    QMessageBox::information(this,"Login","Username or Password is incorrect");
    //if the id or password does not match

    connclose();
    }
    }

}


void MainWindow::on_pushButton_signup_clicked()
{
    hide();
    thirddialog = new signup_Dialog(this);
    thirddialog->show();//opening sign up page of Jobseeker
}


void MainWindow::on_pushButton_signupemp_clicked()
{
    hide();
    siemp = new signup_emp(this);
    siemp->show();//opening sign up page of Employer
}

//Function to hide and unhide password
void MainWindow::on_checkBox_login_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:

        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
        break;
    case 2:

        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
        break;
    }
}

