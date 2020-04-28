#ifndef GAMETABLEWIDGET_H
#define GAMETABLEWIDGET_H


#include "../../GUIpart/StartDeck/StartDeckWidget.h"
#include "../../GUIpart/BattleArea/BattleAreaWidget.h"
#include "../../GUIpart/ThisPlayerDeck/ThisPlayerDeckWidget.h"
#include "../../GUIpart/OtherPlayerDeck/OtherPlayerDeckWidget.h"
#include "../../GUIpart/HandUp/HandUpWidget.h"

class GameTableWidget : public QWidget
{
    Q_OBJECT
private:
    StartDeckWidget* m_startDeckWidget;
    QList<SharedParentForPlayersDeck*> m_playersList;
    BattleAreaWidget* m_battleAreaWidget;
    HandUpWidget* m_handUpWidget;

    QPair<Card*, BattlePairWidget*> m_functionalPair;
    QList<qint16> m_playersIDList;
    qint16 m_thisPlayerID;

    //TEST
    ThisPlayerDeckWidget* m_thisPlayer;
public:
    explicit GameTableWidget(qint16, QList<qint16>, qint16, qint16, QWidget *parent = nullptr);

protected:
    SharedParentForPlayersDeck* findDeckForID(qint16);

public slots:
    void slotAttackerChangeThisCard(Card*);
    void slotDefenderChangeThisCard(Card*);
    void slotPlayerChangeThisBattlePair(BattlePairWidget*);
    void slotCheckFunctionlPairForSendToServer();


    void serverSlotPlayerTakeAllCards(qint16);
    void serverSlotPlayerTakeCardFromDeck(qint16, Card::Suit, Card::Dignity);
    void serverSlotPlayerTossedCard(qint16, Card::Suit, Card::Dignity);
    void serverSlotPlayerBeatCard(qint16, qint16, Card::Suit, Card::Dignity);
    void serverSlotSetNewMainPair(qint16, qint16);
    void serverSlotMakeTurn();

signals:
    void actionButtonWasClicked();
    void tryBeat(Card*, BattlePairWidget*);
    void tryToss(Card*);
};


#endif // GAMETABLEWIDGET_H
