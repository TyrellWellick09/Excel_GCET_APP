#include "taskproccessdocuments.h"
#include <QDebug>
#include <QHash>

TaskProccessDocuments::TaskProccessDocuments(QMainWindow* window, char id, QString export_path, QList<QXlsx::Document*>* drms_document, QList<QXlsx::Document*>* booms_documents )
    : mId(id), mexport_path(export_path), mdrms_document(drms_document), mbooms_documents(booms_documents),  mainWindow(window)
{
    // Constructor
}

TaskProccessDocuments::~TaskProccessDocuments()
{
    qDebug() << mId << " Procces files finish.";
}

void TaskProccessDocuments::run(){

    QStringList drms_column_names_to_find = {"Design Registration Project id", "Part mask with supplier prefix and '*'", "Supplier"};
    QStringList booms_column_names_to_find = {"Project Number", "Part Number", };

    // Start a map to store the values of each document
    QMap<QString, QList<QVariant>> drms_columnDataMap;
    QMap<QString, QList<QVariant>> booms_columnDataMap;
    QMap<QString, QList<QVariant>> matchingDataMap;

    qDebug() << "Export Proccess start";



    if (!mdrms_document->isEmpty()) {
        QXlsx::Worksheet *drms_worksheet = mdrms_document->at(0)->currentWorksheet();
        QStringList drms_columns;
        int drms_worksheet_dimention = drms_worksheet->dimension().rowCount();

        // Obtener los nombres de las columnas del archivo drms
        if (drms_worksheet) {
            for (int col = 1; col <= drms_worksheet->dimension().columnCount(); ++col) {
                drms_columns.append(drms_worksheet->read(1, col).toString());
            }
        }

        // Iterar sobre las columnas que deseas buscar
        foreach (const QString &desiredColumnName, drms_column_names_to_find) {
            int drms_columnIndex = drms_columns.indexOf(desiredColumnName);
            if (drms_columnIndex != -1) {
                // Encontrar la columna por nombre

                // Inicializar una lista para almacenar los datos de esta columna
                QList<QVariant> drms_columnData;

                // Recorrer las filas para obtener los datos de esta columna
                for (int row = 2; row <= drms_worksheet_dimention; ++row) {
                    QVariant drms_cellData = drms_worksheet->read(row, drms_columnIndex + 1); // +1 porque las columnas comienzan desde 1
                    drms_columnData.append(drms_cellData);
                }

                // Almacenar los datos de la columna en el mapa
                drms_columnDataMap[desiredColumnName] = drms_columnData;
            }
        }
//        // Print out with the console
//        foreach (const QString &columnName, drms_columnDataMap.keys()) {
//            qDebug() << "Columna:" << columnName;
//            QList<QVariant> columnData = drms_columnDataMap[columnName];
//            foreach (const QVariant &data, columnData) {
//                qDebug() << data.toString();
//            }
//        }
        qDebug() << "DRMS Proccessed";

    }
    else {
        qDebug() << "The drms document have not charged correctly";
    }




    if (!mbooms_documents->isEmpty()) {

        for (const QXlsx::Document* boomDocument : *mbooms_documents) {

            QXlsx::Worksheet *booms_worksheet = boomDocument->currentWorksheet();
            QStringList booms_columns; // Store the names of the columns
            int booms_worksheet_dimention = booms_worksheet->dimension().rowCount();



            // Get the names of the columns
            if (booms_worksheet) {
                for (int col = 1; col <= booms_worksheet->dimension().columnCount(); ++col) {
                    booms_columns.append(booms_worksheet->read(1, col).toString());
                }
            }

            foreach (const QString &desiredColumnName, booms_column_names_to_find) {
                int booms_columnIndex = booms_columns.indexOf(desiredColumnName);

                if (booms_columnIndex != -1) {

                    // Start a list to store the column data
                    QList<QVariant> booms_columnData;

                    // Recorrer las filas para obtener los datos de esta columna
                    for (int row = 2; row <= booms_worksheet_dimention; ++row) {
                        QVariant booms_cellData = booms_worksheet->read(row, booms_columnIndex + 1); // +1 porque las columnas comienzan desde 1
                        booms_columnData.append(booms_cellData);
                    }

                    // Almacenar los datos de la columna en el mapa
                    booms_columnDataMap[desiredColumnName] = booms_columnData;

//                    // Print out with the console
//                    foreach (const QString &columnName, booms_columnDataMap.keys()) {
//                        qDebug() << "Columna:" << columnName;
//                        QList<QVariant> columnData = booms_columnDataMap[columnName];
//                        foreach (const QVariant &data, columnData) {
//                            qDebug() << data.toString();
//                        }
//                    }

                }
            }

        }
        qDebug() << "BOOMS Proccessed";

    }



    else {
        qDebug() << "The booms document have not charged correctly";
    }


    // Comparative of the files

    qDebug() << "Comparative Init";
    QList<int> rowIndexes;


    // Obtener las listas de datos de las columnas que deseas comparar
    QList<QVariant> drms_designRegistrationData = drms_columnDataMap["Design Registration Project id"];
    QList<QVariant> booms_projectNumberData = booms_columnDataMap["Project Number"];

    QList<QVariant> matchingDrmsData; // Almacenar los datos coincidentes de drms


    // Iterar sobre los valores de "Design Registration Project id" de drms
    for (int i = 0; i < drms_designRegistrationData.size(); ++i) {
        const QVariant &drms_value = drms_designRegistrationData[i];

        // Verificar si el valor de drms está en la lista de "Project Number" de booms
        if (booms_projectNumberData[1] == drms_designRegistrationData[i]) {
            rowIndexes.append(i);

            //qDebug() << "Numero en lista: " << rowIndexes[i];

    }

        qDebug() << "Lista de indices : " << rowIndexes;

    //booms_projectNumberData(1) == drms_designRegistrationData(i)

//        for(int i = 0; i < rowIndexes.size(); ++i){
//            qDebug() << "Row at index" << rowIndexes[i] << ":";
//            foreach (const QString &columnName, drms_columnDataMap.keys()) {
//                QList<QVariant> columnData = drms_columnDataMap[columnName];

//                if (rowIndexes[i] < columnData.size()) {
//                    QVariant cellValue = columnData[rowIndexes[i]];
//                    qDebug() << columnName << ": " << cellValue;
//                }
//                else {
//                    qDebug() << "Column" << columnName << "has no data at index" << rowIndexes[i];
//                }
//            }
//            qDebug() << "------------------------";
//        }
    }
}













