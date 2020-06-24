#include "UserInformation.h"

UserInformation::UserInformation(UserID id, const QString& name)
    :m_userID{ id },
     m_userName{ name }
    {
    }


UserID UserInformation::userID() const
{
    return m_userID;
}
const QString& UserInformation::userName() const
{
    return m_userName;
}
