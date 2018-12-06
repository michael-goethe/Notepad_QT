#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include <QHoverEvent>
#include <QEvent>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    saved = false;
    game = true;
    open = new QListWidgetItem;
    save = new QListWidgetItem;
    savedoc = new QListWidgetItem;

    ui->listWidget->addItem("file");
    ui->listWidget->addItem(open);
    open->setText("open");
    ui->listWidget->addItem(save);
    save->setText("save as");
    ui->listWidget->addItem(savedoc);
    savedoc->setText("save");

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(upperletter()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(list()));
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fontchange(QString)));

    QFont font;
    font.setPointSize(10);
    ui->textEdit->setFont(font);
    ui->textEdit->setFocus();

    for(int i= 8; i < 48; i+=2)
        ui->comboBox->addItem(QString::number(i));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fontchange(QString event){
    QFont font;
    font.setPointSize(event.toInt());
    ui->textEdit->selectAll();
    ui->textEdit->setFont(font);
    ui->textEdit->setFocus();
    MainWindow::cursorend();
}

void MainWindow::cursorend(){
    QTextCursor  cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void MainWindow::list(){
    ui->listWidget->resize(ui->listWidget->width(), 30);
    if (ui->listWidget->currentItem() == open){
        ui->listWidget->setCurrentItem(0);
        MainWindow::openas();
    }
    else if (ui->listWidget->currentItem() == save){
        ui->listWidget->setCurrentItem(0);
        MainWindow::saveas();
    }
    else if (ui->listWidget->currentItem() == savedoc){
        ui->listWidget->setCurrentItem(0);
        MainWindow::justsave();
    }
  MainWindow::cursorend();
}

bool MainWindow::event(QEvent * e)
{
    if (e->type() == QEvent::HoverMove)
        if (ui->listWidget->underMouse()){
            ui->listWidget->resize(ui->listWidget->width(), 120);
        }
        else
            ui->listWidget->resize(ui->listWidget->width(), 30);
    else return QWidget::event(e);
    return QWidget::event(e);
}

void MainWindow::justsave(){

    if (!saved)
        savefile  = QFileDialog::getSaveFileName(this, "save a file", "D:/" + savefile + ".txt", "All Files");
    if (savefile.isEmpty())
        return;
    QFile file (savefile);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::saveas()
{
    savefile  = QFileDialog::getSaveFileName(this, "save a file", "D:/" + savefile + ".txt", "All Files");
    if (savefile.isEmpty())
        return;
    else {
        QFile file (savefile);
        MainWindow::filesname(&file);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out (&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
        saved = true;
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->textEdit->resize(width()-40, height()-100);
}

void MainWindow::filesname(QFile * file){
    fileInfo = (file->fileName());
    filename = (fileInfo.fileName());
    ui->label->setText(filename + " - notepad");
}

void MainWindow::openas()
{
    savefile = QFileDialog::getOpenFileName(this, "open a file", "D:/");
    QFile file(savefile);
    MainWindow::filesname(&file);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        return;
    }
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
    saved = true;
}

void MainWindow::upperletter()
{
    if (game){
        QString text = ui->textEdit->toPlainText();
        if (text.length() > 4)
            if (text[text.length() - 5] == '.' && text[text.length() - 4] == 32){
                text[text.length() - 3] = text[text.length() - 3].toUpper();
                game = false;
                ui->textEdit->setText(text);
            }
    }
    else{
        game = true;
        MainWindow::cursorend();
    }
}
