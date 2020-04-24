#ifndef RENTSMODEL_HPP
#define RENTSMODEL_HPP

#include <QObject>
#include <QNetworkAccessManager>

class RentsModel : public QObject
{
    Q_OBJECT
public:
    explicit RentsModel(QObject *parent = nullptr);
    Q_INVOKABLE void getUserRents(const QString& login);

signals:
    void rentsDataReceived(const QList<QObject*>& rentsData);
    void rentsDataReceiveError(const QString& error);
    void addRentSuccess();
    void addRentError(const QString& error);
private:
    QList<QObject*> m_rents;
    QNetworkAccessManager m_net;
};

#endif // RENTSMODEL_HPP
