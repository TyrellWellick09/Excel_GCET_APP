#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <vector>
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include <QStandardItemModel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_drms->setFocus();


    // Read only to the texEdit
    ui->textEdit_names_files->setReadOnly(true);
    // Activate scroll bar if is neccesary
    ui->textEdit_names_files->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->textEdit_names_files->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->label_loading_drms->setVisible(false);
    ui->progressBar_proccess_drms->setVisible(false);

    ui->label_time_proccess_drms->setVisible(false);

    ui->label_loading_booms->setVisible(false);
    ui->progressBar_proccess_booms->setVisible(false);
    ui->label_time_proccess_booms->setVisible(false);

    ui->label_loading_export->setVisible(false);
    ui->progressBar_proccess_export->setVisible(false);
    ui->label_time_proccess_export->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_search_files_clicked()
{
    QString files_names;

    // Get the list of files in the selected folder
    files_paths_list = open_excel_files();

    // Check if it's not empty
    if (!files_paths_list.isEmpty()) {
        // Print the list of files to the console
        qDebug() << "Files found in the folder:";
        for (const QString &file_path : files_paths_list) {
            qDebug() << file_path;
        }

        for(const QString &file :files_paths_list ){
            // Get the names of the files
            QString file_path = QFileInfo(file).fileName();

            // Separate by comma
            if(!files_names.isEmpty()){
                files_names += '\n';
            }

            // Add to the list
            files_names += file_path;
        }

        // Set visible the textEdit
        ui->textEdit_names_files->setVisible(true);

        // Add the names to the textEdit
        ui->textEdit_names_files->setPlainText(files_names);


        // Add the task to charge the documents to the Qthread Pool
        TaskChargeDocuments *X = new TaskChargeDocuments(this, 'X', files_paths_list, &loaded_documents);
        QThreadPool::globalInstance()->start(X, QThread::NormalPriority);

        qDebug() << "Finish the procces";


    }
    else{
        qDebug() << "No files was selected";
    }



}

void MainWindow::update_booms_section(const QString& time_proccess, int progres_value, bool state)
{
    if(state){
        // make visible the widgets
        ui->label_loading_booms->setVisible(state);
        ui->progressBar_proccess_booms->setVisible(state);
        ui->label_time_proccess_booms->setVisible(state);

        // update the widgets
        ui->label_loading_booms->setText("LOADING...");
        ui->progressBar_proccess_booms->setValue(progres_value);
        ui->label_time_proccess_booms->setText(time_proccess);
        if(progres_value >=100){ui->label_loading_booms->setText("LOADED.");}


    }
    else{
        // make visible the widgets
        ui->label_loading_booms->setVisible(state);
        ui->progressBar_proccess_booms->setVisible(state);
        ui->label_time_proccess_booms->setVisible(state);

        // update the widgets
        ui->label_loading_booms->setText("");
        ui->progressBar_proccess_booms->setValue(progres_value);
        ui->label_time_proccess_booms->setText("");

    }
}


void MainWindow::update_drms_section(int progres_value, bool state)
{
    if(state){
        // make visible the widgets
        ui->label_loading_drms->setVisible(state);
        ui->progressBar_proccess_drms->setVisible(state);

        // update the widgets
        ui->label_loading_drms->setText("LOADING...");
        ui->progressBar_proccess_drms->setValue(progres_value);
        if(progres_value >=100){ui->label_loading_drms->setText("LOADED.");}

    }
    else{
        // make visible the widgets
        ui->label_loading_drms->setVisible(state);
        ui->progressBar_proccess_drms->setVisible(state);

        // update the widgets
        ui->label_loading_drms->setText("");
        ui->progressBar_proccess_drms->setValue(progres_value);

    }
}



