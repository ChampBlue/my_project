#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <random>

class Card {
    protected:
        cv::Mat card;
        std::vector<cv::Mat*> card_vec;

    public:
        Card(){} 
};

class Space : public Card {
    public:
        Space()

};

int main()
{


    return 0;
}