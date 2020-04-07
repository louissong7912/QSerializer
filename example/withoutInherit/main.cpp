#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <qjsonmarshalerlib_global.h>
#include <qjsonmarshaler.h>
#include "employee.h"
#include <QDebug>
const QString EMPLOYEE_FILE = "employeeOutput.json";

void writeEmployeeToJsonFile(Employee * e);
Employee * readEmployeeFromJsonFile();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Employee employee;

    writeEmployeeToJsonFile(&employee);

    Employee * employee2 = readEmployeeFromJsonFile();

    qDebug()<<"EMPLOYEE 2"<<QString(QJsonDocument(QJsonMarshaler::Marshal(employee2)).toJson()).toStdString().c_str();
    exit(0);
    return a.exec();
}

void writeEmployeeToJsonFile(Employee * e)
{
    QJsonObject jsonUser =  QJsonMarshaler::Marshal(e);
    qDebug()<<"EMPLOYEE 1"<<QString(QJsonDocument(jsonUser).toJson()).toStdString().c_str();

    QJsonDocument document(jsonUser);
    QFile file(EMPLOYEE_FILE);
    if(file.exists())
        file.remove();
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QString(document.toJson()).toStdString().c_str());
        file.close();
    }
}

Employee * readEmployeeFromJsonFile()
{
    QFile file (EMPLOYEE_FILE);
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
        return QJsonMarshaler::Unmarshal<Employee>(jsonObj);
    }
    throw -1;
}

