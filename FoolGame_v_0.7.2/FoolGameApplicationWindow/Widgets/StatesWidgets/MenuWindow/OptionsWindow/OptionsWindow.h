#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H
#include "GameSettingObject/GameSettingObject.h"
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QPainter>
#include <QLabel>

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


    QLabel* m_pixmapScreen;
    QPushButton* m_changeNewAvatarButton;


    QComboBox* m_rateController;


public:
    explicit OptionsWindow(const QPixmap&, QWidget *parent = nullptr);
    SettingsStruct allSettings() const { return m_gameSettingsController->allSettings(); }

signals:
    void signalUserAvatarUpdate(const QPixmap&);
    void signalExitButtonWasClicked(bool);

protected slots:
    void slotUpdateAvatar();
};

#endif // OPTIONSWINDOW_H
