#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_betting_clicked()
{

}

void MainWindow::on_select_clicked()
{

}

void MainWindow::on_play_clicked()
{

}

void MainWindow::on_start_clicked()
{
    int seed_money;

    ui->input_label->
}

void MainWindow::on_database_clicked()
{

}
