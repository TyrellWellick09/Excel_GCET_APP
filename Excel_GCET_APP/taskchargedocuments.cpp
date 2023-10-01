#include "taskchargedocuments.h"
#include <QDebug>
#include <QFileInfo>


TaskChargeDocuments::TaskChargeDocuments(QMainWindow* window, char id, QStringList paths_list, QList<QXlsx::Document*>* documents)
    : mId(id), mPathlist(paths_list), mDocuments(documents) , mainWindow(window)
{
    // Constructor
}



TaskChargeDocuments::~TaskChargeDocuments()
{
    qDebug() << mId << " Load files finish.";
}






void TaskChargeDocuments::run()
{
    int document_number = 1;
    int total_documnets_number = 0;
    int average_time_kb;
    double  average_time_files_kb;
    double time_proccess;
    double files_size = 0;
    QList<double> average_times; // mejor un contador y una suma;
    int suma = 0;
    QString time_proccess_message;
    int progress_value = 0;
    QString status;



    for(const QString &path : mPathlist){
        total_documnets_number = mPathlist.size();

        for(const QString &path : mPathlist){
            QFile file(path);
            qint64 fileSize = file.size(); // Size on bytes
            double fileSizeKB = fileSize / 1024.0; // Size KB
            files_size += fileSizeKB;
        }

        if (QFile::exists(path)){
            QElapsedTimer timer;
            timer.start();





            // Charge documents from each path
            QXlsx::Document* document = new QXlsx::Document(path);


            // Get the file size
            QFile file(path);
            qint64 fileSize = file.size(); // Size on bytes
            double fileSizeKB = fileSize / 1024.0; // Size KB
            average_time_files_kb = 0;


            if(document->load()){

                // Get the time in seconds
                time_proccess = timer.elapsed()/1000.0;



                average_time_kb = fileSizeKB / time_proccess;
                average_times.append(average_time_kb);

                for (int i = 0; i < average_times.size(); i++) {
                    suma += average_times[i];
                }

                if(average_time_kb != 0){

                    files_size = files_size - fileSizeKB;
                    average_time_files_kb = files_size/(suma/average_times.size());



                }

                // Add each document to the list
                mDocuments->append(document);

                progress_value = (document_number * 100)/total_documnets_number;

                time_proccess_message = QStringLiteral("File number %1, Size %2 KB, Time left %3  sec.")
                                            .arg(document_number)
                                            .arg(fileSizeKB)
                                            .arg(average_time_files_kb);


                if(mId == 'X'){
                    // Show time proccess
                    QMetaObject::invokeMethod(mainWindow, "update_booms_section", Qt::QueuedConnection,
                                              Q_ARG(QString, time_proccess_message),
                                              Q_ARG(int, progress_value),
                                              Q_ARG(bool, true));
                }

                if(mId == 'D'){
                    QMetaObject::invokeMethod(mainWindow, "update_drms_section", Qt::QueuedConnection,
                                              Q_ARG(int, progress_value),
                                              Q_ARG(bool, true));
                    QThread::msleep(2000);
                    QMetaObject::invokeMethod(mainWindow, "update_drms_section", Qt::QueuedConnection,
                                              Q_ARG(int, progress_value),
                                              Q_ARG(bool, false));

                }















                qDebug() << "File number " << document_number << "Size : " << fileSizeKB << "KB" << "Time : " << time_proccess << " sec";
                qDebug() << "rest time: " << average_time_files_kb << "sec";
                document_number += 1;

            }
            else
            {
                qDebug() << "Error al cargar el archivo: " << path;
            }


        }
    }

    if(mId == 'X'){
        QThread::msleep(2000);
        QMetaObject::invokeMethod(mainWindow, "update_booms_section", Qt::QueuedConnection,
                                  Q_ARG(QString, ""),
                                  Q_ARG(int, 0),
                                  Q_ARG(bool, false));
    }
}

