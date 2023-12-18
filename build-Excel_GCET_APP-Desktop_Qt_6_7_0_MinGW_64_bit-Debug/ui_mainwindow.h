/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_select_file;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *button_search_files;
    QPushButton *exportID;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label_loading_booms;
    QSpacerItem *horizontalSpacer_23;
    QProgressBar *progressBar_proccess_booms;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_time_proccess_booms;
    QSpacerItem *horizontalSpacer_24;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_select_file_drms;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_drms;
    QPushButton *button_search_files_drms;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_loading_drms;
    QSpacerItem *horizontalSpacer_10;
    QProgressBar *progressBar_proccess_drms;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_time_proccess_drms;
    QSpacerItem *horizontalSpacer_18;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_files_selected;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *textEdit_names_files;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_clean;
    QPushButton *button_export;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_loading_export;
    QSpacerItem *horizontalSpacer_6;
    QProgressBar *progressBar_proccess_export;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_time_proccess_export;
    QSpacerItem *horizontalSpacer_15;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(609, 618);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(500, 400));
        MainWindow->setMaximumSize(QSize(800, 700));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: black;\n"
" \n"
"color: rgb(255, 255, 255);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_select_file = new QLabel(centralwidget);
        label_select_file->setObjectName("label_select_file");
        QFont font;
        font.setPointSize(12);
        label_select_file->setFont(font);

        horizontalLayout->addWidget(label_select_file);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color : rgb(0, 0, 0)"));

        horizontalLayout_3->addWidget(lineEdit);

        button_search_files = new QPushButton(centralwidget);
        button_search_files->setObjectName("button_search_files");
        button_search_files->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 199, 96);"));

        horizontalLayout_3->addWidget(button_search_files);


        horizontalLayout_14->addLayout(horizontalLayout_3);

        exportID = new QPushButton(centralwidget);
        exportID->setObjectName("exportID");
        exportID->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 199, 96);"));

        horizontalLayout_14->addWidget(exportID);

        horizontalLayout_14->setStretch(0, 7);

        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_22);

        label_loading_booms = new QLabel(centralwidget);
        label_loading_booms->setObjectName("label_loading_booms");
        label_loading_booms->setFont(font);

        horizontalLayout_19->addWidget(label_loading_booms);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_23);


        verticalLayout->addLayout(horizontalLayout_19);

        progressBar_proccess_booms = new QProgressBar(centralwidget);
        progressBar_proccess_booms->setObjectName("progressBar_proccess_booms");
        progressBar_proccess_booms->setMinimumSize(QSize(0, 20));
        progressBar_proccess_booms->setMaximumSize(QSize(16777215, 20));
        progressBar_proccess_booms->setValue(0);

        verticalLayout->addWidget(progressBar_proccess_booms);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_20);

        label_time_proccess_booms = new QLabel(centralwidget);
        label_time_proccess_booms->setObjectName("label_time_proccess_booms");

        horizontalLayout_18->addWidget(label_time_proccess_booms);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_24);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);

        label_select_file_drms = new QLabel(centralwidget);
        label_select_file_drms->setObjectName("label_select_file_drms");
        label_select_file_drms->setFont(font);

        horizontalLayout_8->addWidget(label_select_file_drms);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        lineEdit_drms = new QLineEdit(centralwidget);
        lineEdit_drms->setObjectName("lineEdit_drms");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_drms->sizePolicy().hasHeightForWidth());
        lineEdit_drms->setSizePolicy(sizePolicy1);
        lineEdit_drms->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color : rgb(0, 0, 0)"));

        horizontalLayout_2->addWidget(lineEdit_drms);

        button_search_files_drms = new QPushButton(centralwidget);
        button_search_files_drms->setObjectName("button_search_files_drms");
        button_search_files_drms->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 199, 96);"));

        horizontalLayout_2->addWidget(button_search_files_drms);


        horizontalLayout_17->addLayout(horizontalLayout_2);

        horizontalLayout_17->setStretch(0, 7);

        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        label_loading_drms = new QLabel(centralwidget);
        label_loading_drms->setObjectName("label_loading_drms");
        label_loading_drms->setFont(font);

        horizontalLayout_9->addWidget(label_loading_drms);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_9);

        progressBar_proccess_drms = new QProgressBar(centralwidget);
        progressBar_proccess_drms->setObjectName("progressBar_proccess_drms");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(progressBar_proccess_drms->sizePolicy().hasHeightForWidth());
        progressBar_proccess_drms->setSizePolicy(sizePolicy2);
        progressBar_proccess_drms->setMinimumSize(QSize(598, 20));
        progressBar_proccess_drms->setMaximumSize(QSize(16777215, 20));
        progressBar_proccess_drms->setValue(0);
        progressBar_proccess_drms->setTextVisible(true);
        progressBar_proccess_drms->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar_proccess_drms);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_19);

        label_time_proccess_drms = new QLabel(centralwidget);
        label_time_proccess_drms->setObjectName("label_time_proccess_drms");

        horizontalLayout_15->addWidget(label_time_proccess_drms);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_18);


        verticalLayout->addLayout(horizontalLayout_15);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_files_selected = new QLabel(centralwidget);
        label_files_selected->setObjectName("label_files_selected");

        horizontalLayout_4->addWidget(label_files_selected);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        textEdit_names_files = new QTextEdit(centralwidget);
        textEdit_names_files->setObjectName("textEdit_names_files");
        textEdit_names_files->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color : rgb(0, 0, 0)"));

        verticalLayout_3->addWidget(textEdit_names_files);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_21);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        button_clean = new QPushButton(centralwidget);
        button_clean->setObjectName("button_clean");
        button_clean->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 199, 96);"));

        horizontalLayout_5->addWidget(button_clean);

        button_export = new QPushButton(centralwidget);
        button_export->setObjectName("button_export");
        button_export->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 199, 96);"));

        horizontalLayout_5->addWidget(button_export);


        horizontalLayout_16->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout_16);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        label_loading_export = new QLabel(centralwidget);
        label_loading_export->setObjectName("label_loading_export");
        label_loading_export->setFont(font);

        horizontalLayout_7->addWidget(label_loading_export);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_7);

        progressBar_proccess_export = new QProgressBar(centralwidget);
        progressBar_proccess_export->setObjectName("progressBar_proccess_export");
        progressBar_proccess_export->setMinimumSize(QSize(0, 20));
        progressBar_proccess_export->setMaximumSize(QSize(16777215, 20));
        progressBar_proccess_export->setValue(0);

        verticalLayout->addWidget(progressBar_proccess_export);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_14);

        label_time_proccess_export = new QLabel(centralwidget);
        label_time_proccess_export->setObjectName("label_time_proccess_export");

        horizontalLayout_10->addWidget(label_time_proccess_export);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_15);


        verticalLayout->addLayout(horizontalLayout_10);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EXCEL GCET APP", nullptr));
        label_select_file->setText(QCoreApplication::translate("MainWindow", "PLEASE SELECT THE FOLDER THAT CONTAINS THE BOMS", nullptr));
        button_search_files->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        exportID->setText(QCoreApplication::translate("MainWindow", "Copy PIDs", nullptr));
        label_loading_booms->setText(QCoreApplication::translate("MainWindow", "LOADING...", nullptr));
        label_time_proccess_booms->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
        label_select_file_drms->setText(QCoreApplication::translate("MainWindow", "PLEASE SELECT THE DRMS FILE", nullptr));
        button_search_files_drms->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_loading_drms->setText(QCoreApplication::translate("MainWindow", "LOADING...", nullptr));
        label_time_proccess_drms->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
        label_files_selected->setText(QCoreApplication::translate("MainWindow", "Files Selected:", nullptr));
        button_clean->setText(QCoreApplication::translate("MainWindow", "Clean", nullptr));
        button_export->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        label_loading_export->setText(QCoreApplication::translate("MainWindow", "LOADING...", nullptr));
        label_time_proccess_export->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
