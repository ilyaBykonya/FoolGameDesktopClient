#include "ThisUserFullInformation.h"



ThisUserFullInformation::ThisUserFullInformation(UserID id, const QString& name, Cash noDepositCash, Cash depositCash, quint32 countOfGames, quint32 raitingPoints, const QPixmap& userAvatar,  QObject* parent)
    :QObject{ parent },
     m_ID{ id },
     m_name{ name },
     m_noDepositCash{ noDepositCash },
     m_depositCash{ depositCash },
     m_countOfGames{ countOfGames },
     m_raitingPoints{ raitingPoints },
     m_userAvatar{ userAvatar }
    {
    }

UserID ThisUserFullInformation::id() const
{
    return m_ID;
}
const QString& ThisUserFullInformation::name() const
{
    return m_name;
}
Cash ThisUserFullInformation::dollars() const
{
    return m_noDepositCash;
}
Cash ThisUserFullInformation::tokens() const
{
    return m_depositCash;
}
quint32 ThisUserFullInformation::countOfGames() const
{
    return m_countOfGames;
}
quint32 ThisUserFullInformation::raitingPoints() const
{
    return m_raitingPoints;
}
const QPixmap& ThisUserFullInformation::userAvatar() const
{
    return m_userAvatar;
}




void ThisUserFullInformation::setName(const QString& newName)
{
    m_name = newName;
}
void ThisUserFullInformation::setDollars(Cash cash)
{
    m_noDepositCash = cash;
}
void ThisUserFullInformation::setTokens(Cash cash)
{
    m_depositCash = cash;
}
void ThisUserFullInformation::setCountOfGames(quint32 countOfGames)
{
    m_countOfGames = countOfGames;
}
void ThisUserFullInformation::setRaitingPoints(quint32 raitingPoints)
{
    m_raitingPoints = raitingPoints;
}
void ThisUserFullInformation::setUserAvatar(const QPixmap& newAvatar)
{
    m_userAvatar = newAvatar;
}
