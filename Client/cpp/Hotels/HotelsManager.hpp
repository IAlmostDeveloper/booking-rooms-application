#ifndef HOTELSMANAGER_HPP
#define HOTELSMANAGER_HPP

#include <QNetworkAccessManager>
#include "Hotelsmodel.hpp"
#include "../Session.hpp"

class HotelsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HotelsModel* hotelsModel READ hotelsModel WRITE setHotelsModel NOTIFY hotelsModelChanged)
public:
    explicit HotelsManager(Session* session = nullptr);
    Q_INVOKABLE void getParsedHotelsList();
    Q_INVOKABLE void addHotelToDatabase(const QString& name, const QString& address,
                                        const QString& description, bool available);
    HotelsModel* hotelsModel();
    void setHotelsModel(HotelsModel* hotelsModel);
    Q_INVOKABLE void setNewHotelsModel();
    void setNewSession(const QString& token, const QString& login, bool isAdmin);

signals:
    void clearHotelsModel();
    void hotelsModelChanged();
    void hotelsDataReceived();
    void hotelsDataReceiveError(const QString& error);
    void addHotelSuccess();
    void addHotelError(const QString& error);

private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    HotelsModel* m_hotelsModel;
};

#endif // HOTELSMANAGER_HPP
