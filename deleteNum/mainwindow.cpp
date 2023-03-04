#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit1->setText("D:\\in.txt");
    ui->lineEdit2->setText("D:\\out.txt");
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(openInFile()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(openOutFile()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startChange()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openInFile()
{
    qDebug() << "openInFIle";
    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", "C:\\");
    ui->lineEdit1->setText(mFolderPath);
}

void MainWindow::openOutFile()
{
    qDebug() << "openOutFile";
    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", "C:\\");
    ui->lineEdit2->setText(mFolderPath);
}

void MainWindow::startChange()
{
    qDebug() << "startChange";

    // 将待打开的文件名写入
    QString inFileName = ui->lineEdit1->text();
    QString outFileName = ui->lineEdit2->text();
    QFile inFile(inFileName), outFile(outFileName);

    // inFile只读 outFile只写
    // 文件不存在 或者 打开失败
    if (!inFile.exists() || !outFile.exists() || \
            !inFile.open(QIODevice::ReadOnly | QIODevice::Text) || \
            !outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::information(NULL, "错误!", "打开文件失败");
        return;
    }

    // 每读一行in, 处理后往out里面写
    QString line;
    QTextStream in(&inFile); // 用文件构造流
    line = in.readLine();    // 读取一行
    vec.push_back(solve(line));
    while (!line.isNull())
    {
        line = in.readLine(); // 循环读取下一行
        vec.push_back(solve(line));
    }

    // 将vec的内容写入outFile
    QTextStream out(&outFile); //文件流写入
    for (QString words : vec)
    {
        out << words << "\n";
    }

    // 关闭in和out文件
    inFile.close();
    outFile.close();

    // 提示用户已完成
    QMessageBox::information(NULL, "成功!", "替换完成");
}

// 将第一个空格及之前的删去
QString MainWindow::solve(QString &line)
{
    QString s = line;
    if (s.size() && !s[0].isNumber()) return s;
    int i = 0;
    for (i = 0; i < s.size(); i ++)
    {
        if (s[i] == ' ')
            break;
    }
    // i 的下标是空格
    s = s.mid(i+1);
    return s;
}
