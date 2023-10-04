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

//    // Set invisible the textEdit
//    ui->textEdit_names_files->setVisible(false);

    ui->label_loading_drms->setVisible(false);
    ui->progressBar_proccess_drms->setVisible(false);
//    ui->progressBar_proccess_drms->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px;}");
//    ui->progressBar_proccess_drms->setTextVisible(false);
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



    // Show status
    //ui->label_status->setText("Finish Charge_Documents Task");

    //    // Free memory for the documents loaded on the heap
    //    foreach (QXlsx::Document* document, loaded_documents)
    //    {
    //        delete document;
    //    }

    //    // Clear the list of documents (optional)
    //    loaded_documents.clear();


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


void MainWindow::get_data(QXlsx::Document &document){

    int first_column = 0;
    int end_column = 0;
    int first_row = 0;
    int end_row = 0;

    //Obtener la cantidad de columnas escritas en la primera hoja
    int columnCount = document.dimension().lastColumn() - document.dimension().firstColumn() + 1;


    first_column = document.dimension().firstColumn();
    first_row = document.dimension().firstRow();
    end_column = document.dimension().lastColumn();
    end_row = document.dimension().lastRow();


//    // Mostrar la cantidad de columnas por consola
//    qDebug() << "El archivo tiene:" << columnCount <<"columnas";
//    qDebug() << "La primera columna es:" << document.dimension().firstColumn();
//    qDebug() << "La ultima columna es:" << document.dimension().lastColumn();
//    qDebug() << "La primera fila es:" << document.dimension().firstRow();
//    qDebug() << "La ultima fila es:" << document.dimension().lastRow();



    // Leer y almacenar los valores del rango de celdas
    for (int row = first_row; row <= end_row; ++row) {
        QVector<QString> rowData;
        for (int column = first_column; column <= end_column; ++column) {
            QXlsx::Cell *cell = document.cellAt(row, column);
            if (cell) {
                rowData.push_back(cell->value().toString());
            } else {
                rowData.push_back(""); // Celda vacía
            }
        }
        cell_values.push_back(rowData);
    }

    // Configurar el modelo de datos del QTableView
    QStandardItemModel *model = new QStandardItemModel(cell_values.size(), cell_values[0].size());
    for (int row = 0; row < cell_values.size(); ++row) {
        for (int column = 0; column < cell_values[row].size(); ++column) {
            QModelIndex index = model->index(row, column);
            model->setData(index, cell_values[row][column]);
        }
    }

    // Cambiar encabezado de la fila
    QStringList verticalHeaders;
    for (int i = 0; i < model->rowCount(); ++i) {
        verticalHeaders << QString::number(i);
    }
    model->setVerticalHeaderLabels(verticalHeaders);

    // Cambiar encabezado de columna
    QStringList horizontalHeaders;
    for (int j = 0; j < model->columnCount(); ++j) {
        horizontalHeaders << QString::number(j);
    }
    model->setHorizontalHeaderLabels(horizontalHeaders);



    // Asignar el modelo al QTableView
    //ui->tableview_columns->setModel(model);






}


void MainWindow::on_button_export_clicked()
{
    QString export_path;

    // Add the task to charge the documents to the Qthread Pool
    TaskProccessDocuments *E = new TaskProccessDocuments(this, 'E', export_path , &loaded_drms_document, &loaded_documents);
    QThreadPool::globalInstance()->start(E, QThread::NormalPriority);






//    // Guardar el nuevo archivo en la ubicación deseada
//    QString savePath = export_path + "/nuevo_archivo.xlsx";
//    new_document.saveAs(savePath);

//    // Verificar si la variable está vacía
//    if (file_paths.isEmpty()) {
//        QMessageBox::warning(this, "Warning", "The file path is empty");
//    } else if (export_path.isEmpty()) {
//        QMessageBox::warning(this, "Warning", "The export path is empty");
//    }
}


