#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <random>
#include <mysql/mysql.h>

class DiceGame {
public:
    int player_money;

    DiceGame(int seed_money) : player_money(seed_money) {}
    void betting(int bet_money) {
        player_money -= bet_money;
    }
    void bet_result(const int& choice, const int& choice2, const int& result, const int& result2, const int& bet_money) {
        if (result == choice - 1 && result2 == choice2 - 1) {
            player_money += bet_money * 2;
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

int main()
{
    int seed_money;
    std::cout << "게임 머니 충전 : ";
    std::cin >> seed_money;
    std::cout << std::endl;

    DiceGame dice_game(seed_money);
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    if (!mysql_real_connect(con, "localhost", "root", "iot123", NULL, 3306, NULL, 0))
        finish_with_error(con);
    else
        std::cout << "mysql connect success" << std::endl;

    std::vector<cv::Mat*> p_mat;
    cv::Mat* dice_arr = new cv::Mat[6];

    for (int i = 0; i < 6; i++) {
        cv::Mat img = cv::imread("/home/mount/work_c/game/dice_game/" + std::to_string(i + 1) + ".png");
        if (img.empty()) {
            std::cerr << "이미지 불러오기 실패" << std::endl;
            return -1;
        }
        dice_arr[i] = img.clone();
        p_mat.push_back(dice_arr + i);
    }

    int choice = 0, choice2 = 0, bet_money = 0;
    std::cout << "첫 번 째 주사위 결과를 예상 값 : ";
    std::cin >> choice;
    std::cout << std::endl;

    std::cout << "두 번 째 주사위 결과 예상 값 : ";
    std::cin >> choice2;
    std::cout << std::endl;

    std::cout << "베팅 금액 입력 : ";
    std::cin >> bet_money;
    std::cout << std::endl;

    if (mysql_query (con, "USE Dicegame"))
        finish_with_error(con);

    if (mysql_query(con, "SELECT COUNT(*) FROM information_schema.TABLES WHERE (TABLE_SCHEMA = 'Dicegame') AND (TABLE_NAME = 'dice_game')"))
        finish_with_error(con);

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL)
        finish_with_error(con);

    MYSQL_ROW row = mysql_fetch_row(result);
    int table_exists = atoi(row[0]);
    mysql_free_result(result);

    if (!table_exists) {
        if (mysql_query (con, "CREATE TABLE dice_game (idx INT PRIMARY KEY AUTO_INCREMENT, money INT)"))
            finish_with_error(con);
    }

    dice_game.betting(bet_money);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, p_mat.size() - 1);

    int random_index = dis(gen);
    int random_index2 = dis(gen);
    cv::Mat random_dice = *(p_mat[random_index]);
    cv::Mat random_dice2 = *(p_mat[random_index2]);

    cv::imshow("첫 번 째 주사위 결과", random_dice);
    cv::imshow("두 번 째 주사위 결과", random_dice2);

    dice_game.bet_result(choice, choice2, random_index, random_index, bet_money);

    std::string query = "INSERT INTO dice_game (money) VALUES ("+ std::to_string (dice_game.player_money) + ")";
    if (mysql_query (con, query.c_str()))
        finish_with_error(con);

    if (mysql_query(con, "SELECT * FROM dice_game"))
        finish_with_error(con);

    cv::waitKey(0);

	/*if (mysql_query (con, "TRUNCATE TABLE dice_game"))
		finish_with_error(con);*/
		
    delete[] dice_arr;
    mysql_close(con);

    return 0;
}
