#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(QWidget *parent)
    :QWidget{ parent },
     m_gameSettingsController{ new GameSettingObject(this) }
    {
        //=====================================================================

        QPushButton* m_exitButton = new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "");
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &OptionsWindow::signalExitButtonWasClicked);

        //=====================================================================

        QGroupBox* deckSizeButtonsGroupBox = new QGroupBox;

            m_deck_24 = new QCheckBox("24 cards");
                m_deck_24->setChecked(m_gameSettingsController->deckTypeFlag_24());
                QObject::connect(m_deck_24, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setDeckTypeFlag_24);

            m_deck_36 = new QCheckBox("36 cards");
                m_deck_36->setChecked(m_gameSettingsController->deckTypeFlag_36());
                QObject::connect(m_deck_36, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setDeckTypeFlag_36);

            m_deck_52 = new QCheckBox("52 cards");
                m_deck_52->setChecked(m_gameSettingsController->deckTypeFlag_52());
                QObject::connect(m_deck_52, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setDeckTypeFlag_52);



                QVBoxLayout* deckSizeOptionsLayout = new QVBoxLayout;
                    deckSizeOptionsLayout->addWidget(m_deck_24);
                    deckSizeOptionsLayout->addWidget(m_deck_36);
                    deckSizeOptionsLayout->addWidget(m_deck_52);
            deckSizeButtonsGroupBox->setLayout(deckSizeOptionsLayout);

            //=====================================================================

            QGroupBox* playersCountButtonsGroupBox = new QGroupBox;

                m_players_2 = new QCheckBox("2 players");
                        m_players_2->setChecked(m_gameSettingsController->playersCountFlag_2());
                    QObject::connect(m_players_2, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setPlayerCountFlag_2);

                m_players_3 = new QCheckBox("3 players");
                    m_players_3->setChecked(m_gameSettingsController->playersCountFlag_3());
                    QObject::connect(m_players_3, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setPlayerCountFlag_3);

                m_players_4 = new QCheckBox("4 players");
                    m_players_4->setChecked(m_gameSettingsController->playersCountFlag_4());
                    QObject::connect(m_players_4, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setPlayerCountFlag_4);

                m_players_5 = new QCheckBox("5 players");
                    m_players_5->setChecked(m_gameSettingsController->playersCountFlag_5());
                    QObject::connect(m_players_5, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setPlayerCountFlag_5);

                m_players_6 = new QCheckBox("6 players");
                    m_players_6->setChecked(m_gameSettingsController->playersCountFlag_6());
                    QObject::connect(m_players_6, &QCheckBox::toggled, m_gameSettingsController, &GameSettingObject::setPlayerCountFlag_6);

                QVBoxLayout* playersCountOptionsLayout = new QVBoxLayout;
                    playersCountOptionsLayout->addWidget(m_players_2);
                    playersCountOptionsLayout->addWidget(m_players_3);
                    playersCountOptionsLayout->addWidget(m_players_4);
                    playersCountOptionsLayout->addWidget(m_players_5);
                    playersCountOptionsLayout->addWidget(m_players_6);
                playersCountButtonsGroupBox->setLayout(playersCountOptionsLayout);


        //=====================================================================

        m_trancferableAbilityButton = new QRadioButton("Trancferable game");
            m_trancferableAbilityButton->setChecked(m_gameSettingsController->trancferableAbility());
            QObject::connect(m_trancferableAbilityButton, &QRadioButton::toggled, m_gameSettingsController, &GameSettingObject::setTrancferableAbility);

        QGridLayout* optionsLayout = new QGridLayout;
            optionsLayout->addWidget(m_exitButton, 0, 0);
            optionsLayout->addWidget(deckSizeButtonsGroupBox, 2, 2, 5, 4);
            optionsLayout->addWidget(playersCountButtonsGroupBox, 2, 6, 5, 4);
            optionsLayout->addWidget(m_trancferableAbilityButton, 7, 2, 1, 4);
            optionsLayout->setRowStretch(1, 2);
            optionsLayout->setRowStretch(8, 2);
            optionsLayout->setColumnStretch(10, 1);

        this->setLayout(optionsLayout);
    }

void OptionsWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}
