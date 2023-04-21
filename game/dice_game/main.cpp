#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <random>

int main()
{
    std::vector<cv::Mat*> p_mat;
    cv::Mat* dice_arr = new cv::Mat[6];

    for (int i = 0; i < 6; i++) {
        cv::Mat img = cv::imread("/home/mount/work_c/game/dice_game/dice/" + std::to_string(i + 1) + ".png");
        if (img.empty()) {
            std::cerr << "이미지 불러오기 실패" << std::endl;
            return -1;
        }
        dice_arr[i] = img.clone();
        p_mat.push_back(dice_arr + i);
    }

    int choice = 0;
    std::cout << "주사위 결과를 예측 하시오 : ";
    std::cin >> choice;
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, p_mat.size() - 1);
    int random_index = dis(gen);
    cv::Mat random_dice = *(p_mat[random_index]);

    cv::imshow("주사위 결과", random_dice);

    if (random_index == choice - 1)
        std::cout << "WIN" << std::endl;
    else
        std::cout << "LOSE" << std::endl;

    cv::waitKey(0);

    delete[] dice_arr;
    return 0;
}
