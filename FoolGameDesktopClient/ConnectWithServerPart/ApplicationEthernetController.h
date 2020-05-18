#ifndef APPLICATIONETHERNETCONTROLLER_H
#define APPLICATIONETHERNETCONTROLLER_H
#include "../InstanceGUIpart/GameTable/GameTableWidget.h"
#include <QtNetwork/QTcpSocket>

class ApplicationEthernetController: public QObject
{
    Q_OBJECT
public:
    //Надо ещё создать перечисления для
    //платёжной системы (снять/пополнтиь)
    //и смены настроек. Также можно отправлять
    //опции вместе с SignalFromApplicationOnServer::PlayerWantPlay
    //Для этого требуется расширить соответствующие функции
    //в приложении и на сервере
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
        ThisPlayerTakeCardFromDeck = 3,
        OtherPlayerTakeCardFromDeck = 4,
        SetNewMainPlayersPair = 5,
        MakeTurn = 6,
        YourActionIsUnsuccesfully = 7,

        SetPlayerID = 8,
        GetAllPlayInstanceOptions = 9
    };

private:
    QTcpSocket* m_tcpSocket;
    qint16 m_nextDataBlockSize;
    GameTableWidget* m_tableWidget;
    qint16 m_ID;

public:
    explicit ApplicationEthernetController(QObject* parent = nullptr);

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
    void instanceSlotPlayerTryBeat(Card*, qint16);
    void instanceSlotPlayerTryToss(Card*);
    void instanceSlotPlayerWantPlay();

signals:
    //Эти сигналы вызываются для стола.
    //Решение, какой из них будет вызван,
    //присылается от сервера
    void signalPlayerTakeAllCards(qint16);
    void signalPlayerTossedCard(qint16, Card::Suit, Card::Dignity);
    void signalPlayerBeatCard(qint16, qint16, Card::Suit, Card::Dignity);
    void signalThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void signalOtherPlayerTakeCardFromDeck(qint16);
    void signalSetNewMainPair(qint16, qint16);
    void signalMakeTurn();
    void signalYourActionIsUnsuccesfully();

    void signalCreateGameInstance(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16);
};

#endif // APPLICATIONETHERNETCONTROLLER_H
