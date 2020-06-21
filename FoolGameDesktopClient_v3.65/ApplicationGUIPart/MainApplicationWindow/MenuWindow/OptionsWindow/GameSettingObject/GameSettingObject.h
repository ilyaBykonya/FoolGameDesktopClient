#ifndef GAMESETTINGOBJECT_H
#define GAMESETTINGOBJECT_H
#include <QSettings>

class GameSettingObject : public QObject
{
    Q_OBJECT
private:
    enum DeckType
    {
        Deck_24 = 0x01,
        Deck_36 = 0x02,
        Deck_52 = 0x04
    };
    enum CountPlayers
    {
        Players_2 = 0x01,
        Players_3 = 0x02,
        Players_4 = 0x04,
        Players_5 = 0x08,
        Players_6 = 0x10
    };

    QSettings* m_settings;
    quint8 m_deckType;
    quint8 m_countOfPlayers;
    bool m_trancferableAbility;

public:
    explicit GameSettingObject(QObject *parent = nullptr);
    ~GameSettingObject();

    quint8 deckTypeAllFlags() const { return m_deckType; }
    bool deckTypeFlag_24() const { return (m_deckType & DeckType::Deck_24); }
    void setDeckTypeFlag_24(bool f)
    {
        if(f)
            m_deckType |= DeckType::Deck_24;
        else
            m_deckType &= ~DeckType::Deck_24;
    }
    bool deckTypeFlag_36() const { return (m_deckType & DeckType::Deck_36); }
    void setDeckTypeFlag_36(bool f)
    {
        if(f)
            m_deckType |= DeckType::Deck_36;
        else
            m_deckType &= ~DeckType::Deck_36;
    }
    bool deckTypeFlag_52() const { return (m_deckType & DeckType::Deck_52); }
    void setDeckTypeFlag_52(bool f)
    {
        if(f)
            m_deckType |= DeckType::Deck_52;
        else
            m_deckType &= ~DeckType::Deck_52;
    }

    quint8 countOfPlayersAllFlags() const { return m_countOfPlayers; }
    bool playersCountFlag_2() const { return (m_countOfPlayers & CountPlayers::Players_2); }
    void setPlayerCountFlag_2(bool f)
    {
        if(f)
            m_countOfPlayers |= CountPlayers::Players_2;
        else
            m_countOfPlayers &= ~CountPlayers::Players_2;
    }
    bool playersCountFlag_3() const { return (m_countOfPlayers & CountPlayers::Players_3); }
    void setPlayerCountFlag_3(bool f)
    {
        if(f)
            m_countOfPlayers |= CountPlayers::Players_3;
        else
            m_countOfPlayers &= ~CountPlayers::Players_3;
    }
    bool playersCountFlag_4() const { return (m_countOfPlayers & CountPlayers::Players_4); }
    void setPlayerCountFlag_4(bool f)
    {
        if(f)
            m_countOfPlayers |= CountPlayers::Players_4;
        else
            m_countOfPlayers &= ~CountPlayers::Players_4;
    }
    bool playersCountFlag_5() const { return (m_countOfPlayers & CountPlayers::Players_5); }
    void setPlayerCountFlag_5(bool f)
    {
        if(f)
            m_countOfPlayers |= CountPlayers::Players_5;
        else
            m_countOfPlayers &= ~CountPlayers::Players_5;
    }
    bool playersCountFlag_6() const { return (m_countOfPlayers & CountPlayers::Players_6); }
    void setPlayerCountFlag_6(bool f)
    {
        if(f)
            m_countOfPlayers |= CountPlayers::Players_6;
        else
            m_countOfPlayers &= ~CountPlayers::Players_6;
    }

    bool trancferableAbility() const { return m_trancferableAbility; }
    void setTrancferableAbility(bool n) { m_trancferableAbility = n; }

};

#endif // GAMESETTINGOBJECT_H
