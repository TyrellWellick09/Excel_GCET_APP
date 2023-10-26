#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QHostInfo>
#include <QDirIterator>
#include <QListWidgetItem>



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    bool openConsole = false;


    // Get the execution path
    QString execution_path = qApp->applicationDirPath();

//    qDebug() << "App path : " << qApp->applicationDirPath();

    // Get the filespath
    QString currentPath = execution_path;

    QDir dir(currentPath);

    // return one folder
    dir.cdUp();

    // get the path
    QString pathFiles = dir.absolutePath();

//    qDebug() << "Path original: " << currentPath;
//    qDebug() << "Path anterior: " << pathFiles;

    QStringList excelFiles;  // Store the excel files

    QDirIterator it(pathFiles, QStringList() << "*.xlsx" <<"*.xls" << "*.xlsm",  QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        excelFiles.append(it.next());  // add the path to the list
    }

//    qDebug() << "Archivos Excel encontrados:";
    foreach (const QString &file, excelFiles) {
        qDebug() << file;
    }

    // Get the PCname and user number
    QString nombrePC = QHostInfo::localHostName();


    // Toma los últimos 5 caracteres del nombre de la PC
    QString username = nombrePC.right(5);

//    qDebug() << "Nombre de la PC: " << nombrePC;
//    qDebug() << "Últimos 5 caracteres del nombre de la PC: " << username;





        foreach (QString const &excelPathfile, excelFiles) {

        // Verify is the file exist
        QFile file(excelPathfile);
        if (file.exists()) {

            // Get the file info
            QFileInfo fileInfo(excelPathfile);
            QString rutaArchivo = fileInfo.absolutePath();
            QString nombreBase = fileInfo.completeBaseName();
            QString extension = fileInfo.suffix();

                if(nombreBase.right(5) != username){



                // Create the new number with the username
                QString nuevoNombreArchivo = QString("%1_%2.%3").arg(nombreBase, username, extension);

                // Renombra el archivo
                QFile nuevoFile(rutaArchivo + "/" + nuevoNombreArchivo);
                if (file.rename(nuevoFile.fileName())) {
                    qDebug() << "El archivo se ha renombrado exitosamente a:" << nuevoFile.fileName();
                } else {
                    qDebug() << "Error al renombrar el archivo.";
                }
            }
            else{qDebug() << "The file already has the username";
                openConsole = true;

            }
        } else {
            qDebug() << "El archivo no existe.";
            openConsole = true;
        }
        }



    if(openConsole == false){a.exit();}
    else{return a.exec();}



}




