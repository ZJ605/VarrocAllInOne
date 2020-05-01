/********************************************************************************
** Form generated from reading UI file 'UI_CreateGeometryDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGEOMETRYDIALOG_H
#define UI_CREATEGEOMETRYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *y_coord;
    QTextEdit *txtEdit_y;
    QVBoxLayout *verticalLayout;
    QLabel *x_coord;
    QTextEdit *txtEdit_x;
    QDialogButtonBox *btnBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(375, 386);
        verticalLayout_3 = new QVBoxLayout(Dialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        y_coord = new QLabel(Dialog);
        y_coord->setObjectName(QString::fromUtf8("y_coord"));

        verticalLayout_2->addWidget(y_coord);

        txtEdit_y = new QTextEdit(Dialog);
        txtEdit_y->setObjectName(QString::fromUtf8("txtEdit_y"));

        verticalLayout_2->addWidget(txtEdit_y);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        x_coord = new QLabel(Dialog);
        x_coord->setObjectName(QString::fromUtf8("x_coord"));

        verticalLayout->addWidget(x_coord);

        txtEdit_x = new QTextEdit(Dialog);
        txtEdit_x->setObjectName(QString::fromUtf8("txtEdit_x"));

        verticalLayout->addWidget(txtEdit_x);


        verticalLayout_3->addLayout(verticalLayout);

        btnBox = new QDialogButtonBox(Dialog);
        btnBox->setObjectName(QString::fromUtf8("btnBox"));
        btnBox->setOrientation(Qt::Horizontal);
        btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(btnBox);

#ifndef QT_NO_SHORTCUT
        y_coord->setBuddy(txtEdit_y);
        x_coord->setBuddy(txtEdit_x);
#endif // QT_NO_SHORTCUT

        retranslateUi(Dialog);
        QObject::connect(btnBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(btnBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        y_coord->setText(QApplication::translate("Dialog", "y souradnice", nullptr));
        txtEdit_y->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">0 10 -10 -20 -30 0 </span></p></body></html>", nullptr));
        x_coord->setText(QApplication::translate("Dialog", "x souradnice", nullptr));
        txtEdit_x->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">0 10 20 30 40 50</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGEOMETRYDIALOG_H
