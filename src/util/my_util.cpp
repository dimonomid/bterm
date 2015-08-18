/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "my_util.h"

#include <QFile>



/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

QString MyUtil::byteArrayToHex(const std::vector<uint8_t> &data)
{
    QString text;

    for (uint8_t byte : data){
        QString tmp;
        tmp.sprintf("%.2x ", byte);
        text += tmp;
    }

    return text;
}

QVariantMap MyUtil::qjsErrorToVariant(const QJSValue &valError)
{
    return QVariantMap{
        {"lineNumber", valError.property("lineNumber").toVariant()},
            {"name", valError.property("name").toVariant()},
            {"fileName", valError.property("fileName").toVariant()},
            {"stack", valError.property("stack").toVariant()},
            {"message", valError.property("message").toVariant()}
    };
}

QString MyUtil::readFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return QString();
    }

    return QString(file.readAll());
}

