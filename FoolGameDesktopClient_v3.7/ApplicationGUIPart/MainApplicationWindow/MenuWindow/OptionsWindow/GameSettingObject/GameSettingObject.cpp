#include "GameSettingObject.h"

GameSettingObject::GameSettingObject(QObject *parent)
    :QObject{ parent },
     m_saver{ new QSettings("TEST", "FoolGameDesktopClient", this) }
    {
        m_saver->beginGroup("/game_settings");
            m_settings.m_deckType = m_saver->value("DeckType", 7).toInt();//7 == 00000111 т.е. по-умолчанию все колоды активны
            m_settings.m_countOfPlayers = m_saver->value("PlayersCount", 31).toInt();//31 == 00011111 т.е. любое кол-во игроков
            m_settings.m_trancferableAbility = m_saver->value("TrancferableAbility", false).toBool();
        m_saver->endGroup();
    }

GameSettingObject::~GameSettingObject()
{
    m_saver->beginGroup("/game_settings");
        m_saver->setValue("/DeckType", m_settings.m_deckType);
        m_saver->setValue("/PlayersCount", m_settings.m_countOfPlayers);
        m_saver->setValue("/TrancferableAbility", m_settings.m_trancferableAbility);
    m_saver->endGroup();
}
