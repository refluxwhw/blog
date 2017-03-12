#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_score = 0;
    onScore(0);

    connect(ui->widget, SIGNAL(sigEraserLine(int)),
            this, SLOT(onScore(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    Tetris* t = ui->widget;
    int k = e->key();
    switch (e->key())
    {
        case Qt::Key_A: //
        case Qt::Key_Left:
            t->onLeftClicked();
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            t->onRightClicked();
            break;
        case Qt::Key_J:
            t->onRotateLeft();
            break;
        case Qt::Key_K:
            t->onRotateRight();
            break;
        case Qt::Key_S:
            t->onDownPresse();
            break;
        default:
            e->ignore();
            return;
    }
    e->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    Tetris* t = ui->widget;
    switch (e->key())
    {
        case Qt::Key_S:
            t->onDownRelease();
            break;
        default:
            e->ignore();
            return;
    }
    e->accept();
}

void MainWindow::onScore(int line)
{
    switch (line) {
        case 1:
            m_score += 100;
            break;
        case 2:
            m_score += 400;
            break;
        case 3:
            m_score += 800;
            break;
        case 4:
            m_score += 1600;
            break;
        default:
            break;
    }

    ui->label_score->setText(QString("Score: %1").arg(m_score));
}

