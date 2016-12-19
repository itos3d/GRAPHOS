#ifndef WAITFORRESULTSCLIENT_H
#define WAITFORRESULTSCLIENT_H

#include <QObject>

class WaitForResultsClient : public QObject
{
    Q_OBJECT
public:
    explicit WaitForResultsClient(QObject *parent = 0);

signals:

public slots:
    void onFileCreated(QString path);

};

#endif // WAITFORRESULTSCLIENT_H
