#include "taskproccessdocuments.h"
#include <QDebug>
#include <QHash>
#include <QStandardPaths>


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

    QList<int> rowIndexes;


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

        qDebug() << "DRMS Proccessed";


    }
    else {
        qDebug() << "The drms document have not charged correctly";
    }

    // Obtener las listas de datos de las columnas que deseas comparar
    QList<QVariant> drms_designRegistrationData = drms_columnDataMap["Design Registration Project id"];




    if (!mbooms_documents->isEmpty()) {

        for (const QXlsx::Document* boomDocument : *mbooms_documents) {

            // Agregar el nombre del archivo boom
            for (const QString &columnName : drms_columnDataMap.keys()) {
                matchingDataMap[columnName].append(boomDocument->documentProperty("Title"));
            }

            // Agregar una fila en blanco
            for (const QString &columnName : drms_columnDataMap.keys()) {
                matchingDataMap[columnName].append(QVariant());
            }

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

                }
            }

            // Comparative of the files

            qDebug() << "Comparative Init";
            qDebug() << "project booms : "<<"booms_projectNumberData";



            QList<QVariant> booms_projectNumberData = booms_columnDataMap["Project Number"];

            QList<QVariant> matchingDrmsData; // Almacenar los datos coincidentes de drms


            // Iterar sobre los valores de "Design Registration Project id" de drms
            for (int i = 0; i < drms_designRegistrationData.size(); ++i) {
                const QVariant &drms_value = drms_designRegistrationData[i];

                // Verificar si el valor de drms está en la lista de "Project Number" de booms
                if (booms_projectNumberData[0] == drms_designRegistrationData[i]) {
                    rowIndexes.append(i);


                    // Iterar sobre las claves (nombres de las columnas) en drms_columnDataMap
                    for (const QString &columnName : drms_columnDataMap.keys()) {
                        // Obtener la lista de datos de la columna actual
                        QList<QVariant> columnData = drms_columnDataMap[columnName];

                        // Verificar si el índice es válido para esta columna
                        if (i < columnData.size()) {
                            // Obtener el valor en ese índice
                            QVariant cellValue = columnData[i];

                            // Agregar el valor al mapa de datos coincidentes
                            matchingDataMap[columnName].append(cellValue);
                        }
                    }

                }

            }
//            // Agregar dos filas en blanco
//            for (int j = 0; j < 2; ++j) {
//                for (const QString &columnName : drms_columnDataMap.keys()) {
//                    matchingDataMap[columnName].append(QVariant());
//                }
//            }



        }


        // Path of the new file
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString filePath = desktopPath + "/nuevo_archivo.xlsx";

        QXlsx::Document xlsx;






//        foreach (const QString &columnName, drms_columnDataMap.keys()) {

//            xlsx.write(1 , colum_number, columnName);
//            ++colum_number;
//        }


//        for(int i = 0; i < rowIndexes.size(); ++i){
//            int rowIndex = rowIndexes[i];
//            //qDebug() << "Row at index" << rowIndex << ":";


//            foreach (const QString &columnName, drms_columnDataMap.keys()) {
//                QList<QVariant> columnData = drms_columnDataMap[columnName];
//                ++colum_number;



//                if (rowIndexes[i] < columnData.size()) {
//                    QVariant cellValue = columnData[rowIndexes[i]];
//                    //qDebug() << columnName << ": " << cellValue;
//                    xlsx.write(i + 2, colum_number, cellValue);
//                }
//                else {
//                    qDebug() << "Column" << columnName << "has no data at index" << rowIndexes[i];
//                }
//            }
//            //qDebug() << "------------------------";
//        }

        int rowIndex = 2; // Comenzar en la fila 2 para dejar espacio para encabezados

        foreach (const QString &columnName, matchingDataMap.keys()) {
            xlsx.write(1, matchingDataMap.keys().indexOf(columnName) + 1, columnName);
            QList<QVariant> columnData = matchingDataMap[columnName];

            for (int i = 0; i < columnData.size(); ++i) {
                xlsx.write(rowIndex, matchingDataMap.keys().indexOf(columnName) + 1, columnData[i]);
                ++rowIndex;
            }
            rowIndex = 2;

        }





//        int colum_number = 0;


//        // filas
//        for (int i = 0; i < matchingDataMap.size(); ++i) {

//            // columnas
//            for (const QString &columnName : matchingDataMap.keys()) {
//                QList<QVariant> columnData = matchingDataMap[columnName];
//                ++colum_number;

//                QVariant cellValue = columnData[i];

//                xlsx.write(i+1, colum_number, cellValue);


//            }

//        }

        xlsx.setColumnWidth(1, 30);
        xlsx.setColumnWidth(1, 30);
        xlsx.setColumnWidth(1, 30);




        xlsx.saveAs(filePath);

        qDebug() << "Archivo Excel guardado en:" << filePath;




        for (int i = 0; i < matchingDataMap.begin().value().size(); ++i) {
            qDebug() << "Row" << i << ":";
            for (const QString &columnName : matchingDataMap.keys()) {
                QList<QVariant> columnData = matchingDataMap[columnName];

                if (i < columnData.size()) {
                    QVariant cellValue = columnData[i];
                    qDebug() << columnName << ": " << cellValue;
                } else {
                    qDebug() << columnName << ": "; // Impresión de celda en blanco
                }
            }
            qDebug() << "------------------------";
        }





    }

    else {
        qDebug() << "The booms document have not charged correctly";
    }




}





