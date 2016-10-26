#ifndef ECHARTSOBJECT_H
#define ECHARTSOBJECT_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>

class EChartsObject : public QObject
{
    Q_OBJECT
public:
    explicit EChartsObject(QObject *parent = 0);
    virtual ~EChartsObject();

public:
    QString toJson();

signals:

public slots:

protected:
    virtual QString buildJson();

protected:
    QString format(const QString &key, QVariant value);
    QString formatMap(QVariantMap data);
    QString formatVariant(QVariant value);

};

#endif // ECHARTSOBJECT_H
