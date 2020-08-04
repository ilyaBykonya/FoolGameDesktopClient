#include "GameUserInformation.h"


GameUserInformation::GameUserInformation(UserID id, const QString& name, const QPixmap& avatar, QObject* parent)
    :QObject{ parent },
     m_userID{ id },
     m_userName{ name },
     m_userAvatar{ avatar }
    {
    }


UserID GameUserInformation::userID() const
{
    return m_userID;
}
const QString& GameUserInformation::userName() const
{
    return m_userName;
}
const QPixmap& GameUserInformation::userAvatar() const
{
    return m_userAvatar;
}
