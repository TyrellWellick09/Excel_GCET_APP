#include "taskproccessdocuments.h"
#include "qforeach.h"
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
    QMap<QString, QList<QVariant>> dataMapEnrique; // 061752
    QMap<QString, QList<QVariant>> dataMapAlberto; // 055048
    QMap<QString, QList<QVariant>> dataMapRafael; // 053796
    QMap<QString, QList<QVariant>> dataMapJose; // 056130
    QMap<QString, QList<QVariant>> dataMapMitsuki; // 061751
    QMap<QString, QList<QVariant>> dataMapAndres; // 055647
    QMap<QString, QList<QVariant>> dataMapFernando; // 058902
    QMap<QString, QList<QVariant>> dataMapAugusto; // 056461
    QMap<QString, QList<QVariant>> dataMapNotOwner; // number

    QList<QMap<QString, QList<QVariant>>*> dataMapListPtr;
    QList<QMap<QString, QList<QVariant>>> dataMapList;

    QMap<QString, QMap<QString, QList<QVariant>>> dataMapMap;

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
    QList<QVariant> drms_statusText = drms_columnDataMap["Status Text"];
    QList<QVariant> drms_partNumber = drms_columnDataMap["Part mask with supplier prefix and '*'"];
    QList drms_datamap_keys = drms_columnDataMap.keys();
    QList matching_datamap_keys = matchingDataMap.keys();
    drms_datamap_keys.append("Boom file Name");
    drms_datamap_keys.append("GCET Engineer");
    drms_columnDataMap["Boom file Name"];
    drms_columnDataMap["GCET Engineer"];

    qDebug() << "Key names = " << drms_datamap_keys;

    int name = 0;
    //bool start = false;

    QList<QString> fileNames; // Aquí almacenaremos los nombres de archivo

    foreach (const QString &filePath, mfile_paths) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.baseName();
        fileNames.append(fileName);

    }

    if (!mbooms_documents->isEmpty()) {

        for (const QXlsx::Document* boomDocument : *mbooms_documents) {

            QString fileNamePrint = fileNames[name];
            qDebug() << "Nombre del archivo: " << fileNamePrint;
            int userNumber = (fileNames[name].right(5)).toInt();
            qDebug() << "Nombre de usuario: " << userNumber;

            int nameFileSize = fileNames[name].length();

            int creationDate = (fileNames[name].mid(nameFileSize - 18, 6)).toInt();
            qDebug() << "Fecha de creacion del boom : " << creationDate;

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


            QList<QVariant> booms_projectNumberData = booms_columnDataMap["Project Number"];
            QList<QVariant> booms_partNumberData = booms_columnDataMap["Part Number"];


            for(const QVariant &boomPart : booms_partNumberData){

                // Iterar sobre los valores de "Design Registration Project id" de drms
                for (int i = 0; i < drms_designRegistrationData.size(); ++i) {
                    //qDebug() << "count i : " << drms_designRegistrationData.size();

                    // Verificar si el valor de drms está en la lista de "Project Number" de booms
                    if (booms_projectNumberData[1] == drms_designRegistrationData[i]) {
                        //qDebug() << "boms column size: " << booms_projectNumberData.size();
                        //qDebug() << "Status column size: " << drms_statusText.size();
                        //() << "i: " << i;

                        QVariant drmsPart = drms_partNumber[i];

                        if(boomPart == drmsPart){

                            // Verifica si el índice es válido para la columna "Status text"
                            if (i < drms_statusText.size()) {
                                // Accede al valor de la columna "Status text" en el índice i
                                QVariant statusTextValue = drms_statusText[i];
                                qDebug() << "Status: " << drms_statusText[i];

                                // Comprueba si el valor es "Approved"
                                if (statusTextValue.toString() == "Approved") {
                                    // El valor es "Approved", puedes realizar las acciones que necesites aquí


                                    // Iterar sobre las claves (nombres de las columnas) en drms_columnDataMap
                                    for (const QString &columnName : drms_datamap_keys) {
                                        //qDebug() << "Name of the columns drms keys" << columnName;


                                        // Obtener la lista de datos de la columna actual
                                        QList<QVariant> columnData = drms_columnDataMap[columnName];
                                        //qDebug() << "column data: " << columnData;

                                        if(columnName == "Boom file Name" ){


                                            switch (userNumber) {
                                            case 61752:

                                                dataMapEnrique["Boom file Name"].append(fileNames[name]);
                                                dataMapEnrique["GCET Engineer"].append("Enrique");
                                                qDebug() << "Enrique boom: " << fileNames[name];
                                                break;

                                            case 55048:
                                                dataMapAlberto["Boom file Name"].append(fileNames[name]);
                                                dataMapAlberto["GCET Engineer"].append("Alberto");
                                                qDebug() << "Alberto boom: " << fileNames[name];
                                                break;

                                            case 53796:
                                                dataMapRafael["Boom file Name"].append(fileNames[name]);
                                                dataMapRafael["GCET Engineer"].append("Rafael");
                                                qDebug() << "Rafael boom: " << fileNames[name];
                                                break;

                                            case 56130:
                                                dataMapJose["Boom file Name"].append(fileNames[name]);
                                                dataMapJose["GCET Engineer"].append("Jose");

                                                break;

                                            case 61751:
                                                dataMapMitsuki["Boom file Name"].append(fileNames[name]);
                                                dataMapMitsuki["GCET Engineer"].append("Mitsuki");
                                                break;

                                            case 55647:
                                                dataMapAndres["Boom file Name"].append(fileNames[name]);
                                                dataMapAndres["GCET Engineer"].append("Andres");
                                                break;

                                            case 58902:
                                                dataMapFernando["Boom file Name"].append(fileNames[name]);
                                                dataMapFernando["GCET Engineer"].append("Fernando");
                                                break;

                                            case 56461:
                                                dataMapAugusto["Boom file Name"].append(fileNames[name]);
                                                dataMapAugusto["GCET Engineer"].append("Augusto");
                                                break;

                                            default:
                                                dataMapNotOwner["Boom file Name"].append(fileNames[name]);
                                                dataMapNotOwner["GCET Engineer"].append("Not Owner");
                                                qDebug() << "Not owner boom: " << fileNames[name];
                                                break;


                                            }
                                        }

                                        // Verificar si el índice es válido para esta columna
                                        if (i < columnData.size()) {
                                            // Obtener el valor en ese índice
                                            QVariant cellValue  = columnData[i];

                                            switch (userNumber) {
                                            case 61752:
                                                dataMapEnrique[columnName].append(cellValue);
                                                qDebug() << "Enrique data: " << cellValue;
                                                break;

                                            case 55048:
                                                dataMapAlberto[columnName].append(cellValue);
                                                qDebug() << "Alberto data: " << cellValue;
                                                break;

                                            case 53796:
                                                dataMapRafael[columnName].append(cellValue);
                                                qDebug() << "Rafael data: " << cellValue;
                                                break;

                                            case 56130:
                                                dataMapJose[columnName].append(cellValue);
                                                break;

                                            case 61751:
                                                dataMapMitsuki[columnName].append(cellValue);
                                                break;

                                            case 55647:
                                                dataMapAndres[columnName].append(cellValue);
                                                break;

                                            case 58902:
                                                dataMapFernando[columnName].append(cellValue);
                                                break;

                                            case 56461:
                                                dataMapAugusto[columnName].append(cellValue);
                                                break;

                                            default:
                                                dataMapNotOwner[columnName].append(cellValue);
                                                qDebug() << "NotOwner data: " << cellValue;
                                                break;
                                                \
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else{qDebug() << "Not coincidence part";}
                    }
                }

            }
            ++name;
        }

        // Declaration of the variables of statistics

        int total_registers = 0;
        double total_annualvalue = 0.0;
        QVariant init_date = "";
        QVariant end_date = "";
        QMap<QString, int> registers_by_engineer;
        QMap<QString, double> annualValue_by_engineer; // Get the total approved registers by engineer



        // Path of the new file
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString filePath = desktopPath + "/nuevo_archivo.xlsx";

        QXlsx::Document xlsx;
        // "Annual value"






        // Get the total approved registers by engineer


        // add to the map of maps
        dataMapMap["Enrique"] = dataMapEnrique;
        dataMapMap["Alberto"] = dataMapAlberto;
        dataMapMap["Rafael"] = dataMapRafael;
        dataMapMap["Jose"] = dataMapJose;
        dataMapMap["Mitsuki"] = dataMapMitsuki;
        dataMapMap["Andres"] = dataMapAndres;
        dataMapMap["Fernando"] = dataMapFernando;
        dataMapMap["Augusto"] = dataMapAugusto;
        dataMapMap["NotOwner"] = dataMapNotOwner;

        QList dataMapMap_keys = dataMapMap.keys();

        // Agrega Listas a los QMap a la lista
        dataMapList.append(dataMapEnrique);
        dataMapList.append(dataMapAlberto);
        dataMapList.append(dataMapRafael);
        dataMapList.append(dataMapJose);
        dataMapList.append(dataMapMitsuki);
        dataMapList.append(dataMapAndres);
        dataMapList.append(dataMapFernando);
        dataMapList.append(dataMapAugusto);
        dataMapList.append(dataMapNotOwner);

        // Get the annual value by engineer
//        qDebug() << "Start for";
        for (const QString &name : dataMapMap_keys) {
            const QMap<QString, QList<QVariant>> &innerMap = dataMapMap.value(name);
//            qDebug() << "in 1rst for";


            // Iterar sobre el QMap interno
            foreach (const QString &columnName, innerMap.keys()) {
//                qDebug() << "in 2cond for";
//                qDebug() << "columnname: "<< columnName;


                if (columnName == "Annual value") {
                    const QList<QVariant> &columnData = innerMap.value(columnName);
//                    qDebug() << "in if";


                    // Sumar las cantidades de "Annual Value"
                    double totalAnnualValue = 0.0;
                    foreach (const QVariant &data, columnData) {
//                        qDebug() << "data : " << data;
                        totalAnnualValue += data.toDouble();
//                        qDebug() << "total AnnualValue : " << totalAnnualValue;
                    }

                    // Almacenar el total en el QMap por ingeniero
                    annualValue_by_engineer[name] += totalAnnualValue;
                    total_annualvalue += totalAnnualValue;
                }
            }
        }

//        qDebug() << "Enrique Qmap: " << dataMapEnrique;
//        qDebug() << "Alberto Qmap: " << dataMapAlberto;





        int rowIndex = 1; // Comenzar en la fila 2 para dejar espacio para encabezados

        for (int mapIndex = 0; mapIndex < dataMapList.size(); ++mapIndex) {
            // Obtén el QMap actual
            QMap<QString, QList<QVariant>> currentMap = dataMapList[mapIndex];

//            qDebug() << "For number: " << mapIndex;

            if(!currentMap.isEmpty()){

                // Itera sobre las claves (nombres de las columnas) en el QMap
                QStringList columnNames = currentMap.keys();

                if (mapIndex > 0) {
                    // Si no es el primer QMap, agrega una fila en blanco
                    rowIndex++;
                }

                foreach (const QString &columnName, columnNames) {
                    // Si no es el primer QMap, agrega los nombres de las columnas

                    xlsx.write(rowIndex, columnNames.indexOf(columnName) + 1, columnName);
//                    qDebug() << "Column name first: " << columnName;

                }

                // Aumenta el índice de la primera fila para el QMap actual si no es el último QMap
                if (mapIndex < dataMapList.size() - 1) {
                    rowIndex++;
                }

                foreach (const QString &columnName, columnNames) {
                    // Obtén la lista de datos de la columna actual
                    QList<QVariant> columnData = currentMap[columnName];

                    // Realiza la conversión de fechas si la columna se llama "approved date"
                    if ((columnName == "Approved Date") || (columnName == "Design Registration Win/Winbuy Date") || (columnName == "Date Design Registration Submitted") ) {
                        for (int dataRowIndex = 0; dataRowIndex < columnData.size(); ++dataRowIndex) {
                            QVariant data = columnData[dataRowIndex];
                            if(!data.isNull()){
                                qDebug() << "Date : " << data;
                                process_date(data, &init_date, &end_date);
//                                double numericDate = columnData[dataRowIndex].toDouble();
//                                QDateTime baseDate = QDateTime::fromString("1900-01-01", "yyyy-MM-dd");
//                                QDateTime correctDate = baseDate.addDays(static_cast<int>(numericDate - 2));
//                                columnData[dataRowIndex] = correctDate.toString("MM/dd/yyyy");
                            }
                        }
                    }

                    // Itera sobre los datos de la columna y escríbelos en el archivo Excel
                    for (int dataRowIndex = 0; dataRowIndex < columnData.size(); ++dataRowIndex) {
                        xlsx.write(rowIndex + dataRowIndex, columnNames.indexOf(columnName) + 1, columnData[dataRowIndex]);
//                        qDebug() << "Data print : " << columnData[dataRowIndex];
                    }
                }

                // Aumenta el índice de la primera fila para el próximo QMap
                rowIndex += columnNames.isEmpty() ? 1 : currentMap[columnNames[0]].size();
            }
        }

        registers_by_engineer["Enrique"]= dataMapEnrique["Status Text"].size();
        total_registers += dataMapEnrique["Status Text"].size();
        registers_by_engineer["Alberto"] = dataMapAlberto["Status Text"].size();
        total_registers += dataMapAlberto["Status Text"].size();
        registers_by_engineer["Rafael"] = dataMapRafael["Status Text"].size();
        total_registers += dataMapRafael["Status Text"].size();
        registers_by_engineer["Jose"] = dataMapJose["Status Text"].size();
        total_registers += dataMapJose["Status Text"].size();
        registers_by_engineer["Mitsuki"] = dataMapMitsuki["Status Text"].size();
        total_registers += dataMapMitsuki["Status Text"].size();
        registers_by_engineer["Andres"] = dataMapAndres["Status Text"].size();
        total_registers += dataMapAndres["Status Text"].size();
        registers_by_engineer["Fernando"] = dataMapFernando["Status Text"].size();
        total_registers += dataMapFernando["Status Text"].size();
        registers_by_engineer["Augusto"] = dataMapAugusto["Status Text"].size();
        total_registers += dataMapAugusto["Status Text"].size();
        registers_by_engineer["NotOwner"] = dataMapNotOwner["Status Text"].size();
        total_registers += dataMapNotOwner["Status Text"].size();

        qDebug() << "Register by engineer: " << registers_by_engineer;
        qDebug() << "Annual value by enginer: " << annualValue_by_engineer;
        qDebug() << "Total Register: " << total_registers;
        qDebug() << "Total Annual Value: " << total_annualvalue;
        qDebug() << "Init date: " << init_date.toString();
        qDebug() << "End date: " << end_date.toString();




        xlsx.setColumnWidth(1, 20); // AM Name
        xlsx.setColumnWidth(2, 15); // Annual value
        xlsx.setColumnWidth(3, 15); // Approved Date
        xlsx.setColumnWidth(4, 70); // Boom file Name
        xlsx.setColumnWidth(5, 20); // Customer
        xlsx.setColumnWidth(6, 30); // Date Design Registration Submitted
        xlsx.setColumnWidth(7, 30); // Design Registration Project Name
        xlsx.setColumnWidth(8, 30); // Design Registration Project id
        xlsx.setColumnWidth(9, 33); // Design Registration Win/Winbuy Date
        xlsx.setColumnWidth(10, 20); // FAE Name
        xlsx.setColumnWidth(11, 15); // GCET Engineer
        xlsx.setColumnWidth(12, 15); // Industry
        xlsx.setColumnWidth(13, 15); // Market
        xlsx.setColumnWidth(14, 30); // Name
        xlsx.setColumnWidth(15, 35); // Part mask with supplier prefix and '*'
        xlsx.setColumnWidth(16, 15); // Sales Office
        xlsx.setColumnWidth(17, 15); // Status Text
        xlsx.setColumnWidth(18, 15); // Supplier

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


void TaskProccessDocuments::process_date(QVariant drms_date, QVariant *init_date, QVariant *end_date){

    // Fecha inicial (por ejemplo, 1 de enero de 2000)
    QDate startDate(2000, 1, 1);

    // String de fecha que quieres convertir
    QString date = drms_date.toString();

    // Convertir el string a un objeto QDate
    QDate date_converter = QDate::fromString(date, "yyyy-MM-dd");



    if (date_converter.isValid()) {
        // Calcular la diferencia en días
        int diference_days = startDate.daysTo(date_converter);
        qDebug() << "Número de días desde la fecha inicial:" << diference_days;

        if(*init_date == ""){
            *init_date = date_converter;
            qDebug() << "Start comparacion";
        }

        else if(*end_date == ""){
            *end_date = date_converter;
            qDebug() << "first end date ";}

        else if(init_date->toDate() > date_converter){
            *init_date = date_converter;
            qDebug() << "NEW Init Date." << *init_date ;
        }

        else if(end_date->toDate() < date_converter){
            *end_date = date_converter;
            qDebug() << "End end date " << *end_date;
        }

    } else {
        qDebug() << "Formato de fecha no válido.";
        qDebug() << "Fecha." << date_converter ;

    }
}
