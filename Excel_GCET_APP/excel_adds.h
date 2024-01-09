#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QDateTime>

QDate excelSerialNumberToDate(double serialNumber);
QDate typeOfDate(const QVariant& valor);

#endif // EXCELUTILS_H
