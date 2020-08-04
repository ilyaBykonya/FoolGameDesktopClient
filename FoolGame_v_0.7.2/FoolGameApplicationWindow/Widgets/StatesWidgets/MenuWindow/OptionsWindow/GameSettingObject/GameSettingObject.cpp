#include "GameSettingObject.h"

GameSettingObject::GameSettingObject(QObject *parent)
    :QObject{ parent },
     m_saver{ new QSettings("TEST", "FoolGameDesktopClient", this) }
    {
        m_saver->beginGroup("/game_settings");
            m_settings.m_deckType = DeckType(m_saver->value("DeckType", Deck_24).toInt());//1 == 00000001 т.е. по-умолчанию активна колода на 24 карты
            m_settings.m_countOfPlayers = CountOfPlayers(m_saver->value("PlayersCount", Players_2).toInt());//1 == 00000001 т.е. 2 игрока
            m_settings.m_rateIndex = m_saver->value("RateIndex", 0).toInt();
            m_settings.m_trancferableAbility = m_saver->value("TrancferableAbility", true).toBool();
        m_saver->endGroup();
    }

GameSettingObject::~GameSettingObject()
{
    m_saver->beginGroup("/game_settings");
        m_saver->setValue("/DeckType", m_settings.m_deckType);
        m_saver->setValue("/PlayersCount", m_settings.m_countOfPlayers);
        m_saver->setValue("/RateIndex", m_settings.m_rateIndex);
        m_saver->setValue("/TrancferableAbility", m_settings.m_trancferableAbility);
    m_saver->endGroup();
}
