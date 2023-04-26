#include "mainwindow.h"
#include "./ui_mainwindow.h"

const int cacheline = 100;
DictionaryEntry::DictionaryEntry()
{

}

DictionaryEntry::DictionaryEntry(QString entryline)
{
    QStringList entrylist  = entryline.split("\t");
    int listsize = entrylist.size();
    spain = entrylist[0];
    chin = entrylist[listsize-1];
        for(int i=1;i<listsize-1;i++)
        {
           spain+=entrylist[i];
        }

    readtimes= 0;
    hittimes = 0;

    qDebug() << spain <<chin ;
}

Dictionary::Dictionary()
{

}
Dictionary::Dictionary(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    in.setCodec("UTF-8");
    int lineid = 0 ;
    while (!in.atEnd()&&lineid<cacheline)
    {
        QString line = in.readLine();      //整行读取
        qDebug() << line;
        DictionaryEntry EntryT(line);
        lineid+=1;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_StartButton_clicked()
{

}


void MainWindow::on_QuitButton_clicked()
{
    exit(0);
}



void MainWindow::on_InputLine_returnPressed()
{
    input = ui->InputLine->text();
     ui->OutputLine->setText(input);
}


void MainWindow::on_OrderButton_clicked()
{
    QString outputs("examen para áéíóú");
    ui->QuestionLine->setText(outputs);
}
//D:\GitHub\CIntellifusion\Lexico\1.txt

void MainWindow::on_Fileline_returnPressed()
{
    // choose a new file
    QString filename = ui->Fileline->text();
    Dictionary dic(filename);
}

