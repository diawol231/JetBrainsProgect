#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include "KMP.h"
#include <qt_windows.h>
#include <QTextCursor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    edit = ui->textEdit;       //указатели на наши объекты на экране
    pb2 = ui->pushButton_2;
    pb3 = ui->pushButton_3;
    ledit = ui->lineEdit;


    ui->label->setText("WELCOME!!");
    ui->label_2->setText("Hi! It's my GUI for JetBrain Intership, this text line for searching");
    ui->label_3->setText("in dictionary works dynamically when editing text, but i add and button for it)");

    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::run);                //запуск последовательных процессов после изменения текста в строке lineEdit
    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::FindProcess);
    connect(ledit, &QLineEdit::textChanged, this, &MainWindow::stop);

    connect(pb2, &QPushButton::clicked, this, &MainWindow::run);                    //запуск последовательных процессов после нажатия кнопки
    connect(pb2, &QPushButton::clicked, this, &MainWindow::FindProcess);
    connect(pb2, &QPushButton::clicked, this, &MainWindow::stop);

    connect(pb3,  &QPushButton::clicked, this,&MainWindow::stopWork);               //принудительная остановка процесса вывода на экран textEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //выход из программы
{
    ExitProcess(244);
}

void MainWindow::stopWork(){    //уведомляет о остановке процесса и его завешении
    if(ui->label->text() != "DONE!!")
        ui->label->setText("STOP!");
    process = false;
}

void MainWindow::run(){       //уведомляет, что процесс уже запущен
    process = true;
    ui->label->setText("WAIT, PLEASE!)");
}

void MainWindow::stop(){        //уведомляет, что процесс  завершился
    if(ui->label->text() != "STOP!")
        ui->label->setText("DONE!!");
    process = false;
}

void MainWindow::FindProcess(){
        QString file_name = "words.txt";
        QString arg1 = ui->lineEdit->text();
        QString buff_word, buff_arg;
        KMP kmp;  //создаем объект класса

        ui->textEdit->clear();   //очистка поля для поиска

        QFile file(file_name);  //объект файла

        if(!file.open(QIODevice::ReadOnly)){     //проверка на открытие
            QMessageBox::warning(this, "warning!", "File not open");
            return;
        }

        QTextStream in(&file);    //для считывания слов из файла

        while(!in.atEnd()){

            if(!process){         //для прерывания недоисполняемых сигналов, если их прервали новым процессом.
                process = true;
                return;
            }

            QString word;
            in>>word;            //берем слово из строки

            bool succsess = kmp.kmpCompare(word, arg1); //идем сравнивать с помощью алгоритма КМП

            if (succsess){                  //если удачно, выводим слово
                ui->textEdit->append(word);
            }
            qApp->processEvents();
        }
        file.close();

        ui->textEdit->moveCursor(QTextCursor::Start);  //переводим каретку в исходное положение

        if(ui->textEdit->toPlainText().isEmpty())      //если наше поле textEdit так и осталось пустым
            ui->textEdit->setText("Nothing found =(");
}
