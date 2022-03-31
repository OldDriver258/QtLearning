#include "mainwindow.h"
#include <QApplication>

/*
 * 默认的 Qt 环境不支持 openssl 库
 * 根据博客 https://blog.csdn.net/qq_39486027/article/details/106449384?spm=1001.2101.3001.6650.4&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-4.pc_relevant_antiscanv2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-4.pc_relevant_antiscanv2&utm_relevant_index=5
 * 添加库到对应目录后正常
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     qDebug() << "QSslSocket=" << QSslSocket::sslLibraryBuildVersionString();
     qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    MainWindow w;
    w.show();
    return a.exec();
}
