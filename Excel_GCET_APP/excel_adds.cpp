#include "excel_adds.h"
// Function to convert a base number to date. That numbers comes from excel
QDate excelSerialNumberToDate(double serialNumber) {
    qDebug() << "Base number: " << serialNumber;
    // The base date of Excel is January 1 of 1900
    const QDate excelBaseDate(1900, 1, 1);

    // Converter the serial number to days since the base date of Excel
    int days = static_cast<int>(serialNumber);

    // Create a QDate object using the base date of Excel and the days
    QDate date = excelBaseDate.addDays(days - 2); // Adjustment necessary for 1900/02/29 that does not exist in Excel
    return date;
}

QDate typeOfDate(const QVariant& valor) {
    bool succesfulConvertion = false;

    // Intentar convertir a double
    double doubleValue = valor.toDouble(&succesfulConvertion);
    if (succesfulConvertion) {
        qDebug() << "Fecha en formato número: " << doubleValue;

                    QDate dateCreated = excelSerialNumberToDate(doubleValue);

        return dateCreated;
    }

    // Intentar convertir a QDate
    QDate fecha = valor.toDate();
    if (fecha.isValid()) {
        qDebug() << "Fecha en formato QDate: " << fecha;
        // Retorna la fecha si la conversión es exitosa
        return fecha;
    }

    qDebug() << "Formato de fecha no reconocido.";
    return QDate();

}

