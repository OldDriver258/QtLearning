#include "networker.h"

NetWorker::NetWorker(QObject *parent) :
    QObject(parent),
    d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished,
            this,       &NetWorker::finished);
}

NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}

NetWorker *NetWorker::instance()
{
    static NetWorker netWorker;
    return &netWorker;
}

/*
 * 将用户的 url 给底层的 QNetworkAccessManager
 */
void NetWorker::get(const QString &url)
{
    d->manager->get(QNetworkRequest(QUrl(url)));
}


