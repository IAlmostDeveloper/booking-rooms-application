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
    virtual ~HotelsManager();
    Q_INVOKABLE void getParsedHotelsList();
    Q_INVOKABLE void addHotelToDatabase(const QString& name, const QString& address,
                                        const QString& description, bool available);
    Q_INVOKABLE void editHotel(int id, const QString& name, const QString& address,
                               const QString& description, bool available);
    Q_INVOKABLE void deleteHotel(int id);

    HotelsModel* hotelsModel();
    void setHotelsModel(HotelsModel* hotelsModel);
    void setNewSession(const QString& token, const QString& login, bool isAdmin);

signals:
    void hotelsModelChanged();
    void hotelsDataReceived();
    void hotelsDataReceiveError(const QString& error);
    void addHotelSuccess();
    void addHotelError(const QString& error);
    void editHotelSuccess();
    void editHotelError(const QString& error);
    void deleteHotelSuccess();
    void deleteHotelError(const QString& error);

private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    HotelsModel* m_hotelsModel;
};

#endif // HOTELSMANAGER_HPP
