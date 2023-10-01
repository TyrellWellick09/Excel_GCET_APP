#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xlsxdocument.h"
#include <QThreadPool>
#include "taskchargedocuments.h"
#include <QPaintEvent>
#include <QLabel>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:
    void on_button_search_files_clicked();
    void on_button_search_files_drms_clicked();

public slots:
    void update_booms_section(const QString& time_proccess, int progres_value, bool state);
    void update_drms_section(int progres_value, bool state);




//Functions prototipes private
    void on_button_export_clicked();

private:
    QStringList open_excel_files();
    QString open_export_path();
    void get_data(QXlsx::Document &document);
    void get_index_selected_columns();



//Variables private
private:
    QStringList  files_paths_list;
    QString export_path;
    QVector<QVector<QString>> cell_values;
    QVector<int> selected_column_index;
    QList<QXlsx::Document*> loaded_documents;
    QList<QXlsx::Document*> loaded_drms_document;



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

//comment with vs code

