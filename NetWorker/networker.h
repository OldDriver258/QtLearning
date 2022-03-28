#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>
#include <QNetworkReply>


class NetWorker : public QObject
{
    Q_OBJECT
public:
    ~NetWorker();

    static NetWorker *instance();
    void get(const QString &url);

signals:
    void finished(QNetworkReply *reply);

private:
    /*
     * 这里声明了一个NetWorker的内部类，然后声明了这个内部类的 d 指针
     * 它的存在于 C++ 程序的编译有关, 在 C++ 中，保持二进制兼容性非常重要
     * 如果你能够保持二进制兼容，则当以后升级库代码时，用户不需要重新编译自己的程序即可直接运行
     * 如果你使用 Qt5.0 编译了一个程序，这个程序不需要重新编译就可以运行在 Qt5.1 下，这就是二进制兼容
     * 果不需要修改源代码，但是必须重新编译才能运行，则是源代码兼容
     * 如果必须修改源代码并且再经过编译，例如从 Qt4 升级到 Qt5，则称二者是不兼容的
     */
    class Private;
    friend class Private;
    Private *d;

    explicit NetWorker(QObject *parent = 0);
    Q_DISABLE_COPY(NetWorker); // 禁止对类进行复制
};


class NetWorker::Private
{
public:
    Private(NetWorker *q) :
        manager(new QNetworkAccessManager(q))
    {
    }

    QNetworkAccessManager *manager;
};

#endif // NETWORKER_H
