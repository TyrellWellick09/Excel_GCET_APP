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
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
//using namespace QXlsx;
#include <QStandardItemModel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_search_file_clicked()
{
    // Optener la ruta del archivo en el QLineEdit
    file_path = open_excel_file();
    // Verificar que no este vacio
    if (!file_path.isEmpty()) {
        ui->lineEdit->setText(file_path);
        qDebug() << "Archivo seleccionado: " << file_path;
    }
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


void MainWindow::on_button_read_clicked()
{

    // Verificar si la ruta del archivo existe
    if (!QFile::exists(file_path))
    {
        // Mostrar un mensaje de error
        QMessageBox::critical(this, "Error", "La ruta del archivo no existe.");
        return; // Salir de la función sin realizar más operaciones
    }

    // Obtener solo el nombre del archivo
    QString fileName = QFileInfo(file_path).fileName();

    // Construir el texto completo a mostrar en el QLabel
    QString labelText = QString("File selected: %1").arg(fileName);

    qDebug() << "Archivo o ruta ingresada: " << file_path;




    // Cargar el archivo Excel
    QXlsx::Document origin_document(file_path);

    if (origin_document.load())
    {
        // Mostrar el nombre del archivo en el QLabel
        ui->label_file_name->setText(labelText);

        get_data(origin_document);

    }
    else
    {
        qDebug() << "Error loading Excel file.";
    }





}


QString MainWindow::open_excel_file()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Archivos Excel (*.xlsx *.xls)");

    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
            return selectedFiles.first();
        }
    }

    return "";
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
    ui->tableview_columns->setModel(model);






}





void MainWindow::on_button_export_clicked()
{
    uint8_t startRow = 5;
    uint8_t startColumn = 5;
    get_index_selected_columns();



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




    // Guardar el nuevo archivo en la ubicación deseada
    QString savePath = export_path + "/nuevo_archivo.xlsx";
    new_document.saveAs(savePath);

    // Verificar si la variable está vacía
    if (file_path.isEmpty()) {
        QMessageBox::warning(this, "Warning", "The file path is empty");
    } else if (export_path.isEmpty()) {
        QMessageBox::warning(this, "Warning", "The export path is empty");
    }














}

void MainWindow::get_index_selected_columns(){

    selected_column_index.clear();

    QItemSelectionModel *selectionModel = ui->tableview_columns->selectionModel();
    QAbstractItemModel *model = ui->tableview_columns->model();

    if (selectionModel && model) {
        QModelIndexList selectedColumns = selectionModel->selectedColumns();

        for (const QModelIndex &index : selectedColumns) {
            selected_column_index.append(index.column());
        }

        qDebug() << "Los indices de las columnas seleccionados son:"<< selected_column_index;
    }

}



//// Iterar a través de todas las filas
//for (int row = 0; row < cell_values.size(); ++row) {
//    int newRow = row + 1; // Las filas en QXlsx se indexan desde 1
//    int newColumn = 1;    // El primer valor de la fila

//    // Iterar a través de todas las columnas
//    for (int column = 0; column < cell_values[row].size(); ++column) {
//        QString cellValue = cell_values[row][column];

//        bool columnIsSelected = false;
//        foreach (const QModelIndex &selectedIndex, selectedColumns) {
//            if (selectedIndex.column() == column) {
//                columnIsSelected = true;
//                break;
//            }
//        }

//        if (columnIsSelected) {
//            // La columna está seleccionada, así que no hagas nada en esta celda
//        } else {
//            // La columna no está seleccionada, así que copia el valor al nuevo archivo y modelo
//            newDocument.write(newRow, newColumn, cellValue);
//        }

//        newColumn++; // Mover a la siguiente columna en el archivo
//    }
//}
