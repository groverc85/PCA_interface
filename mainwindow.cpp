#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtWidgets>
#include "qfiledialog.h"

extern string image_1, image_2, image_3;
QString fileName;
test Test;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadFromFileButton, SIGNAL(clicked()), SLOT(loadFromFile()));
    connect(ui->matchBreed,SIGNAL(clicked()),SLOT(matchBreed()));
    setWindowTitle(tr("Dog Breed Classification"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFromFile()
{
    ui->label->setText(tr("Select an image file"));
    fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                        tr("Images (*.png *.pgm *.jpg)"));
    QImage image;
    if (!image.load(fileName)) {
        ui->label->setText(tr("Selected file is not an image, please select another."));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));  
    qDebug() << "FileName:" << fileName;
}

void MainWindow::matchBreed()
{
    Test.test_image(fileName.toStdString());
//    ui->pos1->setText(tr("test"));
    ui->pos1->setText(QString::fromStdString(image_1));
    ui->pos2->setText(QString::fromStdString(image_2));
    ui->pos3->setText(QString::fromStdString(image_3));
}
