#ifndef GAMESETTINGOBJECT_H
#define GAMESETTINGOBJECT_H
#include "FoolGameApplicationWindow/Files/SettingsStruct.h"
#include <QSettings>

class GameSettingObject : public QObject
{
    Q_OBJECT
private:
    QSettings* m_saver;
    SettingsStruct m_settings;

public:
    explicit GameSettingObject(QObject *parent = nullptr);
    GameSettingObject(const GameSettingObject&);
    ~GameSettingObject();

    DeckType deckType() const { return m_settings.m_deckType; };
    void setDeckType(DeckType t) { m_settings.m_deckType = t; }

    CountOfPlayers countOfPlayers() const { return m_settings.m_countOfPlayers; };
    void setCountOfPlayers(CountOfPlayers t) { m_settings.m_countOfPlayers = t; }

    quint8 rateIndex() const { return m_settings.m_rateIndex; }
    void setRateIndex(quint8 n) { m_settings.m_rateIndex = n; }

    bool trancferableAbility() const { return m_settings.m_trancferableAbility; }
    void setTrancferableAbility(bool n) { m_settings.m_trancferableAbility = n; }

    SettingsStruct allSettings() const { return m_settings; }
};

#endif // GAMESETTINGOBJECT_H
