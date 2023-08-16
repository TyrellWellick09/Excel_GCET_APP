#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <vector>

#include "xlsxabstractsheet.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


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


void MainWindow::on_pbSearch_clicked()
{
    // Optener la ruta del archivo en el QLineEdit
    QString filePath = openExcelFile();
    // Mostrar la ruta del archivo en el QLineEdit
    ui->lineEdit->setText(filePath);
    qDebug() << "Archivo seleccionado: " << filePath;


}

QString MainWindow::openExcelFile()
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

void MainWindow::on_pbSearchExp_clicked()
{
    QString directoryPath = openOutputDirectory();
    if (!directoryPath.isEmpty()) {
        QLineEdit *lineEditExport = findChild<QLineEdit*>("lineEditExport");
        if (lineEditExport) {
            lineEditExport->setText(directoryPath);
        }
    }
}

QString MainWindow::openOutputDirectory()
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





void MainWindow::on_pbRead_clicked()
{
    QString filePath = ui->lineEdit->text(); // Obtener la ruta del QLineEdit

    // Verificar si la ruta del archivo existe
    if (!QFile::exists(filePath))
    {
        // Mostrar un mensaje de error
        QMessageBox::critical(this, "Error", "La ruta del archivo no existe.");
        return; // Salir de la función sin realizar más operaciones
    }

    // Obtener solo el nombre del archivo
    QString fileName = QFileInfo(filePath).fileName();

    // Construir el texto completo a mostrar en el QLabel
    QString labelText = QString("File selected: %1").arg(fileName);


    // Mostrar el nombre del archivo en el QLabel
    ui->labelNameFile->setText(labelText);



    qDebug() << "Archivo o ruta ingresada: " << filePath;

//    // Cargar el archivo Excel
//    QXlsx::Document originDocument(filePath);

//    if (xlsx.load())
//    {
//        // Mostrar el nombre del archivo en el QLabel
//        ui->labelNameFile->setText(labelText);



//        // Obtener la cantidad de columnas escritas en la primera hoja
//        int columnCount = xlsx.dimension().lastColumn() - xlsx.dimension().firstColumn() + 1;

//        firstColumn = xlsx.dimension().firstColumn();
//        lastColumn = xlsx.dimension().lastColumn();

//        int firstRow = xlsx.dimension().firstRow();
//        int lastRow = xlsx.dimension().lastRow();

//        // Mostrar la cantidad de columnas por consola
//        qDebug() << "El archivo tiene:" << columnCount <<"columnas";

//        qDebug() << "La primera columna es:" << xlsx.dimension().firstColumn();
//        qDebug() << "La ultima columna es:" << xlsx.dimension().lastColumn();

//        qDebug() << "La primera fila es:" << xlsx.dimension().firstRow();
//        qDebug() << "La ultima fila es:" << xlsx.dimension().lastRow();

//        //Cell* cell = xlsx.cellAt(1, 3); // get cell pointer.
//        // Seleccionar la primera hoja de trabajo
//        bool success = xlsx.selectSheet(0);

//        if (success)
//        {


//            // Obtener el puntero a la hoja de trabajo seleccionada
//            QXlsx::AbstractSheet *sheet = xlsx.currentWorksheet();
//            // Obtener el nombre de la hoja de trabajo
//            QString sheetName = sheet->sheetName();

//            // Imprimir el nombre de la hoja de trabajo
//            qDebug() << "Nombre de la hoja de trabajo:" << sheetName;





//            // Imprimir el nombre de cada columna
//            for (int col = firstColumn; col <= lastColumn; col++)
//            {
//                Cell* cell = xlsx.cellAt(firstRow, col);
//                QVariant columnName = cell->readValue();
//                qDebug() << "Nombre de la columna:" << col << columnName.toString();

//                columnNames.append(columnName.toString());


//            }





//        }
//        else
//        {
//            qDebug() << "No se encontraron hojas de trabajo en el archivo.";
//        }
//    }



//    else
//    {
//        qDebug() << "Error loading Excel file.";
//    }



}









