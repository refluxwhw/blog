#ifndef DRAGTEXTEDIT_H
#define DRAGTEXTEDIT_H

#include <QTextEdit>

class DragTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit DragTextEdit(QWidget *parent = 0);
    explicit DragTextEdit(const QString &text, QWidget *parent = 0);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);

signals:
    void dragFileIn(const QString& filePath);
};

#endif // DRAGTEXTEDIT_H
