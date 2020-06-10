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
            FromAppInstToServInst,
            SignInSignals
        };


        enum ApplicationSignal
        {
            PlayerWantPlay = 0,
            PlayerDepositMoney,
            PlayerWithdrawMoney,
            MessageSignal
        };
        enum TableSignal
        {

            ActionButtonWasClicked = 0,
            TryBeat,
            TryToss,
            TryTransferable
        };

        enum SignIn
        {
            TryLogIn = 0,
            TryRegistration
        };
    }

    namespace ServerSignal
    {
        enum TypeSignal
        {
            FromServToApp = 0,
            FromServInstToAppInst,
            SignInSignals
        };

        enum ServerSignal
        {
            SetPlayerID = 0,
            GetAllPlayInstanceOptions,
            AlertMessage,
            MessageSignal
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

        enum SignIn
        {
            SuccesfullyLogIn = 0,
            SuccesfullyRegistration,
            UnsuccesfullyLogIn,
            UnsuccesfullyRegistration
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
    void serverSlotReadSignIn(QDataStream&);
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


    //!Слоты [приложение -> сервер]
    void registrationSlotPlayerLogIn(const QString&, const QString&);
    void registrationSlotPlayerRegistration(const QString&, const QString&);

    void applicationSlotPlayerWantPlay(quint8, quint8, bool);

    void applicationSlotPlayerDepositMoney(qint16);
    void applicationSlotPlayerWithdrawMoney(qint16);

    void messageSlotSendMessage(ChatWindow::Canal, const QString&);
    //!



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

    void signalInstanceUnsuccesfullyAction(Card::Suit, Card::Dignity, qint16);

    //нижняя (видимая) карта колоды, id ЭТОГО игрока, список id всех игроков, id первого ходящего и защищеющегося, размер колоды
    void signalApplicationCreateGameInstance(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16, qint16);
    void signalApplicationMakeAlert(const QString&, const QString&);

    void registrationSignalSuccusfullyLogIn();
    void registrationSignalSuccusfullyRegistration();
    void registrationSignalUnsuccusfullyLogIn(const QString&);
    void registrationSignalUnsuccusfullyRegistration(const QString&);

    void messageSignalReceiveMessage(ChatWindow::Canal, const QString&);

};

#endif // APPLICATIONETHERNETCONTROLLER_H
