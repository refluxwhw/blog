#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "md5.h"

#include <QFileDialog>
#include <QFile>

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

int file_md5(const char *path, char md5[], int size)
{
    if (NULL == md5 || size < 32)
    {
        return -1;
    }

    FILE *fp = fopen (path, "rb");
    if (fp == NULL) {
        return -1;
    }

    MD5_CTX mdContext;
    MD5Init(&mdContext);
    int bytes;
    unsigned char data[1024];
    while ((bytes = fread (data, 1, 1024, fp)) != 0)
    {
        MD5Update(&mdContext, data, bytes);
    }
    MD5Final (&mdContext);
    fclose (fp);

    for(int i=0; i<16; i++)
    {
        sprintf(&md5[i*2], "%02x", mdContext.digest[i]);
    }

    return 0;
}

QString getFileMD5(const QString &path)
{
    char buf[36] = {};
    if (0 != file_md5(path.toLocal8Bit().data(), buf, 36))
    {
        return "";
    }

    return QString(buf);
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "", "./");
    if (path.isEmpty())
    {
        return;
    }

    ui->lineEdit->setText(path);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = ui->lineEdit->text();
    QFile file(path);
    if (!file.exists())
    {
        return;
    }

    QString md5 = getFileMD5(path);
    ui->textEdit->setText("file: " + path + "\nMD5 : " + md5);
}
