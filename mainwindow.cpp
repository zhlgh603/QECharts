#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWebView>
#include <QWebSettings>
#include <QUrl>

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

    view->load(QUrl("qrc:///index.html"));

    this->setGeometry(0, 0, 700, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}
