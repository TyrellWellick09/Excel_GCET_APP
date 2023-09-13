#ifndef TASKCHARGEDOCUMENTS_H
#define TASKCHARGEDOCUMENTS_H

#include <QRunnable>
#include <QMainWindow>
#include "mainwindow.h"



class TaskChargeDocuments : public QRunnable
{
public:
    TaskChargeDocuments(char id, QStringList paths_list, QList<QXlsx::Document*>* documents);
    ~TaskChargeDocuments();

protected:
    void run();

private:
    char mId;
    QStringList mPathlist;
    QList<QXlsx::Document*>* mDocuments;


};

#endif // TASKCHARGEDOCUMENTS_H
