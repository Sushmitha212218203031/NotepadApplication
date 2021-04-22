#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QFontDialog>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QColorDialog>
#include<QColor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionquit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionsave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionnew_triggered()
{
    file_path="";
    ui->textEdit->setText("");
}

void MainWindow::on_actionopen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionsave_as_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionselect_font_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionAbout_qt_triggered()
{
    QString about_text;
    about_text   = "Author   : somebody";
    about_text  += "date     :15/04/2021";
    about_text  += "(C) notepad (R)";

    QMessageBox::about(this,"about notepad",about_text);


}

void MainWindow::on_actionprint_triggered()
{
  QPrinter printer;
  printer.setPrinterName("desired printer name");
  QPrintDialog dialog(&printer,this);
  if(dialog.exec() == QDialog::Rejected) return;
  ui->textEdit->print(&printer);
}

void MainWindow::on_actionbold_triggered()
{
   QFont font;
   font.setWeight(QFont::Bold);
   ui->textEdit->setFont(font);
}

void MainWindow::on_actionitalic_triggered()
{
    QFont font;
    font.setItalic(QFont::Cursive);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionunderline_triggered()
{
    QFont font;
    font.setUnderline(QFont::UnderlineResolved);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionfont_background_colour_triggered()
{
    QColor color =QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()) {
        ui->textEdit->setTextBackgroundColor(color);
    }

}

void MainWindow::on_actionfont_colour_triggered()
{
    QColor color =QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()) {
        ui->textEdit->setTextColor(color);
    }
}
