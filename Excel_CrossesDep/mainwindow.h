#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xlsxdocument.h"
#include <QThread>



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
    void on_button_search_file_clicked();
    void on_button_read_clicked();
    void on_button_search_export_clicked();


//Functions prototipes private
    void on_button_export_clicked();

private:
    QStringList open_excel_files();
    QString open_export_path();
    void get_data(QXlsx::Document &document);
    void get_index_selected_columns();


//Variables private
private:
    QStringList  file_paths;
    QString export_path;
    QVector<QVector<QString>> cell_values;
    QVector<int> selected_column_index;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
