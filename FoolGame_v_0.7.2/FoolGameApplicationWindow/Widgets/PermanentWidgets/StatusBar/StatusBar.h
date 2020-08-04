#pragma once
#include "FoolGameApplicationWindow/Objects/UsersInformation/ThisUserFullInformation/ThisUserFullInformation.h"
#include "InfoPanel/InfoPanel.h"
#include <QHBoxLayout>
#include <QLabel>

class StatusBar: public QWidget
{
    Q_OBJECT

private:
    InfoPanel* m_userName;
    InfoPanel* m_dollars;
    InfoPanel* m_tokens;
    InfoPanel* m_countOfGames;
    InfoPanel* m_raitingPoints;

public:
    explicit StatusBar(ThisUserFullInformation*, QWidget* = nullptr);

public slots:
    void slotUpdateInformation(ThisUserFullInformation*);
};


