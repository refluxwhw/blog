/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pbtnShotAndMin;
    QPushButton *pbtnMin;
    QPushButton *pbtnShot;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(255, 41);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMaximumSize(QSize(257, 41));
        pbtnShotAndMin = new QPushButton(Widget);
        pbtnShotAndMin->setObjectName(QStringLiteral("pbtnShotAndMin"));
        pbtnShotAndMin->setGeometry(QRect(90, 9, 75, 23));
        pbtnMin = new QPushButton(Widget);
        pbtnMin->setObjectName(QStringLiteral("pbtnMin"));
        pbtnMin->setGeometry(QRect(171, 9, 75, 23));
        pbtnShot = new QPushButton(Widget);
        pbtnShot->setObjectName(QStringLiteral("pbtnShot"));
        pbtnShot->setGeometry(QRect(10, 10, 75, 23));
        QWidget::setTabOrder(pbtnShot, pbtnShotAndMin);
        QWidget::setTabOrder(pbtnShotAndMin, pbtnMin);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pbtnShotAndMin->setText(QApplication::translate("Widget", "\346\234\200\345\260\217\345\214\226\346\210\252\345\233\276", 0));
        pbtnMin->setText(QApplication::translate("Widget", "\346\234\200\345\260\217\345\214\226", 0));
        pbtnShot->setText(QApplication::translate("Widget", "\346\210\252   \345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
