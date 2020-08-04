#pragma once
#include <QObject>
#include "TypesAliases.h"
enum DeckType
{
    Deck_24 = 0x01,
    Deck_36 = 0x02,
    Deck_52 = 0x04
};
enum CountOfPlayers
{
    Players_2 = 0x01,
    Players_3 = 0x02,
    Players_4 = 0x04,
    Players_5 = 0x08,
    Players_6 = 0x10
};


const quint8 countOfTransactons = 8;
const Cash transactions[countOfTransactons] =
{
    0,
    100,
    200,
    500,
    1000,
    2500,
    5000,
    10000
};


struct SettingsStruct
{
    DeckType m_deckType;
    CountOfPlayers m_countOfPlayers;
    bool m_trancferableAbility;
    quint8 m_rateIndex;
};



