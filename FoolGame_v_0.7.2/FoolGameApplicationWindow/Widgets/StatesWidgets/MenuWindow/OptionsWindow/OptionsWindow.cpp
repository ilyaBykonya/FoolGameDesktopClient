#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(const QPixmap& avatar, QWidget *parent)
    :QWidget{ parent },
     m_gameSettingsController{ new GameSettingObject(this) },
     m_rateController{ new QComboBox }
    {
        //=====================================================================
        //=====================================================================


        QPushButton* m_exitButton = new QPushButton(QIcon("D:/FoolGame/FoolGameDesktopClient/pictures/quit_button_picture/ara.png"), "");
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &OptionsWindow::signalExitButtonWasClicked);

        //=====================================================================
        //=====================================================================


        for(quint8 i = 0; i < countOfTransactons; ++i)
            m_rateController->addItem(QString::number(transactions[i]));

        QObject::connect(m_rateController, (void(QComboBox::*)(int))(&QComboBox::activated),
                         [this](int index) { m_gameSettingsController->setRateIndex(index); });

        m_rateController->setCurrentIndex(m_gameSettingsController->rateIndex());


        //=====================================================================
        //=====================================================================

        QGroupBox* deckSizeButtonsGroupBox = new QGroupBox;
        deckSizeButtonsGroupBox->setTitle("Deck size");

            m_deck_24 = new QCheckBox("24 cards");
                m_deck_24->setChecked(m_gameSettingsController->deckType() & DeckType::Deck_24);
                QObject::connect(m_deck_24, &QCheckBox::toggled,
                                 [this](){ m_gameSettingsController->setDeckType(DeckType::Deck_24); });

            m_deck_36 = new QCheckBox("36 cards");
                m_deck_36->setChecked(m_gameSettingsController->deckType() & DeckType::Deck_36);
                QObject::connect(m_deck_36, &QCheckBox::toggled,
                                 [this](){ m_gameSettingsController->setDeckType(DeckType::Deck_36); });

            m_deck_52 = new QCheckBox("52 cards");
                m_deck_52->setChecked(m_gameSettingsController->deckType() & DeckType::Deck_52);
                QObject::connect(m_deck_52, &QCheckBox::toggled,
                                 [this](){ m_gameSettingsController->setDeckType(DeckType::Deck_52); });



                QVBoxLayout* deckSizeOptionsLayout = new QVBoxLayout;
                    deckSizeOptionsLayout->addWidget(m_deck_24);
                    deckSizeOptionsLayout->addWidget(m_deck_36);
                    deckSizeOptionsLayout->addWidget(m_deck_52);
        deckSizeButtonsGroupBox->setLayout(deckSizeOptionsLayout);

        //=====================================================================
        //=====================================================================



        //=====================================================================
        //=====================================================================

            QGroupBox* playersCountButtonsGroupBox = new QGroupBox;
            playersCountButtonsGroupBox->setTitle("Count of players");

                m_players_2 = new QCheckBox("2 players");
                        m_players_2->setChecked(m_gameSettingsController->countOfPlayers() & CountOfPlayers::Players_2);
                    QObject::connect(m_players_2, &QCheckBox::toggled,
                                     [this](){ m_gameSettingsController->setCountOfPlayers(CountOfPlayers::Players_2); });

                m_players_3 = new QCheckBox("3 players");
                    m_players_3->setChecked(m_gameSettingsController->countOfPlayers() & CountOfPlayers::Players_3);
                    QObject::connect(m_players_3, &QCheckBox::toggled,
                                     [this](){ m_gameSettingsController->setCountOfPlayers(CountOfPlayers::Players_3); });

                m_players_4 = new QCheckBox("4 players");
                    m_players_4->setChecked(m_gameSettingsController->countOfPlayers() & CountOfPlayers::Players_4);
                    QObject::connect(m_players_4, &QCheckBox::toggled,
                                     [this](){ m_gameSettingsController->setCountOfPlayers(CountOfPlayers::Players_4); });

                m_players_5 = new QCheckBox("5 players");
                    m_players_5->setChecked(m_gameSettingsController->countOfPlayers() & CountOfPlayers::Players_5);
                    QObject::connect(m_players_5, &QCheckBox::toggled,
                                     [this](){ m_gameSettingsController->setCountOfPlayers(CountOfPlayers::Players_5); });

                m_players_6 = new QCheckBox("6 players");
                    m_players_6->setChecked(m_gameSettingsController->countOfPlayers() & CountOfPlayers::Players_6);
                    QObject::connect(m_players_6, &QCheckBox::toggled,
                                     [this](){ m_gameSettingsController->setCountOfPlayers(CountOfPlayers::Players_6); });

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


        m_pixmapScreen = new QLabel;
        m_changeNewAvatarButton = new QPushButton("Change avatar");
        QObject::connect(m_changeNewAvatarButton, &QPushButton::clicked,
                         this, &OptionsWindow::slotUpdateAvatar, Qt::ConnectionType::UniqueConnection);

        QVBoxLayout* settingsAvatarLayout = new QVBoxLayout;
        settingsAvatarLayout->addWidget(m_pixmapScreen, 4);
        settingsAvatarLayout->addWidget(m_changeNewAvatarButton, 1);


        m_pixmapScreen->setPixmap(avatar);


        QGridLayout* optionsLayout = new QGridLayout;
            optionsLayout->addWidget(m_exitButton, 0, 0);
            optionsLayout->addWidget(m_rateController, 0, 1, 1, 6);
            optionsLayout->addWidget(deckSizeButtonsGroupBox, 2, 2, 5, 4);
            optionsLayout->addWidget(playersCountButtonsGroupBox, 2, 6, 5, 4);
            optionsLayout->addWidget(m_trancferableAbilityButton, 7, 2, 1, 4);
            optionsLayout->addLayout(settingsAvatarLayout, 2, 10, 5, 4);


            optionsLayout->setRowStretch(1, 2);
            optionsLayout->setRowStretch(8, 2);
            optionsLayout->setColumnStretch(14, 1);

        this->setLayout(optionsLayout);
    }


void OptionsWindow::slotUpdateAvatar()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Change picture no more 80x80 px");
    if(!filePath.isEmpty())
    {
        QPixmap pix(filePath);
        if(pix.width() * pix.height() < 6500)
        {
            emit this->signalUserAvatarUpdate(pix);
            m_pixmapScreen->setPixmap(pix);
        }
        else
        {
            QMessageBox::information(this, "Error", "This picture very big");
        }
    }
}
