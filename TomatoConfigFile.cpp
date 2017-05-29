#include "TomatoConfigFile.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>

bool TomatoConfigFile::readConfigFile(unsigned int & working_time, unsigned int & resting_time)
{
    if (!QFile::exists(Tomato_Config_File)) {
        return false;
    }

    QFile file(Tomato_Config_File);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject rootObject = d.object();
    working_time = static_cast<unsigned int>(rootObject.value(QString("WorkingTime")).toInt());
    resting_time = static_cast<unsigned int>(rootObject.value(QString("RestingTime")).toInt());

    return true;
}

void TomatoConfigFile::setConfigFile(unsigned int working_time, unsigned int resting_time)
{
    QJsonObject json;
    json.insert("WorkingTime", static_cast<int>(working_time));
    json.insert("RestingTime", static_cast<int>(resting_time));

    QJsonDocument document;
    document.setObject(json);
    QString json_str(document.toJson(QJsonDocument::Compact));

    QFile file(Tomato_Config_File);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);
    in << json_str;
    file.close();
}

