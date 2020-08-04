#pragma once
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include <QPixmap>

class GameUserInformation: public QObject
{
private:
    UserID m_userID;
    QString m_userName;
    QPixmap m_userAvatar;

public:
    explicit GameUserInformation(UserID, const QString&, const QPixmap&, QObject* = nullptr);

    UserID userID() const;
    const QString& userName() const;
    const QPixmap& userAvatar() const;
};
