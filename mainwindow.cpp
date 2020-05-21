#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->redSlider->setStyleSheet("QSlider::handle:horizontal {background-color: red;}");
    ui->greenSlider->setStyleSheet("QSlider::handle:horizontal {background-color: green;}");
    ui->blueSlider->setStyleSheet("QSlider::handle:horizontal {background-color: blue;}");

    connect(ui->redSlider, SIGNAL(valueChanged(int)), ui->screen, SLOT(updateRed(int)));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), ui->screen, SLOT(updateGreen(int)));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), ui->screen, SLOT(updateBlue(int)));
    connect(ui->saveButton, SIGNAL(clicked(bool)), ui->screen, SLOT(save()));
    connect(ui->loadButton, SIGNAL(clicked(bool)), ui->screen, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
