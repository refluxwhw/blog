#include "Widget.h"
#include "ui_Widget.h"

#include <QFile>
#include <QDomDocument>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->textEdit, SIGNAL(dragFileIn(QString)),
            this, SLOT(onDragFileIn(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onDragFileIn(const QString &path)
{
    if (!path.endsWith(".ts", Qt::CaseInsensitive))
    {
        ui->textEdit->append(QString("%1 is not end with ts").arg(path));
        return;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->append(file.errorString());
        return;
    }
    QByteArray text = file.readAll();
    file.close();

    QDomDocument doc;
    if (!doc.setContent(text))
    {
        ui->textEdit->append("parser xml failed");
        return;
    }

    if (0 != doc.doctype().name().compare("TS", Qt::CaseInsensitive))
    {
        ui->textEdit->append(QString("not ts file"));
        return;
    }

    QDomElement ts = doc.firstChildElement("TS");
    if (ts.isNull())
    {
        ui->textEdit->append("root TS is not exists");
        return;
    }

    QDomElement context = ts.firstChildElement("context");
    while (!context.isNull())
    {
        QDomElement message = context.firstChildElement("message");
        while (!message.isNull())
        {
            message = message.nextSiblingElement("message");

            QDomElement last = message;
            QDomElement location = last.firstChildElement("location");
            if (location.isNull()) // not exists
            {
                context.removeChild(last);
            }
        }

        context = context.nextSiblingElement("context");
    }

    QFile out(path + "_clean");
    if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        ui->textEdit->append(out.errorString());
        return;
    }

    out.write(doc.toByteArray(2));
    out.close();

    ui->textEdit->append(QString("create file [%1] success").arg(out.fileName()));
}
