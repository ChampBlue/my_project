#include <iostream>
#include <opencv2/opencv.hpp>
#include <mysql.h>
#include <torch/torch.h>
#include <random>
#include <vector>
#include <string>

int main()
{
    MYSQL *con;
    con = mysql_init(NULL);

    if (!mysql_real_connect(con, "localhost", "root", "pi", "database name", 3306, NULL, 0)) {
        std::cerr << "Failed connect db" <<std::endl;
        return -1;
    }

    cv::VideoCapture cam(0);
    torch::jit::script::Module module;
    std::string labelsFile = "coco.names"; // coco.names 파일 경로
    std::vector<std::string> labels;

    // coco.names 파일 읽기
    std::ifstream file(labelsFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            labels.push_back(line);
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open file: " << labelsFile << std::endl;
        return -1;
    }

    while (!cam.isOpened()) {
        cv::Mat frame;
        bool ret = cam.read(frame);

        if (!ret) {
            std::cerr << "Failed to read frame" << std::endl;
            break;
        }

        try {
            module = torch::jit::load("yolo5s.pt");
        }
        catch (const c10::Error& e) {
            std::cerr << "Error loading model: " << e.msg() << std::endl;
            return -1;
        }

        // 이미지 전처리
        cv::resize(frame, frame, cv::Size(640, 640));
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        cv::Mat imgFloat;
        frame.convertTo(imgFloat, CV_32FC3, 1.0 / 255.0);
        torch::Tensor tensorImage = torch::from_blob(imgFloat.data,
            {1, imgFloat.rows, imgFloat.cols, 3}).permute({0, 3, 1, 2});

        // 모델 입력
        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(tensorImage);

        // 모델 실행
        torch::jit::IValue results = module.forward(inputs);

        // 결과 추출
        torch::Tensor detections = results.toTensor();

        // 결과 처리
        for (int i = 0; i < detections.size(0); i++) {
            torch::Tensor detection = detections[i];

            int x1 = static_cast<int>(detection[0].item<float>());
            int y1 = static_cast<int>(detection[1].item<float>());
            int x2 = static_cast<int>(detection[2].item<float>());
            int y2 = static_cast<int>(detection[3].item<float>());
            int labelIndex = static_cast<int>(detection[4].item<float>());

            std::string label;
            if (labelIndex == 25) {
                label = labels[labelIndex];
            }
            else {
                label = "Unknown";
            }

            float conf = detection[5].item<float>();

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(0, 255);

            std::vector<int> color = {distribution(gen), distribution(gen), distribution(gen)};
            cv::Scalar rectColor(color[0], color[1], color[2]);

            cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), rectColor, 2);

            std::string confLabel = label + " " + std::to_string(conf);
            cv::putText(frame, confLabel, cv::Point(x1, y1 - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, rectColor, 2);

            cv::imshow("frame", frame);

            if (cv::waitKey(1) == 27) {
                break;
            }
        }
    }

    cam.release();
    mysql_close(con);
    cv::destroyAllWindows();

    return 0;
}
