#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H
#include <QPainter>
#include <QGroupBox>
#include <QScrollBar>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include "GameSettingObject/GameSettingObject.h"

class OptionsWindow : public QWidget
{
    Q_OBJECT
private:

    GameSettingObject* m_gameSettingsController;

    QCheckBox* m_deck_24;
    QCheckBox* m_deck_36;
    QCheckBox* m_deck_52;

    QCheckBox* m_players_2;
    QCheckBox* m_players_3;
    QCheckBox* m_players_4;
    QCheckBox* m_players_5;
    QCheckBox* m_players_6;

    QRadioButton* m_trancferableAbilityButton;

public:
    explicit OptionsWindow(QWidget *parent = nullptr);

    quint8 deckTypeAllFlags() const { return m_gameSettingsController->deckTypeAllFlags(); }
    quint8 countOfPlayersAllFlags() const { return m_gameSettingsController->countOfPlayersAllFlags(); }
    bool trancferableAbility() const { return m_gameSettingsController->trancferableAbility(); }

    SettingsStruct allSettings() const { return m_gameSettingsController->allSettings(); }
protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
};

#endif // OPTIONSWINDOW_H
