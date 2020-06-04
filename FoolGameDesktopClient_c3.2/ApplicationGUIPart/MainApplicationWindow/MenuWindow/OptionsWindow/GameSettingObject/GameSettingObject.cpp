#include "GameSettingObject.h"

GameSettingObject::GameSettingObject(QObject *parent)
    :QObject{ parent },
     m_settings{ new QSettings("TEST", "FoolGameDesktopClient", this) }
    {
        m_settings->beginGroup("/game_settings");
            m_deckType = m_settings->value("DeckType", 7).toInt();//7 == 00000111 т.е. по-умолчанию все колоды активны
            m_countOfPlayers = m_settings->value("PlayersCount", 31).toInt();//31 == 00011111 т.е. любое кол-во игроков
            m_realCash = m_settings->value("RealCash", false).toBool();
        m_settings->endGroup();
    }

GameSettingObject::~GameSettingObject()
{
    m_settings->beginGroup("/game_settings");
        m_settings->setValue("/DeckType", m_deckType);
        m_settings->setValue("/PlayersCount", m_countOfPlayers);
        m_settings->setValue("/RealCash", m_realCash);
    m_settings->endGroup();
}
