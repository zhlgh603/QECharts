#include "echartsoption.h"

EChartsOption::EChartsOption()
{

}

EChartsOption::~EChartsOption()
{

}

void EChartsOption::empty()
{
    m_title.clear();
    m_title.insert("text", "");
    m_legend.clear();
    m_xAxis.clear();
    m_yAxis.clear();
    m_series.clear();

    QVariantMap seriesBar;
    QVariantList emptyData;
    seriesBar.insert("name", "");
    seriesBar.insert("type", "");
    seriesBar.insert("data", emptyData);
    m_series.append(seriesBar);
}

void EChartsOption::emptyBar()
{
    m_title.clear();
    m_title.insert("text", "");
    m_legend.clear();
    m_xAxis.clear();
    m_yAxis.clear();
    m_series.clear();

    QVariantMap seriesBar;
    QVariantList emptyData;
    seriesBar.insert("name", "");
    seriesBar.insert("type", "bar");
    seriesBar.insert("data", emptyData);
    m_series.append(seriesBar);
}

QVariantMap EChartsOption::getTitle() const
{
    return m_title;
}

QVariantMap EChartsOption::getTooltip() const
{
    return m_tooltip;
}

QVariantMap EChartsOption::getLegend() const
{
    return m_legend;
}

QVariantMap EChartsOption::getXAxis() const
{
    return m_xAxis;
}

QVariantMap EChartsOption::getYAxis() const
{
    return m_yAxis;
}

QVariantList EChartsOption::getSeries() const
{
    return m_series;
}

void EChartsOption::setTitle(QVariantMap title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(title);
}

void EChartsOption::setTooltip(QVariantMap tooltip)
{
    if (m_tooltip == tooltip)
        return;

    m_tooltip = tooltip;
    emit tooltipChanged(tooltip);
}

void EChartsOption::setLegend(QVariantMap legend)
{
    if (m_legend == legend)
        return;

    m_legend = legend;
    emit legendChanged(legend);
}

void EChartsOption::setXAxis(QVariantMap xAxis)
{
    if (m_xAxis == xAxis)
        return;

    m_xAxis = xAxis;
    emit xAxisChanged(xAxis);
}

void EChartsOption::setYAxis(QVariantMap yAxis)
{
    if (m_yAxis == yAxis)
        return;

    m_yAxis = yAxis;
    emit yAxisChanged(yAxis);
}

void EChartsOption::setSeries(QVariantList series)
{
    if (m_series == series)
        return;

    m_series = series;
    emit seriesChanged(series);
}

QString EChartsOption::buildJson()
{
    QString result;
    result += format("title", m_title);
    result += ",";
    result += format("tooltip", m_tooltip);
    result += ",";
    result += format("legend", m_legend);
    result += ",";
    result += format("xAxis", m_xAxis);
    result += ",";
    result += format("yAxis", m_yAxis);
    result += ",";
    result += format("series", m_series);
    return result;
}
