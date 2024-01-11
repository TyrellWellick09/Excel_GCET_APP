#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QHostInfo>
#include <QDirIterator>
#include <QListWidgetItem>
#include <QTextStream>



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

    //Start find the text file

    QString textPathFile = dir.absolutePath() + "/username.txt";



    QFile textFile(textPathFile);
    QString userText;

    if (textFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&textFile);
        while (!stream.atEnd()){

            userText.append(stream.readLine());
        }

    }
    textFile.close();

    qDebug() << "Text file path: " << textPathFile;

    qDebug() << "Text file: " << userText;




    if(!userText.isNull()){

        qDebug() << "Text is: " << userText;

        foreach (QString const &excelPathfile, excelFiles) {

            // Verify is the file exist
            QFile file(excelPathfile);
            if (file.exists()) {

                // Get the file info
                QFileInfo fileInfo(excelPathfile);
                QString rutaArchivo = fileInfo.absolutePath();
                QString nombreBase = fileInfo.completeBaseName();
                QString extension = fileInfo.suffix();

                if (nombreBase.contains(userText)) {
                    // Remove the username from the file name
                    nombreBase.remove("_"+userText);

                    // Create the new file name without the username
                    QString nuevoNombreArchivo = QString("%1.%2").arg(nombreBase, extension);

                    // Rename the file
                    QFile nuevoFile(rutaArchivo + "/" + nuevoNombreArchivo);
                    if (file.rename(nuevoFile.fileName())) {
                        qDebug() << "The username has been removed from the file name. The file is now:" << nuevoFile.fileName();
                    } else {
                        qDebug() << "Error renaming the file.";
                    }
                } else if(nombreBase.right(5) != userText){
                    // Create the new number with the username
                    QString nuevoNombreArchivo = QString("%1_%2.%3").arg(nombreBase, userText, extension);

                    // Renombra el archivo
                    QFile nuevoFile(rutaArchivo + "/" + nuevoNombreArchivo);
                    if (file.rename(nuevoFile.fileName())) {
                        qDebug() << "El archivo se ha renombrado exitosamente a:" << nuevoFile.fileName();
                    } else {
                        qDebug() << "Error al renombrar el archivo.";
                    }

                }

//                if(openConsole == false){a.exit();}
//                else{return a.exec();}



            }
        }

    }


    else{
        // if there are not text file use the computer name

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

                if (nombreBase.contains(username)) {
                    // Remove the username from the file name
                    nombreBase.remove("_"+username);

                    // Create the new file name without the username
                    QString nuevoNombreArchivo = QString("%1.%2").arg(nombreBase, extension);

                    // Rename the file
                    QFile nuevoFile(rutaArchivo + "/" + nuevoNombreArchivo);
                    if (file.rename(nuevoFile.fileName())) {
                        qDebug() << "The username has been removed from the file name. The file is now:" << nuevoFile.fileName();
                    } else {
                        qDebug() << "Error renaming the file.";
                    }
                } else if(nombreBase.right(5) != username){
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

//                if(openConsole == false){a.exit();}
//                else{return a.exec();}



            }
        }
    }
}

