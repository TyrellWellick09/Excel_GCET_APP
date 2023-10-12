#ifndef TASKPROCCESSDOCUMENTS_H
#define TASKPROCCESSDOCUMENTS_H


#include <QRunnable>
#include <QMainWindow>
#include "xlsxdocument.h"
#include <QElapsedTimer>
#include <QThread>
#include <QLabel>
#include <QFileInfo>


class TaskProccessDocuments : public QRunnable
{
public:
    TaskProccessDocuments(QMainWindow* mainWindow, char id, QStringList export_path, QList<QXlsx::Document*>* drms_document, QList<QXlsx::Document*>* booms_documents);
    ~TaskProccessDocuments();


protected:
    void run();

private:
    char mId;
    QStringList mfile_paths;
    QList<QXlsx::Document*>* mdrms_document;
    QList<QXlsx::Document*>* mbooms_documents;
    QMainWindow* mainWindow;


};

#endif // TASKPROCCESSDOCUMENTS_H


