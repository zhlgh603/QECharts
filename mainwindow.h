#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QMenu;
class QWebView;
class QWebInspector;
class EChartsOption;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tutorial();

protected:
    void initData();
    void saveResourceFile(const QString &fileName);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

//echarts function
protected:
    void echartsCreateContainer(QWebView *view, QString divName);
    void echartsInit(QWebView *view, QString divName, QString chartName);

    void printCurrentTime();
    
protected slots:
    void webLoadStarted();
    void webLoadFinish(bool ok);
    void webReload();
    void webDebug();

private:
    EChartsOption *m_option;
    QMenu *m_menu;
    QWebInspector *m_inspector;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
