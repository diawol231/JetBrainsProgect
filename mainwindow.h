#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QThread>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTextEdit *edit;
    QPushButton *pb2,*pb3;
    QLineEdit *ledit;
    QProgressBar *bar;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void stop();
    void run();
    void FindProcess();
    void stopWork();

private:
    Ui::MainWindow *ui;
    volatile bool process = true;
    QThread *thread1;
    QThread *thread2;

};
#endif // MAINWINDOW_H
