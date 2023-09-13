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

    for(const QString &path : mPathlist){

        if (QFile::exists(path)){

            // Charge documents from each path
            QXlsx::Document* document = new QXlsx::Document(path);
            if(document->load()){
                // Add each document to the list
                mDocuments->append(document);
                qDebug() << "File number " << document_number;
                document_number += 1;

            }
            else
            {
                qDebug() << "Error al cargar el archivo: " << path;
            }
        }
    }
}

