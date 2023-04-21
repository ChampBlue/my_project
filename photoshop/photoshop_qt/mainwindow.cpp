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

void MainWindow::on_pushButton_clicked()
{
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "웹캠이 켜진지 확인" << std::endl;
        return;
    }

    int width = 640;
    int height = 360;

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    cv::Mat frame;
    while (true) {
        if (cap.read(frame)) {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            QImage qImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            QPixmap qPixmap = QPixmap::fromImage(qImage);
            ui->label->setPixmap(qPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
            ui->label->show();
        }
        cv::waitKey(10);
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{
    cv::Mat frame2;
        if (cap.read(frame2)) {
            QString file_path = QFileDialog::getSaveFileName(this, "Save Image", ".", "Image Files (*.png *.jpg *.bmp)");
            if (!file_path.isEmpty()) {
                cv::Mat frame;
                cv::cvtColor(frame2, frame, cv::COLOR_BGR2RGB);
                cv::imwrite(file_path.toStdString(), frame);
                std::cout << "Saved image to " << file_path.toStdString() << std::endl;
            }
        }

    cap.release();
    ui->label->clear();
}
