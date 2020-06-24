#pragma once
#include <QDataStream>
#include "TypesAliases.h"
class UserInformation
{
private:
    UserID m_userID;
    QString m_userName;

public:
    explicit UserInformation(UserID, const QString&);

    UserID userID() const;
    const QString& userName() const;
};

