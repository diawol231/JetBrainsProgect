#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include "KMP.h"
#include <qt_windows.h>

QString file_name = "words.txt";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    edit = ui->textEdit;
    pb2 = ui->pushButton_2;
    pb3 = ui->pushButton_3;
    ledit = ui->lineEdit;


    ui->label->setText("WELCOME!!");
    ui->label_2->setText("Hi! It's my GUI for JetBrain Intership, this text line for searching");
    ui->label_3->setText("in dictionary works dynamically when editing text, but i add and button for it)");

    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::run);
    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::FindProcess);
    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::stop);

    connect(pb2, &QPushButton::clicked, this, &MainWindow::run);
    connect(pb2, &QPushButton::clicked, this, &MainWindow::FindProcess);
    connect(pb2, &QPushButton::clicked, this, &MainWindow::stop);

    connect(pb3,  &QPushButton::clicked, this,&MainWindow::stopWork);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ExitProcess(244);
}

void MainWindow::stopWork(){
    if(ui->label->text() != "DONE!!")
        ui->label->setText("STOP!");
    process = false;
}

void MainWindow::run(){
    process = true;
    ui->label->setText("WAIT, PLEASE!)");
}

void MainWindow::stop(){
    if(ui->label->text() != "STOP!")
        ui->label->setText("DONE!!");
    process = false;
}

void MainWindow::FindProcess(){
        QString arg1 = ui->lineEdit->text();
        QString buff_word, buff_arg;
        KMP kmp;
        QString proc = "Processing";

        ui->textEdit->clear();

        QFile file(file_name);

        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this, "warning!", "File not open");
            return;
        }

        QTextStream in(&file);

        while(!in.atEnd()){
            if(!process){
                process = true;
                return;
            }

            QString word;
            in>>word;
            buff_word = word.toLower();
            buff_arg = arg1.toLower();

            bool succsess = kmp.kmpCompare(buff_word, buff_arg);

            if (succsess){
                ui->textEdit->append(word);
            }
            qApp->processEvents();
        }

        file.close();

        if(ui->textEdit->toPlainText().isEmpty())
            ui->textEdit->setText("Nothing found =(");
}
