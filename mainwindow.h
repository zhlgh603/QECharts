#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initData();

    void saveResourceFile(const QString &fileName);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
