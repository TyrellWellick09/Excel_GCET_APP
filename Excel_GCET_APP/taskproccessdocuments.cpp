#include "taskproccessdocuments.h"
#include "qforeach.h"
#include <QDebug>
#include <QHash>
#include <QStandardPaths>
#include "excel_adds.h"


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
                                             "AM Name",
                                             "D Created on"};

    QStringList column_names_final = {"Design Registration Project id",
                                      "GCET Engineer",
                                      "Boom file Name",
                                      "Design Registration Project Name",
                                      "Supplier",
                                      "Part mask with supplier prefix and '*'",
                                      "Annual value",
                                      "Status Text",
                                      "Date Design Registration Submitted",
                                      "Approved Date",
                                      "Design Registration Win/Winbuy Date",
                                      "D Created on",
                                      "Industry",
                                      "Market",
                                      "FAE Name",
                                      "AM Name",
                                      "Name",
                                      "Customer",
                                      "Sales Office"};

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
    QMap<QString, QList<QVariant>> dataMapOscar; // 56399
    QMap<QString, QList<QVariant>> dataMapNotOwner; // number

    QList<int> user_numbers = {61752, 55048, 53796, 56130, 061751, 55647, 58902, 56461, 56399};

    QList<QMap<QString, QList<QVariant>>*> dataMapListPtr;
    QList<QMap<QString, QList<QVariant>>> dataMapList;

    QMap<QString, QMap<QString, QList<QVariant>>> dataMapMap;

    //matchingDataMap["Boom file Name"];

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
    QList<QVariant> drms_dCreated = drms_columnDataMap["D Created on"];
    QList<QVariant> drms_partNumber = drms_columnDataMap["Part mask with supplier prefix and '*'"];
    QList drms_datamap_keys = drms_columnDataMap.keys();
    QList matching_datamap_keys = matchingDataMap.keys();
    drms_datamap_keys.append("Boom file Name");
    drms_datamap_keys.append("GCET Engineer");
    drms_columnDataMap["Boom file Name"];
    drms_columnDataMap["GCET Engineer"];

    //qDebug() << "Key names = " << drms_datamap_keys;

    int name = 0;
    //bool start = false;

    QList<QString> fileNames; // Aquí almacenaremos los nombres de archivo

    foreach (const QString &filePath, mfile_paths) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.completeBaseName();
        fileNames.append(fileName);

    }

    if (!mbooms_documents->isEmpty()) {

        for (const QXlsx::Document* boomDocument : *mbooms_documents) {

            QString fileName = fileNames[name];
            QDate creationDateBoom;
            QString creationDateString;
            int userNumber = 0;
            int fileNameSize = 0;

            qDebug() << "Nombre del archivo: " << fileName;

            // get the user number from the file name
            userNumber = (fileName.right(5)).toInt();
            qDebug() << "Nombre de usuario: " << userNumber;

            // get the size of the name
            fileNameSize = fileNames[name].length();


            if(user_numbers.contains(userNumber)){
                // get the date in string form
                creationDateString = (fileName.mid(fileNameSize - 18, 6));
                qDebug() << "IF";
                qDebug() << "Fecha de creacion del boom creationDateBoom string: " << creationDateString;

                // add the 20 number to complete the year
                creationDateString.push_front("20");

                // transforme to qdate form
                creationDateBoom = QDate::fromString(creationDateString, "yyyyMMdd");
            }
            else{
                qDebug() << "ELSE";

                // get the date in string form
                creationDateString = (fileName.mid(fileNameSize - 12, 6));

                // add the 20 number to complete the year
                creationDateString.push_front("20");

                // transforme to qdate form
                creationDateBoom = QDate::fromString(creationDateString, "yyyyMMdd");

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


            QList<QVariant> booms_projectNumberData = booms_columnDataMap["Project Number"];
            QList<QVariant> booms_partNumberData = booms_columnDataMap["Part Number"];


            for(const QVariant &boomPart : booms_partNumberData){

                // Iterar sobre los valores de "Design Registration Project id" de drms
                for (int i = 0; i < drms_designRegistrationData.size(); ++i) {
                    //qDebug() << "count i : " << drms_designRegistrationData.size();

                    // Verificar si el valor de drms está en la lista de "Project Number" de booms
                    if (booms_projectNumberData[2] == drms_designRegistrationData[i]) {
                        //qDebug() << "boms column size: " << booms_projectNumberData.size();
                        //qDebug() << "Status column size: " << drms_statusText.size();
                        //() << "i: " << i;

                        QVariant drmsPart = drms_partNumber[i];

                        if(boomPart == drmsPart){

                            if(i < drms_dCreated.size()){
                                QVariant dateTime = drms_dCreated[i];
                                qDebug() << "drms_dCreated[i] " << drms_dCreated[i];



                                //QDate dateCreated = excelSerialNumberToDate(dateTime.toDouble()); typeOfDate
                                QDate dateCreated = typeOfDate(drms_dCreated[i]);




                                // Imprimimos la fecha calculada
                                qDebug() << "Fecha de creacion del boom qdate: " << creationDateBoom;
                                qDebug()<< "Fecha drms D created: " << dateCreated;

                                if ((creationDateBoom.isValid()) && (creationDateBoom <= dateCreated)) {


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

                                            case 56399:
                                                dataMapOscar["Boom file Name"].append(fileNames[name]);
                                                dataMapOscar["GCET Engineer"].append("Oscar");
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

                                            case 56399:
                                                dataMapOscar[columnName].append(cellValue);
                                                break;

                                            default:
                                                dataMapNotOwner[columnName].append(cellValue);
                                                qDebug() << "NotOwner data: " << cellValue;
                                                break;

                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else{//qDebug() << "Not coincidence part";
                        }
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
        // Agregar una nueva hoja al documento para los stats
        xlsx.addSheet("Export");

        // "Annual value"
        // Obtener el formato actual de la celda
        QXlsx::Format formatoMoneda;
        formatoMoneda.setNumberFormat("$ #,##0.00");

        // add to the map of maps
        dataMapMap["Enrique"] = dataMapEnrique;
        dataMapMap["Alberto"] = dataMapAlberto;
        dataMapMap["Rafael"] = dataMapRafael;
        dataMapMap["Jose"] = dataMapJose;
        dataMapMap["Mitsuki"] = dataMapMitsuki;
        dataMapMap["Andres"] = dataMapAndres;
        dataMapMap["Fernando"] = dataMapFernando;
        dataMapMap["Augusto"] = dataMapAugusto;
        dataMapMap["Oscar"] = dataMapOscar;

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
        dataMapList.append(dataMapOscar);
        dataMapList.append(dataMapNotOwner);

        // Sumar las cantidades de "Annual Value"

        // Get the annual value by engineer
        for (const QString &name : dataMapMap_keys) {
            const QMap<QString, QList<QVariant>> &innerMap = dataMapMap.value(name);

            QVariantList annualValue = innerMap["Annual value"];
            QVariantList registers = innerMap["Status Text"];
            int i = 0;


            // Iterar sobre el QMap interno
            foreach (const QVariant &regis, registers) {




                if (regis == "Approved" || regis == "Win" ) {



                    // Almacenar el total en el QMap por ingeniero
                    annualValue_by_engineer[name] += annualValue[i].toDouble();
                    registers_by_engineer[name] ++;

                }

                i++;
            }
            total_registers += registers_by_engineer[name];
            total_annualvalue += annualValue_by_engineer[name];
        }


        int rowIndex = 1; // Comenzar en la fila 2 para dejar espacio para encabezados

        //qDebug() << "Test notowner" << dataMapNotOwner.keys();

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

                //qDebug() << "Qmap to check: " << currentMap;

                //qDebug() << "Print of headers: ";
                foreach (const QString &columnName, column_names_final) {
                    //                    qDebug() << "rowIndex: "<< rowIndex;
                    //                    qDebug() << "Column : " << columnNames.indexOf(columnName) + 1;
                    //                    qDebug() << "columnName: " << columnName;

                    xlsx.write(rowIndex, column_names_final.indexOf(columnName) + 1, columnName);

                }

                // Aumenta el índice de la primera fila para el QMap actual si no es el último QMap
                if (mapIndex < dataMapList.size() ) {
                    rowIndex++;
                }
                //                qDebug() << "rowIndex salto de linea: "<< rowIndex;

                foreach (const QString &columnName, column_names_final) {
                    // Obtén la lista de datos de la columna actual
                    QList<QVariant> columnData = currentMap[columnName];

                    // Realiza la conversión de fechas si la columna se llama "approved date"
                    if ((columnName == "Approved Date") || (columnName == "Design Registration Win/Winbuy Date") || (columnName == "Date Design Registration Submitted") ) {
                        for (int dataRowIndex = 0; dataRowIndex < columnData.size(); ++dataRowIndex) {
                            QVariant data = columnData[dataRowIndex];
                            if(!data.isNull()){
                                //                                qDebug() << "Date : " << data;
                                process_date(data, init_date, end_date);

                            }
                        }
                    }

                    // Itera sobre los datos de la columna y escríbelos en el archivo Excel
                    for (int dataRowIndex = 0; dataRowIndex < columnData.size(); ++dataRowIndex) {
                        //                        qDebug() << "rowIndex write: "<< rowIndex;
                        xlsx.write(rowIndex + dataRowIndex, column_names_final.indexOf(columnName) + 1, columnData[dataRowIndex]);
                        //                                                qDebug() << "Data print : " << columnData[dataRowIndex];
                    }
                }

                // Aumenta el índice de la primera fila para el próximo QMap if else
                rowIndex += column_names_final.isEmpty() ? 1 : currentMap[column_names_final[0]].size();


            }
        }


        xlsx.setColumnWidth(1, 25); // Design Registration Project id
        xlsx.setColumnWidth(2, 12); // GCET Engineer
        xlsx.setColumnWidth(3, 80); // Boom file name
        xlsx.setColumnWidth(4, 30); // Design Registration Project Name
        xlsx.setColumnWidth(5, 10); // Supplier
        xlsx.setColumnWidth(6, 30); // Part mask with supplier prefix and '*'
        xlsx.setColumnWidth(7, 12); // Annual Value
        xlsx.setColumnWidth(8, 10); // Status Text
        xlsx.setColumnWidth(9, 30); // Date Design Registration Submitted
        xlsx.setColumnWidth(10, 12); // approved date
        xlsx.setColumnWidth(11, 32); // Design Registration Win/Winbuy Date
        xlsx.setColumnWidth(12, 12); // D created on
        xlsx.setColumnWidth(13, 10); // Industry
        xlsx.setColumnWidth(14, 10); // Market
        xlsx.setColumnWidth(15, 20); // FAE Name
        xlsx.setColumnWidth(16, 12); // AM name
        xlsx.setColumnWidth(17, 30); // Name
        xlsx.setColumnWidth(18, 10); // Customer
        xlsx.setColumnWidth(19, 10); // Sales Office

        // Seleccionar la hoja en la que deseas escribir
        xlsx.addSheet("Stats");

        xlsx.selectSheet("Stats");

        //        qDebug() << "init write stats";
        xlsx.write(2, 1, "Total Approved/Win Registers");
        xlsx.write(2, 2, "Total Annual Value");
        xlsx.write(2, 3, "Start Date");
        xlsx.write(2, 4, "End Date");
        xlsx.write(10, 1, "Engineer");
        xlsx.write(10, 2, "Register by Engineer");
        xlsx.write(10, 3, "Annual Value by Engineer");
        xlsx.write(10, 4, "File Name");
        xlsx.write(10, 5, "Annual Value by Project");
        xlsx.write(10, 6, "Project Name");
        xlsx.write(10, 7, "FAE");
        xlsx.write(10, 8, "Industry");
        xlsx.write(10, 9, "Project ID");
        xlsx.write(3, 1, total_registers);
        xlsx.write(3, 2, total_annualvalue, formatoMoneda);
        xlsx.write(3, 3, init_date.toString());
        xlsx.write(3, 4, end_date.toString());

        // Start to fill the sheet 2 with stats
        rowIndex = 11; // dataMapEnrique
        QList<int> rowList;

        //        qDebug() << "Start new function";

        process_stats(dataMapList, xlsx, rowIndex, rowList);

        //        qDebug() << "after new function";

        // Enginer data annualValue_by_engineer, registers_by_engineer
        QStringList engineers_keys = registers_by_engineer.keys();
        int indexColumn = 0;

        foreach (const QString &columnName, engineers_keys) {

            QVariant registers = registers_by_engineer[columnName];
            QVariant annualValue = annualValue_by_engineer[columnName];

            xlsx.write(rowList[indexColumn], 1, columnName);
            xlsx.write(rowList[indexColumn], 2, registers);
            xlsx.write(rowList[indexColumn], 3, annualValue, formatoMoneda);

            indexColumn++;

        }

        xlsx.autosizeColumnWidth(1);
        xlsx.autosizeColumnWidth(2);
        xlsx.autosizeColumnWidth(3);
        xlsx.autosizeColumnWidth(4);
        xlsx.autosizeColumnWidth(5);
        xlsx.autosizeColumnWidth(6);
        xlsx.autosizeColumnWidth(7);
        xlsx.autosizeColumnWidth(8);
        xlsx.autosizeColumnWidth(9);


        // Aplicar el formato actualizado a la celda
        xlsx.setColumnFormat(5, formatoMoneda);



        xlsx.selectSheet("Export");

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


void TaskProccessDocuments::process_date(QVariant drms_date, QVariant &init_date, QVariant &end_date){

    // Fecha inicial (por ejemplo, 1 de enero de 2000)
    QDate startDate(2000, 1, 1);

    // String de fecha que quieres convertir
    QString date = drms_date.toString();

    // Convertir el string a un objeto QDate
    QDate date_converter = QDate::fromString(date, "yyyy-MM-dd");

    if (date_converter.isValid()) {
        // Calcular la diferencia en días
        int diference_days = startDate.daysTo(date_converter);
        //        qDebug() << "Número de días desde la fecha inicial:" << diference_days;

        if(init_date == ""){
            init_date = date_converter;
            //            qDebug() << "Start comparacion";
        }

        else if(end_date == ""){
            end_date = date_converter;
            //            qDebug() << "first end date ";
        }

        else if(init_date.toDate() > date_converter){
            init_date = date_converter;
            //            qDebug() << "NEW Init Date." << init_date ;
        }

        else if(end_date.toDate() < date_converter){
            end_date = date_converter;
            //            qDebug() << "End end date " << end_date;
        }

    } else {
        //        qDebug() << "Formato de fecha no válido.";
        //            qDebug() << "Fecha." << date_converter ;

    }
}


void TaskProccessDocuments::process_stats(QList<QMap<QString, QList<QVariant>>>& dataMapList, QXlsx::Document& document, int& rowIndex, QList<int>& rowList) {
    //    qDebug() << "init stats by engineer and project";

    // Define column names of the new sheet
    QStringList columnNamesSheet2 = {"Boom file Name", "Annual value", "Design Registration Project Name", "FAE Name", "Industry", "Design Registration Project id"};
    QVariant idx; // Variable to compare the project id to make the sum

    rowList.append(rowIndex);

    // Init for to iterate the list of maps
    for (int indexMap = 0; indexMap < dataMapList.size(); ++indexMap) {
        // Select the current map from the list
        QMap<QString, QList<QVariant>> currentMap = dataMapList[indexMap];
        QVariantList idList = currentMap["Design Registration Project id"]; // Variable to compare the project id to make the sum
        QVariantList revenueList = currentMap["Annual value"]; // List to store the revenue sum

        for (int indexBom = 0; indexBom < idList.size(); indexBom++) {
            QVariant id = idList[indexBom];

            if (idx != id) {
                int column = 4;

                foreach (const QString &columnName, columnNamesSheet2) {
                    QList<QVariant> columnData = currentMap[columnName];

                    int dataCount = columnData.size();

                    // Check if the index is within the valid range
                    if (indexBom < dataCount) {
                        QVariant data = columnData[indexBom];
                        //                        qDebug() << "data = " << data;
                        document.write(rowIndex, column, data);
                        column++;
                    } else {
                        //                        qDebug() << "Error: Index out of range for column " << columnName;
                        // Handle the error appropriately, e.g., skip writing to the document or add a default value.
                    }
                }

                double valueSum = 0;  // Reset valueSum for each new project ID

                for (int i = 0; i < revenueList.size(); i++) {
                    if (id == idList[i]) {
                        valueSum += revenueList[i].toFloat();
                    }
                }

                document.write(rowIndex, 5, valueSum);
                rowIndex++;
            }

            idx = id;
        }

        rowIndex++;
        rowList.append(rowIndex);
    }
}



