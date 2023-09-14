#include "taskchargedocuments.h"
#include <QDebug>
#include <QFileInfo>

TaskChargeDocuments::TaskChargeDocuments(char id, QStringList paths_list, QList<QXlsx::Document*>* documents)
    : mId(id), mPathlist(paths_list), mDocuments(documents)
{
    // Constructor
}

//TaskChargeDocuments::TaskChargeDocuments(char id, QStringList paths_list)
//{
//    mId = id;
//    mPathlist = paths_list;

//}

TaskChargeDocuments::~TaskChargeDocuments()
{
    qDebug() << mId << " ha terminado la carga de archivos";
}

void TaskChargeDocuments::run()
{
    int document_number = 1;
    int average_time_kb;
    double  average_time_files_kb;
    double time_proccess;
    double files_size = 0;
    QList<double> average_times; // mejor un contador y una suma;
    int suma = 0;



    for(const QString &path : mPathlist){

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
}