QStringList MainWindow::open_excel_files()
{
    // Open a file dialog window
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory); // Change the mode to Directory to select a folder
    dialog.setOption(QFileDialog::ShowDirsOnly, true); // Show folders only

    QString selectedFolder; // Variable to store the folder path
    if (dialog.exec())
    {
        QStringList selected_files = dialog.selectedFiles(); // Get the path of the folder
        if (!selected_files.isEmpty())
        {
            selectedFolder = selected_files.first(); // Store in selectedFiles
            // Set the folder path to the QLineEdit
            ui->lineEdit->setText(selectedFolder);
        }
        QDir directory(selectedFolder);
        QStringList fileFilters;
        fileFilters << "*.xlsx" << "*.xls"; // Add the file extensions you want to process here
        QStringList files_list = directory.entryList(fileFilters, QDir::Files);
        for (QString &file : files_list) {
            file = directory.absoluteFilePath(file); // Get the full path of each file and stor in files_list
        }
        return files_list;
    }


    return QStringList(); // Return an empty list if no folder was selected

}


void MainWindow::on_button_search_files_drms_clicked()
{

    // Open a file dialog window
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile); // Change the mode to Directory to select a file
    dialog.setNameFilter("Excel File(*.xlsx *.xls)"); // Filter by .Xlsx and . Xls



    if (dialog.exec())
    {
        QStringList drms_selected = dialog.selectedFiles(); // Variable to store the file path
        QString file_path = QFileInfo(drms_selected.constFirst()).fileName();
        if (!drms_selected.isEmpty())
        {
            qDebug() << "File charge successful: " << drms_selected;

            // Add the task to charge the documents to the Qthread Pool
            TaskChargeDocuments *D = new TaskChargeDocuments(this, 'D', drms_selected, &loaded_drms_document);
            QThreadPool::globalInstance()->start(D, QThread::NormalPriority);

            ui->lineEdit_drms->setText(drms_selected.constFirst());

            ui->progressBar_proccess_drms->setRange(0, 0);
            ui->progressBar_proccess_drms->setVisible(true);
            ui->label_loading_drms->setVisible(true);

        }


    }



}




QString MainWindow::open_export_path()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setWindowTitle("Seleccionar Carpeta de Salida");

    if (dialog.exec())
    {
        QStringList selectedDirectories = dialog.selectedFiles();
        if (!selectedDirectories.isEmpty())
        {
            return selectedDirectories.first();
        }
    }

    return "";
}



void MainWindow::on_button_export_clicked()
{
    if(!files_paths_list.isEmpty() || !loaded_documents.isEmpty() || !loaded_drms_document.isEmpty()){

        ui->progressBar_proccess_export->setRange(0, 0);
        ui->progressBar_proccess_export->setVisible(true);
        ui->label_loading_export->setVisible(true);

        // Add the task to charge the documents to the Qthread Pool
        TaskProccessDocuments *E = new TaskProccessDocuments(this, 'E', files_paths_list , &loaded_drms_document, &loaded_documents);
        QThreadPool::globalInstance()->start(E, QThread::NormalPriority);
    }
    else{
        // StatusBar error message
    }





}

void MainWindow::update_export_section(int progres_value, bool state)
{
    if(state){
        // make visible the widgets
        ui->label_loading_export->setVisible(state);
        ui->progressBar_proccess_export->setVisible(state);

        // update the widgets
        ui->label_loading_export->setText("LOADING...");
        ui->progressBar_proccess_export->setValue(progres_value);
        if(progres_value >=100){ui->label_loading_drms->setText("LOADED.");}

    }
    else{
        // make visible the widgets
        ui->label_loading_export->setVisible(state);
        ui->progressBar_proccess_export->setVisible(state);

        // update the widgets
        ui->label_loading_export->setText("");
        ui->progressBar_proccess_export->setValue(progres_value);

    }
}

void MainWindow::on_button_clean_clicked()
{
    // Clear all the lists and variables
    files_paths_list.clear();
    loaded_documents.clear();
    loaded_drms_document.clear();

    // Clean the main window's widgets

    ui->lineEdit->clear();
    ui->lineEdit_drms->clear();
    ui->textEdit_names_files->clear();

}

