#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWebView>
#include <QWebSettings>
#include <QUrl>
#include <QRect>
#include <QDesktopWidget>

#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebView *view = new QWebView(this);
    view->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(view);

//    this->setLayout(layout);

    this->setCentralWidget(view);

    initData();

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
    delete ui;
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

void MainWindow::initData()
{
    saveResourceFile("index.html");
    saveResourceFile("echarts.min.js");
}
