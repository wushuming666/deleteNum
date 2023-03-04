#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <vector>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openInFile();

    void openOutFile();

    void startChange();

private:
    Ui::MainWindow *ui;
    std::vector<QString> vec;
    QString solve(QString &line);
};

#endif // MAINWINDOW_H
