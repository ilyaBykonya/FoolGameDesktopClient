#ifndef APPLICATIONETHERNETCONTROLLER_H
#define APPLICATIONETHERNETCONTROLLER_H
#include "InstanceGUIPart/GameTable/GameTableWidget.h"
#include <QtNetwork/QTcpSocket>

namespace EthernetSignals
{
    namespace ClientSignal
    {
        enum TypeSignal
        {
            FromAppToServ = 0,
            FromAppInstToServInst
        };

        enum ApplicationSignal
        {
            PlayerWantPlay = 0,
            PlayerDepositMoney,
            PlayerWithdrawMoney,
            PlayerRegistration
        };
        enum TableSignal
        {

            ActionButtonWasClicked = 0,
            TryBeat,
            TryToss,
            TryTransferable
        };
    }

    namespace ServerSignal
    {
        enum TypeSignal
        {
            FromServToApp = 0,
            FromServInstToAppInst
        };

        enum ServerSignal
        {
            SetPlayerID = 0,
            GetAllPlayInstanceOptions,
            AlertMessage
        };
        enum InstanceSignal
        {
            PlayerTakeAllCards = 0,
            PlayerTossedCard,
            PlayerBeatCard,
            PlayerTrancferable,
            ThisPlayerTakeCardFromDeck,
            OtherPlayerTakeCardFromDeck,
            MakeTurn,
            EndOfMatch,
            UnsuccesfullyAction
        };
    }
}

class ApplicationEthernetController: public QObject
{
    Q_OBJECT
private:
    QTcpSocket* m_tcpSocket;
    qint16 m_nextDataBlockSize;
    GameTableWidget* m_tableWidget;
    qint16 m_ID;

public:
    explicit ApplicationEthernetController(QObject* parent = nullptr);

public slots:
    //================================================================
    //приё сигналов сервера
    void serverSlotReadyRead();
    void serverSlotReadFromServToApp(QDataStream&);
    void serverSlotReadFromServInstToAppInst(QDataStream&);

    void serverSlotError(QAbstractSocket::SocketError);
    void serverSlotConnected();
    //================================================================
    //отправка событий на сервер для дльнейшей обработки
    //Эти слоты получают события от инстанса(стола)
    //и передают их слотам выше
    void instanceSlotActionButtonWasClicked();
    void instanceSlotPlayerTryBeat(Card::Suit, Card::Dignity, qint16);
    void instanceSlotPlayerTryToss(Card::Suit, Card::Dignity);
    void instanceSlotTryTransferable(Card::Suit, Card::Dignity);

    void applicationSlotPlayerWantPlay(quint8, quint8, bool);
    void applicationSlotPlayerRegistration(const QString&, const QString&);
    void applicationSlotPlayerDepositMoney(qint16);
    void applicationSlotPlayerWithdrawMoney(qint16);

signals:
    //Эти сигналы вызываются для стола.
    //Решение, какой из них будет вызван,
    //присылается от сервера
    void signalInstancePlayerTakeAllCards(qint16);
    void signalInstancePlayerTossedCard(qint16, Card::Suit, Card::Dignity);
    void signalInstancePlayerBeatCard(qint16, qint16, Card::Suit, Card::Dignity);
    void signalInstancePlayerTransferable(qint16, Card::Suit, Card::Dignity);
    void signalInstanceThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void signalInstanceOtherPlayerTakeCardFromDeck(qint16);
    void signalInstanceSetNewMainPair(qint16, qint16);
    void signalInstanceMakeTurn();
    void signalInstanceEndOfMatch();

    void signalInstanceUnsuccesfullyAction(PlayerActionType, Card::Suit, Card::Dignity, qint16);

    //нижняя (видимая) карта колоды, id ЭТОГО игрока, список id всех игроков, id первого ходящего и защищеющегося, размер колоды
    void signalApplicationCreateGameInstance(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16, qint16);
    void signalApplicationMakeAlert(const QString&, const QString&);
};

#endif // APPLICATIONETHERNETCONTROLLER_H
