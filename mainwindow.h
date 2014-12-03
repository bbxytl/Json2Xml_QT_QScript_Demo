#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString strText, QWidget *parent = 0);
    ~MainWindow();

    void setText(QString strText);

private:
    QTextEdit *m_te;
    QString m_text;
};

#endif // MAINWINDOW_H
