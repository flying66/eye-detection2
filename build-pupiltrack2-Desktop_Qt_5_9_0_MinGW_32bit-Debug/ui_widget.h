/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1280, 708);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 70, 171, 41));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(490, 70, 141, 41));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 150, 561, 481));
        label->setFrameShape(QFrame::Box);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(680, 150, 211, 151));
        label_2->setFrameShape(QFrame::Box);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(980, 150, 211, 151));
        label_3->setFrameShape(QFrame::Box);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(680, 340, 211, 161));
        label_4->setFrameShape(QFrame::Box);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(980, 340, 211, 161));
        label_5->setFrameShape(QFrame::Box);
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 70, 131, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "                               \350\276\223\345\207\272\350\247\206\351\242\221", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "          \345\267\246\347\234\274\347\235\233", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "          \345\217\263\347\234\274\347\235\233", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "      \345\267\246\347\234\274\347\235\233\344\272\214\345\200\274\345\214\226\345\244\204\347\220\206", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "    \345\217\263\347\234\274\347\235\233\344\272\214\345\200\274\345\214\226\345\244\204\347\220\206", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\234\254\345\234\260\345\233\276\347\211\207", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
