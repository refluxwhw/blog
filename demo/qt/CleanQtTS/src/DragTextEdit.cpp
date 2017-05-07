#include "DragTextEdit.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

DragTextEdit::DragTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

DragTextEdit::DragTextEdit(const QString &text, QWidget *parent)
    : QTextEdit(text, parent)
{

}

void DragTextEdit::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
    {
        e->acceptProposedAction();
    }
}

void DragTextEdit::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        QList<QUrl> urls = e->mimeData()->urls();
        foreach (QUrl url, urls)
        {
            QString path = url.toLocalFile();
            emit dragFileIn(path);
        }
    }
}
