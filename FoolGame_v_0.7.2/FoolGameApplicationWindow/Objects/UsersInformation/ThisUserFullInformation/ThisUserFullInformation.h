#pragma once
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include <QPixmap>
#include <QObject>

class ThisUserFullInformation : public QObject
{
    Q_OBJECT
private:
    UserID m_ID;
    QString m_name;
    Cash m_noDepositCash;
    Cash m_depositCash;
    quint32 m_countOfGames;
    quint32 m_raitingPoints;
    QPixmap m_userAvatar;

public:
    explicit ThisUserFullInformation(UserID, const QString&, Cash, Cash, quint32, quint32, const QPixmap&, QObject *parent = nullptr);

    UserID id() const;
    const QString& name() const;
    Cash dollars() const;
    Cash tokens() const;
    quint32 countOfGames() const;
    quint32 raitingPoints() const;
    const QPixmap& userAvatar() const;

public slots:
    void setName(const QString&);
    void setDollars(Cash);
    void setTokens(Cash);
    void setCountOfGames(quint32);
    void setRaitingPoints(quint32);
    void setUserAvatar(const QPixmap&);
};


