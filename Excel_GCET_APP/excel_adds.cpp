#include "excel_adds.h"

QDate excelSerialNumberToDate(double serialNumber) {
    // La fecha base en Excel es el 1 de enero de 1900
    const QDate excelBaseDate(1900, 1, 1);

//    // Ajuste para el problema del año 1900 en Excel
//    if (serialNumber < 60) {
//        serialNumber++;
//    }



    // Convertir el número de serie a días desde la fecha base de Excel
    int days = static_cast<int>(serialNumber);

    // Crear un objeto QDate utilizando la fecha base de Excel y los días
    QDate date = excelBaseDate.addDays(days - 2); // Ajuste necesario para el 1900/02/29 que no existe en Excel

    return date;
}



