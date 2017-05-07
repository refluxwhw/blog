#ifndef DRAGLINEEDIT_H
#define DRAGLINEEDIT_H

#include <QLineEdit>

class DragLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit DragLineEdit(QWidget* parent=0);
    explicit DragLineEdit(const QString &s, QWidget* parent=0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // DRAGLINEEDIT_H
