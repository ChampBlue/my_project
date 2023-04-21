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
    ui->label->clear();
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
    QString file_path = QFileDialog::getSaveFileName(this, "Save Image", ".", "Image Files (*.png *.jpg *.bmp)");
    if (!file_path.isEmpty()) {
        const QPixmap* pixmap = ui->label->pixmap();
        QPixmap saved_pixmap = QPixmap(*pixmap);
        saved_pixmap.save(file_path);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->label->clear();
    fileName = QFileDialog::getOpenFileName(this, tr("Opne Image"), "", tr("Image Files(*.png *.jpg *.bmp"));
    if (!fileName.isEmpty()) {
        load_img = cv::imread(fileName.toStdString());
        if(load_img.cols > 640 || load_img.rows > 360) {
            cv::Mat resized_image;
            cv::resize(load_img, resized_image, cv::Size(640, 360));
            load_img = resized_image;
        }
        cv::cvtColor(load_img, load_img, cv::COLOR_BGR2RGB);
        QImage qImage(load_img.data, load_img.cols, load_img.rows, load_img.step, QImage::Format_RGB888);
        QPixmap qPixmap = QPixmap::fromImage(qImage);

        ui->label->setPixmap(qPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->label->show();
    }

    if(cap.isOpened())
        cap.release();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label->clear();
    cv::Mat load_temp = load_img.clone();
    cv::Mat gray;
    cv::cvtColor(load_temp, gray, cv::COLOR_RGB2GRAY);

    QImage gray_image(gray.data, gray.cols, gray.rows, gray.step, QImage::Format_Grayscale8);

    ui->label->setPixmap(QPixmap::fromImage(gray_image));
    ui->label->setFixedSize(gray_image.width(), gray_image.height());
    ui->label->show();

    if(cap.isOpened())
        cap.release();
}

void MainWindow::on_pushButton_5_clicked()      //blur
{
    ui->label->clear();
    cv::Mat load_temp = load_img.clone();
    cv::blur(load_temp, blur_img, cv::Size(5, 5));

    QImage blur_image(blur_img.data, blur_img.cols, blur_img.rows, blur_img.step, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(blur_image));
    ui->label->setFixedSize(blur_image.width(), blur_image.height());
    ui->label->show();

    if(cap.isOpened())
        cap.release();
}

void MainWindow::on_pushButton_6_clicked()  //sharp
{
    ui->label->clear();
    cv::Mat load_temp = load_img.clone();
    cv::Mat blur_temp = blur_img.clone();
    cv::Mat gap_img = load_temp - blur_temp;
    cv::Mat sharp_img = load_temp + gap_img;

    QImage sharp_image(sharp_img.data, sharp_img.cols, sharp_img.rows, sharp_img.step, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(sharp_image));
    ui->label->setFixedSize(sharp_image.width(), sharp_image.height());
    ui->label->show();

    if(cap.isOpened())
        cap.release();

}
void MainWindow::on_pushButton_7_clicked()
{
        if (cap.read(frame)) {
            QString file_path = QFileDialog::getSaveFileName(this, "Save Image", ".", "Image Files (*.png *.jpg *.bmp)");
            if (!file_path.isEmpty()) {
                cv::imwrite(file_path.toStdString(), frame);
                std::cout << "Saved image to " << file_path.toStdString() << std::endl;
            }
        }

    cap.release();
    ui->label->clear();
}
