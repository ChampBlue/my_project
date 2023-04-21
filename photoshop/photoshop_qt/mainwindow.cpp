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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Opne Image"), "", tr("Image Files(*.png *.jpg *.bmp"));
    if (!fileName.isEmpty()) {
        load_img = cv::imread(fileName.toStdString());
        if(load_img.cols > 640 || load_img.rows > 360) {
            cv::Mat resized_image;
            cv::resize(load_img, resized_image, cv::Size(640, 360));
            load_img = resized_image;
        }
        QImage qImage(load_img.data, load_img.cols, load_img.rows, load_img.step, QImage::Format_RGB888);
        QPixmap qPixmap = QPixmap::fromImage(qImage);

        ui->label->setPixmap(qPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->label->show();
    }
}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->clear();
    cv::Mat blur_img;
    cv::blur(load_img, blur_img, cv::Size(5, 5));

    QImage blur_image(blur_img.data, blur_img.cols, blur_img.rows, blur_img.step, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(blur_image));
    ui->label->setFixedSize(blur_image.width(), blur_image.height());
    ui->label->show();
}

void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{
        if (cap.read(frame)) {
            QString file_path = QFileDialog::getSaveFileName(this, "Save Image", ".", "Image Files (*.png *.jpg *.bmp)");
            if (!file_path.isEmpty()) {
                cv::Mat frame2;
                cv::cvtColor(frame, frame2, cv::COLOR_BGR2RGB);
                cv::imwrite(file_path.toStdString(), frame2);
                std::cout << "Saved image to " << file_path.toStdString() << std::endl;
            }
        }

    cap.release();
    ui->label->clear();
}
