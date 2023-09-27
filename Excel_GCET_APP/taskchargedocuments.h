#ifndef TASKCHARGEDOCUMENTS_H
#define TASKCHARGEDOCUMENTS_H

#include <QRunnable>
#include <QMainWindow>
#include "xlsxdocument.h"
#include <QElapsedTimer>
#include <QThread>


class TaskChargeDocuments : public QRunnable
{
public:
    TaskChargeDocuments(QMainWindow* mainWindow, char id, QStringList paths_list, QList<QXlsx::Document*>* documents);
    ~TaskChargeDocuments();

protected:
    void run();
signals:
    void write_label();

private:
    char mId;
    QStringList mPathlist;
    QList<QXlsx::Document*>* mDocuments;
    QMainWindow* mainWindow;



};

#endif // TASKCHARGEDOCUMENTS_H
