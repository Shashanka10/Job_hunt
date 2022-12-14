#include "providejob.h"
#include "ui_providejob.h"
#include "employer.h"
#include <QPixmap>
#include "global.h"
#include "connect.cpp"
#include<QMessageBox>

providejob::providejob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::providejob)
{
    ui->setupUi(this);
    QPixmap picpj(":/resources/image/pjj.png");
    ui->label_pjpf->setPixmap(picpj.scaled(80,80,Qt::KeepAspectRatio));

}

providejob::~providejob()
{
    delete ui;
}

void providejob::on_pushButton_post_clicked()
{
    QString jobname = ui->lineEdit_jn->text();
    QString address = ui->lineEdit_ja->text();
    QString qualification = ui->lineEdit_qf->text();
    QString salary = ui->lineEdit_salary->text();
    QString type = ui->lineEdit_jobt->text();
    QString description = ui->lineEdit_desc->text();
    class connect conn;
    if(jobname!="" && address != ""&& qualification !=""&& salary != "" && type != ""){

        conn.connopen();

        QSqlQuery post;
        post.prepare("INSERT INTO joblist (JobName,JobAddres,Qualification,Salary,JobType,Employer,Description) VALUES (:jobname,:jobaddress,:qualification,:salary,:type,:tempid,:description)");
        post.bindValue(":jobname",jobname);
        post.bindValue(":jobaddress",address);
        post.bindValue(":qualification",qualification);
        post.bindValue(":salary",salary);
        post.bindValue(":type",type);
        post.bindValue(":tempid",tempid);
        post.bindValue(":description",description);

        if(post.exec()){
        QMessageBox::information(this,tr("Job Posted"),tr("The job has been posted"));
            qDebug()<<("Posted");
        conn.connclose();
        hide();
        employer *emp = new employer(this);
        emp->show();
        }else{
            QMessageBox::critical(this,tr("error::"),post.lastError().text());
            qDebug()<<("Not posted");
        };
    }


}


void providejob::on_pushButton_cancelpjob_clicked()
{
    hide();
    employer *emp = new employer(this);
    emp->show();
}

