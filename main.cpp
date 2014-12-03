#include "mainwindow.h"
#include <QApplication>
#include "qscriptjson.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("程序开始。。。");
    w.show();

    dbg<<"This is a Test !";
    QScriptJson qsj("D:\\json.xml");
    qsj.write2File();

    w.setText("程序已运行完成！\n\n关闭窗口退出程序。。。");
    return a.exec();
}
