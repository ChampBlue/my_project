#include <opencv2/opencv.hpp>
#include <iostream>

//void image_info(cv::Mat& mat) {
//    std::cout << "영상 타입 : " << mat.type() << std::endl;
//    std::cout << std::endl;
//
//    std::cout << "영상 크기 : " << mat.size() << std::endl;
//    std::cout << std::endl;
//}

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "웹캠이 켜진지 확인" << std::endl;
        return -1;
    }

    int width = 640;
    int height = 360;

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    std::string filepath;
    std::cout << "저장할 파일 경로 설정 : " << std::endl;
    std::cin >> filepath;

    std::string file_path = filepath;
    std::cout << "space 바를 누르면 사진 찍힘" << std::endl;

    cv::namedWindow(("웹캠"));

    while (true) {
        cv::Mat frame;
        if(cap.read(frame)) {
            cv::imshow("웹캠", frame);
        }

        int key = cv::waitKey(1);
        if(key == ' ') {
            cv::Mat frame_image;
            cap.read(frame_image);
            cv::imwrite(file_path, frame_image);
            break;
        }
    }

    cv::destroyAllWindows();

    cv::Mat image = cv::imread(file_path);
    if (image.empty()) {
        std::cout << "image 파일을 불러 올 수 없음" <<std::endl;
        return -1;
    }

    cv::Mat cvt_gray;
    cv::cvtColor(image, cvt_gray, cv::COLOR_BGR2GRAY);

    cv::Mat blur_img;
    cv::blur(image, blur_img, cv::Size(5, 5));

    cv::Mat gap_img = image - blur_img;
    cv::Mat sharp_img = image + gap_img;

    //image_info(image);

//    cv::imshow("1", image);
//    cv::imshow("2", blur_img);
//    cv::imshow("3", sharp_img);
//    cv::imshow("4", cvt_gray);
//
//    cv::waitKey(0);

    return 0;
}
