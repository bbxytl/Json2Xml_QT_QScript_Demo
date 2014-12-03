#include "mainwindow.h"


MainWindow::MainWindow(QString strText,QWidget *parent)
    : QMainWindow(parent)
{
   m_text=strText;
   m_te=new QTextEdit(this);
   m_te->setText(m_text);
   this->setCentralWidget(m_te);
}

MainWindow::~MainWindow()
{
    delete m_te;
}

void MainWindow::setText(QString strText)
{
    m_text=m_text+"\n"+strText;
    m_te->setText(m_text);
}
