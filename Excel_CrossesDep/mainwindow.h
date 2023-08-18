#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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
private:
    QString open_excel_file();
    QString open_export_path();

//Variables private
private:
    QString file_path;
    QString export_path;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
