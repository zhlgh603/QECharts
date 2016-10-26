#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWebView>
#include <QWebFrame>
#include <QWebSettings>
#include <QWebElementCollection>
#include <QWebInspector>
#include <QUrl>
#include <QRect>
#include <QDesktopWidget>

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include <QDateTime>

#include <QAction>
#include <QMenu>
#include <QEvent>
#include <QContextMenuEvent>

#include "echartsoption.h"

void MainWindow::printCurrentTime()
{
    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:zzz");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_option = new EChartsOption();
    m_option->empty();

    m_menu = new QMenu(this);

    QAction *tutorialAction = m_menu->addAction(trUtf8("ECharts教程"));
    connect(tutorialAction, SIGNAL(triggered(bool)), this, SLOT(tutorial()));

    m_menu->addSeparator();
    QAction *debugAction = m_menu->addAction(trUtf8("调试"));
    connect(debugAction, SIGNAL(triggered(bool)), this, SLOT(webDebug()));


    QWebView *view = new QWebView(this);
    view->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    view->installEventFilter(this);
    connect(view, SIGNAL(loadStarted()), this, SLOT(webLoadStarted()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(webLoadFinish(bool)));

    m_inspector = new QWebInspector();
    m_inspector->setPage(view->page());

    this->centralWidget()->layout()->addWidget(view);

    initData();

    printCurrentTime();

    QString indexFile = qApp->applicationDirPath()+"/index.html";
    //    view->load(QUrl("qrc:///index.html"));
    view->load(QUrl::fromLocalFile(indexFile));

    int width = 700;
    int height = 500;

    QRect screenRect = qApp->desktop()->screenGeometry();
    int top = (screenRect.height()-height)/2;
    int left = (screenRect.width()-width)/2;

    QRect r = this->geometry();
    r.setTop(top);
    r.setLeft(left);
    r.setWidth(width);
    r.setHeight(height);

    this->setGeometry(r);
}

MainWindow::~MainWindow()
{
    delete m_inspector;
    delete m_option;
    delete ui;
}

void MainWindow::tutorial()
{
    QVariantMap title;
    title.insert("title", trUtf8("ECharts 入门示例"));
    QVariantMap legend;
    QStringList legendData;
    legendData << trUtf8("销量");
    legend.insert("data", legendData);
    QVariantMap xAxis;
    QStringList xAxisData;
    xAxisData << trUtf8("衬衫")
              << trUtf8("羊毛衫")
              << trUtf8("雪纺衫")
             << trUtf8("裤子")
            << trUtf8("高跟鞋")
           << trUtf8("袜子");
    xAxis.insert("data", xAxisData);

    QVariantMap bar;
    bar.insert("name", trUtf8("销量"));
    bar.insert("type", trUtf8("bar"));
    QVariantList barData;
    barData << 5 << 20 << 36 << 10 << 10 << 20;
    bar.insert("data", barData);
    QVariantList series;
    series.append(bar);

    m_option->empty();
    m_option->setTitle(title);
    m_option->setLegend(legend);
    m_option->setXAxis(xAxis);
    m_option->setSeries(series);

    webReload();
}

void MainWindow::saveResourceFile(const QString &fileName)
{
    QFile f(":/"+fileName);
    if(f.open(QIODevice::ReadOnly))
    {
        QByteArray ba = f.readAll();
        f.close();

        QFile wf(qApp->applicationDirPath()+"/"+fileName);
        if(wf.open(QIODevice::WriteOnly))
        {
            wf.write(ba);
            wf.close();
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    QWebView *view = static_cast<QWebView *>(obj);
    if(view)
    {
        if(QEvent::ContextMenu==event->type())
        {
            QContextMenuEvent *e = static_cast<QContextMenuEvent *>(event);
            m_menu->popup(e->globalPos());
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::webLoadStarted()
{
    printCurrentTime();
}

void MainWindow::echartsInit(QWebView *view, QString divName, QString chartName)
{
    QWebElementCollection list = view->page()->mainFrame()->findAllElements("#"+divName);
    if(0<list.count())
    {
        //        EChartsOption option;
        //        option.emptyBar();
        //        option.empty();
        QString jOption = m_option->toJson();
        qDebug() << jOption;
        QString jsInitDiv = trUtf8(""
                                   "var tmpChart = echarts.init(document.getElementById('tmpDiv'));;"
                                   "var tmpChartOption = %1;"
                                   "tmpChart.setOption(tmpChartOption);"
                                   "").arg(jOption);
        jsInitDiv = jsInitDiv.replace("tmpDiv", divName);
        jsInitDiv = jsInitDiv.replace("tmpChart", chartName);

        view->page()->mainFrame()->evaluateJavaScript(jsInitDiv);
    }
}

void MainWindow::echartsCreateContainer(QWebView *view, QString divName)
{
    QWebElementCollection list = view->page()->mainFrame()->findAllElements("#"+divName);
    if(1>list.count())
    {
        //create div with name
        QString jsCreateDiv = QString(""
                                      "var tmp = document.createElement('div');"
                                      "tmp.id = 'tmp';"
//                                      "tmp.style['width']='%1px';"
//                                      "tmp.style['height']='%2px';"
                                      "tmp.style['width']='100%';"
                                      "tmp.style['height']='100%';"
                                      "document.body.appendChild(tmp);"
                                      "");//.arg(700).arg(400);
        jsCreateDiv = jsCreateDiv.replace("tmp", divName);

        view->page()->mainFrame()->evaluateJavaScript(jsCreateDiv);
    }
}

void MainWindow::webLoadFinish(bool ok)
{
    printCurrentTime();

    if(!ok)
    {
        return;
    }
    QWebView *view = findChild<QWebView *>();
    //enable some javascript function
    QString itemName = "theFirst";
    QString divName = itemName + "Div";
    QString chartName = itemName + "Chart";
    echartsCreateContainer(view, divName);
    echartsInit(view, divName, chartName);

    printCurrentTime();
}

void MainWindow::webReload()
{
    QWebView *view = findChild<QWebView *>();
    if(!view)
    {
        return;
    }

    view->triggerPageAction(QWebPage::Reload);
}

void MainWindow::webDebug()
{
    m_inspector->showMaximized();
    m_inspector->raise();
    m_inspector->activateWindow();
}

void MainWindow::initData()
{
    saveResourceFile("index.html");
    saveResourceFile("echarts.min.js");
    //    saveResourceFile("test.js");
}
