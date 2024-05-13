#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->statusbar->hide();

    ui->PassageWords->setStyleSheet("font-family: Baskerville Old Face, sans-serif; font-size: 14px; font-weight: bold; letter-spacing: 1px;");
    ui->DictionaryWords->setStyleSheet("font-family: Baskerville Old Face, sans-serif; font-size: 14px; font-weight: bold; letter-spacing: 1px;");
    ui->ErrorLogWords->setStyleSheet("font-family: Baskerville Old Face, sans-serif; font-size: 14px; font-weight: bold; letter-spacing: 1px;");

    ui->DictionaryWords->setStyleSheet(" border: 2px solid black; border-radius: 10px; padding: 5px;");
    ui->PassageWords->setStyleSheet(" border: 2px solid black; border-radius: 10px; padding: 5px;");
    ui->ErrorLogWords->setStyleSheet(" border: 2px solid white; border-radius: 10px; padding: 5px;");
    ui->ErrorLogWords->setReadOnly(true);

    QFont q1 = ui->DictionaryWords->font();
    q1.setPointSize(12);
    q1.setFamily("Baskerville Old Face, sans-serif");
    ui->DictionaryWords->setFont(q1);
    ui->PassageWords->setFont(q1);
    ui->ErrorLogWords->setFont(q1);

    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "background-color: Purple;"
        "border: 5px solid black;"
        "color: white;"
        "text-align: center;"
        "font-size: 25px;"
        "margin: 4px 2px;"
        "border-radius: 10px;"
        "font-family: Baskerville Old Face, sans-serif;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049; /* Darker Green */"
        "}"
        "QPushButton:pressed {"
        "    background-color: #4CAF50; /* Green */"
        "    border-style: inset;"
        "}"
        );

}


MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked(){

    std::string dictionary = ui->DictionaryWords->toPlainText().toStdString();
    std::string passage = ui->PassageWords->toPlainText().toStdString();

    SpellChecker sc(dictionary, passage);
    auto misspellings = sc.checkSpelling();

    if(misspellings.size() == 0){
        ui->ErrorLogWords->setPlainText("All good!");
        return;
    }

    QString output = "Spelling Errors:\n";
    for(int i =0 ; i<misspellings.size(); i++){

        output += QString::fromStdString("\'" + misspellings[i] + "\'");
        if(i < misspellings.size() - 1){
            output += ", ";
        }
    }

    ui->ErrorLogWords->setPlainText(output);

}
