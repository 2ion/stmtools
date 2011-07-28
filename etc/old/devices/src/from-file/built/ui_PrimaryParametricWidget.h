/********************************************************************************
** Form generated from reading UI file 'PrimaryParametricWidget.ui'
**
** Created: Wed Apr 6 13:04:29 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIMARYPARAMETRICWIDGET_H
#define UI_PRIMARYPARAMETRICWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrimaryParametricWidgetClass
{
public:

    void setupUi(QWidget *PrimaryParametricWidgetClass)
    {
        if (PrimaryParametricWidgetClass->objectName().isEmpty())
            PrimaryParametricWidgetClass->setObjectName(QString::fromUtf8("PrimaryParametricWidgetClass"));
        PrimaryParametricWidgetClass->resize(400, 300);

        retranslateUi(PrimaryParametricWidgetClass);

        QMetaObject::connectSlotsByName(PrimaryParametricWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *PrimaryParametricWidgetClass)
    {
        PrimaryParametricWidgetClass->setWindowTitle(QApplication::translate("PrimaryParametricWidgetClass", "PrimaryParametricWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrimaryParametricWidgetClass: public Ui_PrimaryParametricWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIMARYPARAMETRICWIDGET_H
