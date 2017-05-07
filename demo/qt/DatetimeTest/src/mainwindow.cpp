#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Datetime Transform");

    connect(ui->now, SIGNAL(clicked(bool)), this, SLOT(onGetCurrentDatetime()));
    connect(ui->intToStr, SIGNAL(clicked(bool)), this, SLOT(onTimestampToDatetime()));
    connect(ui->strToInt, SIGNAL(clicked(bool)), this, SLOT(onDatatimeToTimestamp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGetCurrentDatetime()
{
    QDateTime t = QDateTime::currentDateTime();

    ui->datetime->setText(t.toString(ui->format->text()));

    QString str;
    if (ui->comboBox->currentIndex() == 0) {
        str = QString::number(t.toTime_t());
    } else {
        str = QString::number(t.toMSecsSinceEpoch());
    }

    ui->timestamp->setText(str);
}

void MainWindow::onDatatimeToTimestamp()
{
    QDateTime t = QDateTime::fromString(ui->datetime->text(), ui->format->text());
    if (t.isValid()) {
        QString str;
        if (ui->comboBox->currentIndex() == 0) {
            str = QString::number(t.toTime_t());
        } else {
            str = QString::number(t.toMSecsSinceEpoch());
        }

        ui->timestamp->setText(str);
    }
    else
    {
        qDebug() << "Time string and format not macth";
    }
}

void MainWindow::onTimestampToDatetime()
{
    QDateTime t;
    if (ui->comboBox->currentIndex() == 0) {
        t = QDateTime::fromTime_t(ui->timestamp->text().toUInt());
    } else {
        t = QDateTime::fromMSecsSinceEpoch(ui->timestamp->text().toULongLong());
    }

    ui->datetime->setText(t.toString(ui->format->text()));
}
