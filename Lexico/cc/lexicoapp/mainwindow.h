#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

QT_BEGIN_NAMESPACE

const int TABLE_SIZE=1000;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class DictionaryEntry
{
    public:
        DictionaryEntry();
        DictionaryEntry(QString entryline);

    private:
        QString chin;
        QString spain;
        int readtimes;
        int hittimes;

};

class Dictionary
{
    public:
    Dictionary(QString filename);
    Dictionary();
    void OrderTrain();
    void RandomTrain();
    private:
    DictionaryEntry EntryTable[100];
    void Statistic();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartButton_clicked();

    void on_QuitButton_clicked();

    void on_InputLine_returnPressed();

    void on_OrderButton_clicked();

    void on_Fileline_returnPressed();

private:
    Ui::MainWindow *ui;
    QString output;
    QString input;

};
#endif // MAINWINDOW_H
