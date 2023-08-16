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
    void on_pbSearch_clicked();
    void on_pbRead_clicked();
    void on_pbSearchExp_clicked();



private:
    QString openExcelFile();
    QString openOutputDirectory();
    int firstColumn;
    int lastColumn;
    QStringList columnNames;
    QStringList selectedColumnNames;
    QString selectedColumn;
    QString valueRange;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
