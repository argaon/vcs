#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <time.h>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->StartButton->setEnabled(false);
}
int p_value = 0;

bool task_stop = 0;
bool chk_account;
bool chk_file;
bool chk_network;
bool chk_log;
bool chk_app;
bool chk_patch;

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::chk_start()
{
    ui->StartButton->setEnabled(p_max>0);
}
void MainWindow::reset()
{
    ui->cb_account->setChecked(false);
    ui->cb_filesystem->setChecked(false);
    ui->cb_network->setChecked(false);
    ui->cb_log->setChecked(false);
    ui->cb_app->setChecked(false);
    ui->cb_patch->setChecked(false);
    p_max = 0;
    ui->CheckButton->setEnabled(true);
    ui->cb_account->setEnabled(true);
    ui->cb_filesystem->setEnabled(true);
    ui->cb_network->setEnabled(true);
    ui->cb_log->setEnabled(true);
    ui->cb_app->setEnabled(true);
    ui->cb_patch->setEnabled(true);
    chk_start();
}
void MainWindow::on_CheckButton_clicked()
{

    if(p_max > 0)
    {
        ui->cb_account->setChecked(false);
        ui->cb_filesystem->setChecked(false);
        ui->cb_network->setChecked(false);
        ui->cb_log->setChecked(false);
        ui->cb_app->setChecked(false);
        ui->cb_patch->setChecked(false);
        p_max = 0;
    }
    else
    {
    ui->cb_account->setChecked(true);
    chk_account = true;
    ui->cb_filesystem->setChecked(true);
    chk_file = true;
    ui->cb_network->setChecked(true);
    chk_network = true;
    ui->cb_log->setChecked(true);
    chk_log = true;
    ui->cb_app->setChecked(true);
    chk_app = true;
    ui->cb_patch->setChecked(true);
    chk_patch = true;
    p_max = 44;
    }
    chk_start();

}

void MainWindow::on_StartButton_clicked()
{
    time_t now_time;
    struct tm *now_date;
    time(&now_time);
    now_date = localtime(&now_time);

    QProcess process;
    process.startDetached("rm", QStringList()<< "./log");
    ui->progressBar->setValue(0);
    task_stop = 0;
    ui->CheckButton->setEnabled(false);
    ui->cb_account->setEnabled(false);
    ui->cb_filesystem->setEnabled(false);
    ui->cb_network->setEnabled(false);
    ui->cb_log->setEnabled(false);
    ui->cb_app->setEnabled(false);
    ui->cb_patch->setEnabled(false);
    ui->StartButton->setEnabled(false);
    ui->progressBar->setMaximum(p_max);

    QFile file("./log");
    if(!file.open(QIODevice::ReadWrite| QIODevice::Append))
        QMessageBox::information(0,"file info",file.errorString());
    QTextStream stream(&file);

    stream << asctime(now_date);
    stream << "Start Vulnerability Check..."<<endl;
    if(chk_account)
    {
        stream <<"Start check account..."<<endl;
    }

    process.startDetached("/bin/sh", QStringList()<< "./debian_script/account/account_01.sh");
    stream << "account check finish!"<<endl;

    file.close();
    file.open(QIODevice::ReadWrite);
    ui->textBrowser->setText(file.readAll());
    file.close();
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    stream << "Vulnerability Check finish!"<<endl;
    file.close();
    file.open(QIODevice::ReadWrite);
    ui->textBrowser->setText(file.readAll());
    file.close();
    ui->progressBar->setValue(1);

    reset();
}

void MainWindow::on_StopButton_clicked()
{
    task_stop = 1;
    reset();
}

void MainWindow::on_InfoButton_clicked()
{
    QMessageBox::information(0,"Argaon's Info","Major : InformationSecurity & InformationSecurity S/W\nServed in Army : InformationSecurity Tech Sergeant 13-2nd\nBoB 7th Security Consulting");
}

void MainWindow::on_cb_account_clicked(bool checked)
{
    if(checked)
    {
        p_max+=8;
        chk_account = true;
    }
    if(checked == false)
    {
        p_max-=8;
        chk_account = false;
    }
    chk_start();
}

void MainWindow::on_cb_filesystem_clicked(bool checked)
{
    if(checked)
    {
        p_max+=16;
        chk_file = true;
    }
    if(checked == false)
    {
        p_max-=16;
        chk_file = false;
    }
    chk_start();
}

void MainWindow::on_cb_network_clicked(bool checked)
{
    if(checked)
    {
        p_max+=9;
        chk_network = true;
    }
    if(checked == false)
    {
        p_max-=9;
        chk_network = false;
    }
    chk_start();
}

void MainWindow::on_cb_log_clicked(bool checked)
{
    if(checked)
    {
        p_max+=2;
        chk_log = true;
    }
    if(checked == false)
    {
        p_max-=2;
        chk_log = false;
    }
    chk_start();
}

void MainWindow::on_cb_app_clicked(bool checked)
{
    if(checked)
    {
        p_max+=8;
        chk_app = true;
    }
    if(checked == false)
    {
        p_max-=8;
        chk_app = false;
    }
    chk_start();
}

void MainWindow::on_cb_patch_clicked(bool checked)
{
    if(checked)
    {
        p_max+=1;
        chk_patch = true;
    }
    if(checked == false)
    {
        p_max-=1;
        chk_patch = false;
    }
    chk_start();
}
