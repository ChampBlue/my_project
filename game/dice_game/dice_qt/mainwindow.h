#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_betting_clicked();

    void on_select_clicked();

    void on_play_clicked();

    void on_pushButton_clicked();

    void on_database_clicked();

private:
    Ui::MainWindow *ui;
};

class DiceGame {
    int player_money;

 public:
    DiceGame(int seed_money) : player_money(seed_money) {}
    void betting(int bet_money) {
        player_money -= bet_money;
    }
    void bet_result(const int& choice, const int& choice2, const int& result, const int& result2, const int& bet_money) {
        if (result == choice - 1 && result2 == choice2 - 1) {
            player_money += bet_money * 1.9;
            std::cout << "WIN" << std::endl;
            std::cout << "현재 보유 금액 : " << player_money << std::endl;
        }
        else {
            std::cout << "LOSE" << std::endl;
            std::cout << "현재 보유 금액 : " << player_money << std::endl;
        }
    }
};

void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

#endif // MAINWINDOW_H
