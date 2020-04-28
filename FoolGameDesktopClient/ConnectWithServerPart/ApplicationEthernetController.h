#ifndef APPLICATIONETHERNETCONTROLLER_H
#define APPLICATIONETHERNETCONTROLLER_H

#include <QtWidgets>
#include "../GUIpart/GameTable/GameTableWidget.h"
#include <QtNetwork/QTcpSocket>

class ApplicationEthernetController: public QWidget
{
    Q_OBJECT
public:
    enum SignalFromApplicationOnServer
    {

        ActionButtonWasClicked = 0,
        TryBeat = 1,
        TryToss = 2,

        PlayerWantPlay = 3,
    };

    enum SignalFromServerToApplication
    {
        PlayerTakeAllCards = 0,
        PlayerTossedCard = 1,
        PlayerBeatCard = 2,
        TakeCardFromDeck = 3,
        SetNewMainPlayersPair = 4,
        MakeTurn = 5,


        SetPlayerID = 6,
        GetAllPlayInstanceOptions = 7
    };

private:
    QTcpSocket* m_tcpSocket;
    QTextEdit* m_textEdit;
    qint16 m_nextDataBlockSize;
    GameTableWidget* m_tableWidget;
    qint16 m_ID;

    QPushButton* m_startGame;
public:
    explicit ApplicationEthernetController(QWidget* parent = nullptr);

public slots:
    //================================================================
    //отправка событий на сервер для дльнейшей обработки
    void serverSlotReadyRead();
    void serverSlotError(QAbstractSocket::SocketError);
    void serverSlotConnected();
    //================================================================
    //Эти слоты получают события от инстанса(стола)
    //и передают их слотам выше
    void instanceSlotActionButtonWasClicked();
    void instanceSlotPlayerTryBeat(Card*, BattlePairWidget*);
    void instanceSlotPlayerTryToss(Card*);
    void instanceSlotPlayerWantPlay();
signals:
    //Эти сигналы вызываются для стола.
    //Решение, какой из них будет вызван,
    //присылается от сервера
    void signalPlayerTakeAllCards(qint16);
    void signalPlayerTossedCard(qint16, Card::Suit, Card::Dignity);
    void signalPlayerBeatCard(qint16, qint16, Card::Suit, Card::Dignity);
    void signalTakeCardFromDeck(qint16, Card::Suit, Card::Dignity);
    void signalSetNewMainPair(qint16, qint16);
    void signalMakeTurn();
};

#endif // APPLICATIONETHERNETCONTROLLER_H