//qDebug() << "Column data: " << drms_columnDataMap[columnName];

//    // Crear un nuevo objeto QXlsx::Document para el archivo Excel de salida
//    QXlsx::Document outputExcel;

//    // Iterar sobre las columnas que deseas escribir en el nuevo archivo
//    foreach (const QString &columnName, drms_column_names_to_find) {
//        // Obtener los datos correspondientes desde matchingDataMap
//        QList<QVariant> columnData = matchingDataMap[columnName];

//        // Escribir los datos en la nueva hoja de cálculo del archivo Excel
//        for (int row = 0; row < columnData.size(); ++row) {
//            outputExcel.write(row + 1, drms_column_names_to_find.indexOf(columnName) + 1, columnData[row]);
//        }
//    }

//    // Guardar el archivo Excel en una ubicación específica
//    outputExcel.saveAs("C:/Users/061752/OneDrive - Avnet/Desktop/outputExcel.xlsx");


//    // Print out with the console
//    foreach (const QString &columnName, matchingDataMap.keys()) {
//        qDebug() << "Columna:" << columnName;
//        QList<QVariant> columnData = matchingDataMap[columnName];
//        foreach (const QVariant &data, columnData) {
//            qDebug() << data.toString();
//        }
//    }






//foreach (int rowIndex, rowIndexes) {
//qDebug() << "Row at index" << rowIndex << ":";
//foreach (const QString &columnName, matchingDataMap.keys()) {
//    QList<QVariant> columnData = matchingDataMap[columnName];

//    if (rowIndex < columnData.size()) {
//            QVariant cellValue = columnData[rowIndex];
//            qDebug() << columnName << ": " << cellValue;
//    } else {
//            qDebug() << "Column" << columnName << "has no data at index" << rowIndex;
//    }
//}
//qDebug() << "------------------------";
//}



