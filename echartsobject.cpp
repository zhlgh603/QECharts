#include "echartsobject.h"

EChartsObject::EChartsObject(QObject *parent) : QObject(parent)
{

}

EChartsObject::~EChartsObject()
{

}

QString EChartsObject::toJson()
{
    return "{"+buildJson()+"}";
}

QString EChartsObject::buildJson()
{
    return "";
}

QString EChartsObject::format(const QString &key, QVariant value)
{
    return QString("%1: %2").arg(key).arg(formatVariant(value));
}

QString EChartsObject::formatMap(QVariantMap data)
{
    QString result;

    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext())
    {
        i.next();
        QString key = i.key();
        QVariant value = i.value();

        result += QString("%1: %2,").arg(key).arg(formatVariant(value));
    }
    if(","==result.right(1))
    {
        result = result.mid(0, result.length()-1);
    }

    return "{"+result+"}";
}

QString EChartsObject::formatVariant(QVariant value)
{
    QString result = "";
    switch (value.type()) {
    case QVariant::String:
        result = QString("'%1'").arg(value.toString());
        break;
    case QVariant::Int:
        result = QString::number(value.toInt());
        break;
    case QVariant::StringList:
    case QVariant::List:
    {
        result += "[";
        QVariantList list = value.toList();
        for(int i=0;i<list.count();i++)
        {
            QVariant v = list.at(i);
            result += formatVariant(v);
            result += ",";
        }
        if(","==result.right(1))
        {
            result = result.mid(0, result.length()-1);
        }

        result += "]";
    }
        break;
    case QVariant::Map:
        result = formatMap(value.toMap());
        break;
    default:
        break;
    }

    return result;
}
