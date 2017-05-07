#include "draglineedit.h"
#include <QDropEvent>
#include <QMimeData>

DragLineEdit::DragLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

DragLineEdit::DragLineEdit(const QString &s, QWidget *parent)
    : QLineEdit(s, parent)
{

}

void DragLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void DragLineEdit::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //往文本框中追加文件名
    QString path = urls[0].toLocalFile();
    this->setText(path);
}
