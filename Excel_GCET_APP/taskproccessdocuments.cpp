#include "taskproccessdocuments.h"
#include <QDebug>
#include <QHash>
#include <QStandardPaths>


TaskProccessDocuments::TaskProccessDocuments(QMainWindow* window, char id, QStringList file_paths, QList<QXlsx::Document*>* drms_document, QList<QXlsx::Document*>* booms_documents )
    : mId(id), mfile_paths(file_paths), mdrms_document(drms_document), mbooms_documents(booms_documents),  mainWindow(window)
{
    // Constructor
}

TaskProccessDocuments::~TaskProccessDocuments()
{
    qDebug() << mId << " Procces files finish.";
    QMetaObject::invokeMethod(mainWindow, "update_statusBar", Qt::QueuedConnection,
                              Q_ARG(QString, "Export document proccess complete"),
                              Q_ARG(int, 3000));
}

void TaskProccessDocuments::run(){

    QStringList drms_column_names_to_find = {"Design Registration Project id",
                                             "Customer",
                                             "Sales Office",
                                             "Name",
                                             "Design Registration Project Name",
                                             "Supplier",
                                             "Part mask with supplier prefix and '*'",
                                             "Annual value",
                                             "Status Text",
                                             "Date Design Registration Submitted",
                                             "Approved Date",
                                             "Design Registration Win/Winbuy Date",
                                             "Industry",
                                             "Market",
                                             "FAE Name",
                                             "AM Name"};



    QStringList booms_column_names_to_find = {"Project Number", "Part Number" };

    // Start a map to store the values of each document
    QMap<QString, QList<QVariant>> drms_columnDataMap;
    QMap<QString, QList<QVariant>> booms_columnDataMap;
    QMap<QString, QList<QVariant>> matchingDataMap;

    //matchingDataMap["Boom file Name"];

    QList<int> rowIndexes;
    int progress_value = 0;


    //qDebug() << "Export Proccess start";

    QMetaObject::invokeMethod(mainWindow, "update_export_section", Qt::QueuedConnection,
                              Q_ARG(int, progress_value),
                              Q_ARG(bool, true));



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

        //qDebug() << "DRMS Proccessed";


    }
    else {
        QMetaObject::invokeMethod(mainWindow, "update_statusBar", Qt::QueuedConnection,
                                  Q_ARG(QString, "The drms document have not charged correctly"),
                                  Q_ARG(int, 0));

    }

    // Obtener las listas de datos de las columnas que deseas comparar
    QList<QVariant> drms_designRegistrationData = drms_columnDataMap["Design Registration Project id"];
    QList drms_datamap_keys = drms_columnDataMap.keys();
    drms_datamap_keys.append("Boom file Name");

    qDebug() << "Key names = " << drms_datamap_keys;

    int name = 0;
    bool start = false;

    QList<QString> fileNames; // Aquí almacenaremos los nombres de archivo

    foreach (const QString &filePath, mfile_paths) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        fileNames.append(fileName);

    }



    if (!mbooms_documents->isEmpty()) {

        for (const QXlsx::Document* boomDocument : *mbooms_documents) {


            if(start){

                // Agregar una fila en blanco
                for (const QString &columnName : drms_datamap_keys) {
                    matchingDataMap[columnName].append(QVariant());
                    //matchingDataMap["Boom file Name"].append(QVariant());
                }
                // Agregar las keys
                for (const QString &columnName : drms_datamap_keys) {

                    matchingDataMap[columnName].append(columnName);

                }
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

//                    int rowsize_boom = booms_columnDataMap[desiredColumnName].size();

//                    for (int var = 0; var < rowsize_boom; ++var) {
//                        matchingDataMap["Boom file Name"].append(fileNames[name]);
//                    }



                }
            }

            // Comparative of the files

//            qDebug() << "Comparative Init";
//            qDebug() << "project booms : "<<"booms_projectNumberData";



            QList<QVariant> booms_projectNumberData = booms_columnDataMap["Project Number"];



            // Iterar sobre los valores de "Design Registration Project id" de drms
            for (int i = 0; i < drms_designRegistrationData.size(); ++i) {

                // Verificar si el valor de drms está en la lista de "Project Number" de booms
                if (booms_projectNumberData[1] == drms_designRegistrationData[i]) {
                    rowIndexes.append(i);


                    // Iterar sobre las claves (nombres de las columnas) en drms_columnDataMap
                    for (const QString &columnName : drms_datamap_keys) {
                        qDebug() << "Name of the columns drms keys" << columnName;
                        // Obtener la lista de datos de la columna actual
                        QList<QVariant> columnData = drms_columnDataMap[columnName];

                        if(columnName == "Boom file Name"){
                            matchingDataMap[columnName].append(fileNames[name]);

                            qDebug() << "bom name in";

                        }
                        else{qDebug() << "bom name not in";}

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
            ++name;


            start = true;



        }

        QStringList matching_datamap_keys = matchingDataMap.keys();


        // Path of the new file
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString filePath = desktopPath + "/nuevo_archivo.xlsx";

        QXlsx::Document xlsx;







        int rowIndex = 2; // Comenzar en la fila 2 para dejar espacio para encabezados

        foreach (const QString &columnName, matching_datamap_keys) {
            xlsx.write(1, matching_datamap_keys.indexOf(columnName) + 1, columnName);
            QList<QVariant> columnData = matchingDataMap[columnName];

            for (int i = 0; i < columnData.size(); ++i) {

                xlsx.write(rowIndex, matching_datamap_keys.indexOf(columnName) + 1, columnData[i]);
                ++rowIndex;


            }
            rowIndex = 2;

        }




        xlsx.setColumnWidth(1, 30);
        xlsx.setColumnWidth(2, 35);
        xlsx.setColumnWidth(3, 15);




        xlsx.saveAs(filePath);

        qDebug() << "Archivo Excel guardado en:" << filePath;

        QMetaObject::invokeMethod(mainWindow, "update_export_section", Qt::QueuedConnection,
                                  Q_ARG(int, progress_value),
                                  Q_ARG(bool, false));



    }

    else {
        QMetaObject::invokeMethod(mainWindow, "update_statusBar", Qt::QueuedConnection,
                                  Q_ARG(QString, "The booms document have not charged correctly"),
                                  Q_ARG(int, 0));


    }




}





