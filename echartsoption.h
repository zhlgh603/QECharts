#ifndef ECHARTSOPTION_H
#define ECHARTSOPTION_H

#include "echartsobject.h"

#include <QList>
#include <QVariantMap>

class EChartsOption : public EChartsObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap title READ getTitle WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QVariantMap tooltip READ getTooltip WRITE setTooltip NOTIFY tooltipChanged)
    Q_PROPERTY(QVariantMap legend READ getLegend WRITE setLegend NOTIFY legendChanged)
    Q_PROPERTY(QVariantMap xAxis READ getXAxis WRITE setXAxis NOTIFY xAxisChanged)
    Q_PROPERTY(QVariantMap yAxis READ getYAxis WRITE setYAxis NOTIFY yAxisChanged)
    Q_PROPERTY(QVariantList series READ getSeries WRITE setSeries NOTIFY seriesChanged)

public:
    EChartsOption();
    ~EChartsOption();

public:
    void empty();
    void emptyBar();

public:
    QVariantMap getTitle() const;

    QVariantMap getTooltip() const;

    QVariantMap getLegend() const;

    QVariantMap getXAxis() const;

    QVariantMap getYAxis() const;

    QVariantList getSeries() const;

public slots:
    void setTitle(QVariantMap title);

    void setTooltip(QVariantMap tooltip);

    void setLegend(QVariantMap legend);

    void setXAxis(QVariantMap xAxis);

    void setYAxis(QVariantMap yAxis);

    void setSeries(QVariantList series);

signals:
    void titleChanged(QVariantMap title);

    void tooltipChanged(QVariantMap tooltip);

    void legendChanged(QVariantMap legend);

    void xAxisChanged(QVariantMap xAxis);

    void yAxisChanged(QVariantMap yAxis);

    void seriesChanged(QVariantList series);

protected:
    QString buildJson();

private:
    /**
     * @brief m_title       标题组件，包含主标题和副标题
     * show|boolean[default:true]           是否显示标题组件
     * text|string[defalut:'']              主标题，支持\n换行
     * subtext|string[default:'']           副标题，支持\n换行
     * itemGap|number[default:10]           主副标题之间的间距
     * textAlign|string                     标题水平对齐，支持'left','center','right'
     * textBaseline|string                  标题垂直对齐，支持'top','middle','bottom'
     */
    QVariantMap m_title;
    QVariantMap m_tooltip;
    QVariantMap m_legend;
    QVariantMap m_xAxis;
    QVariantMap m_yAxis;
    QVariantList m_series;

};

#endif // ECHARTSOPTION_H
