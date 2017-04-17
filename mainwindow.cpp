#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open File"),
                                            QString(),
                                            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Couled not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
//        QFileInfo fileInfo(fileName);
//        ui->statusBar->showMessage(fileInfo.created().toString());
        ui->statusBar->showMessage(QFileInfo(fileName).lastModified().toString());
        setWindowTitle(fileName);
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save File"),
                                                QString(),
                                                tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    }
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open((QIODevice::WriteOnly))) {
//            error message
        } else {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
        ui->statusBar->showMessage(QFileInfo(fileName).lastModified().toString());
        setWindowTitle(fileName);
    }
}

void MainWindow::on_actionClose_triggered()
{
    ui->textEdit->clear();
    fileName.clear();
    setWindowTitle(fileName);
//    ui->statusBar->showMessage("");
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor();
//    ui->textEdit->setTextBackgroundColor(color);
//    ui->textEdit->setTextColor(color);
//    ui->textEdit->setTextBackgroundColor(color);
    ui->textEdit->setStyleSheet("QTextEdit { background:" + color.name() + "}");
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if (ok) {
        ui->textEdit->setCurrentFont(font);
    }
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    fileName.clear();
    setWindowTitle(fileName);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(ui->textEdit, "About", "Author: Daniel Lee");
}
