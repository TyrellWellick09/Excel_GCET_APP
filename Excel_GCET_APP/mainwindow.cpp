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
    // Read only to the texEdit
    ui->textEdit_names_files->setReadOnly(true);
    // Activate scroll bar if is neccesary
    ui->textEdit_names_files->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->textEdit_names_files->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Set invisible the textEdit
    ui->textEdit_names_files->setVisible(false);
    // Set invisible the label
    ui->label_files_selected->setVisible(false);



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
    }
    else{
        qDebug() << "No files was selected";
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

    // Set visible the label
    ui->label_files_selected->setVisible(true);

    // Add the names to the label
    ui->textEdit_names_files->setPlainText(files_names);

    //    int document_number = 1;

    //    for(const QString &path : files_paths_list){

    //        if (QFile::exists(path)){

    //            // Charge documents from each path
    //            QXlsx::Document* document = new QXlsx::Document(path);
    //            if(document->load()){
    //                // Add each document to the list
    //                loaded_documents.append(document);
    //                qDebug() << "File number " << document_number;
    //                document_number += 1;

    //            }
    //            else
    //            {
    //                qDebug() << "Error al cargar el archivo: " << path;
    //            }
    //        }
    //    }


    TaskChargeDocuments *X = new TaskChargeDocuments('X', files_paths_list, &loaded_documents);
    QThreadPool::globalInstance()->start(X, QThread::NormalPriority);

    qDebug() << "Finish the procces";












    //    // Free memory for the documents loaded on the heap
    //    foreach (QXlsx::Document* document, loaded_documents)
    //    {
    //        delete document;
    //    }

    //    // Clear the list of documents (optional)
    //    loaded_documents.clear();


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


void MainWindow::updateProgress()
{

}




void MainWindow::on_button_search_export_clicked()
{
    export_path = open_export_path();
    if (!export_path.isEmpty()) {
        QLineEdit *lineEditExport = findChild<QLineEdit*>("lineEditExport");
        if (lineEditExport) {
            lineEditExport->setText(export_path);
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
    uint8_t startRow = 5;
    uint8_t startColumn = 5;
    //get_index_selected_columns();

    QVector<QVector<QString>> cell_values_export; // Tu vector bidimensional con los valores

    // Llenar cell_values_export con los valores de cell_values
    for (int i = 0; i < cell_values.size(); ++i) {
        QVector<QString> fila_export;
        for (int j : selected_column_index) {
            fila_export.append(cell_values[i][j]);
        }
        cell_values_export.append(fila_export);
    }


    
    // Crear un nuevo archivo Excel utilizando QXlsx
    QXlsx::Document new_document;




    for (int i = 0; i < cell_values_export.size(); ++i) {
        const QVector<QString> &row = cell_values_export[i];
        for (int j = 0; j < row.size(); ++j) {
            QString value = row[j];
            new_document.write(startRow + i, startColumn + j, value);
        }
    }




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


