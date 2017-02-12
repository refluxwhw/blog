#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->btn_update, &QPushButton::clicked,
                     [this]{
        int x = ui->spinBox->value();
        int y = ui->spinBox_2->value();
        ui->widget_migong->reUpdate(x, y);
        this->resize(x * 10 + 30, y * 10 + 70);
    });

    QObject::connect(ui->btn_reslove, &QPushButton::clicked,
                     [this]{
        ui->widget_migong->reslove();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
