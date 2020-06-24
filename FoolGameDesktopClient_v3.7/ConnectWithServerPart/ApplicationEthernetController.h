#ifndef APPLICATIONETHERNETCONTROLLER_H
#define APPLICATIONETHERNETCONTROLLER_H
#include "ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/GameSettingObject/SettingsStruct/SettingsStruct.h"
#include "InstanceGUIPart/GameTable/Card/Card.h"
#include "ChatWindow/ChatScene/ChatScene.h"
#include <QtNetwork/QTcpSocket>
#include "UserInformation/UserInformation.h"

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

        namespace Signals
        {
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
    }

    namespace ServerSignal
    {
        enum TypeSignal
        {
            FromServToApp = 0,
            FromServInstToAppInst,
            SignInSignals
        };
        namespace Signals
        {
            enum ServerSignal
            {
                SetPlayerID = 0,
                GetAllPlayInstanceOptions,
                AlertMessage,

                UserMessageSignal,
                ServerMessageSignal
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
}

class ApplicationEthernetController: public QObject
{
    Q_OBJECT
private:
    QTcpSocket* m_tcpSocket;
    quint16 m_nextDataBlockSize;
    UserID m_ID;

public:
    explicit ApplicationEthernetController(QObject* parent = nullptr);

public slots:
    //================================================================
    //приём сигналов сервера
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
    void instanceSlotPlayerTryBeat(PairID, Card::Suit, Card::Dignity);
    void instanceSlotPlayerTryToss(Card::Suit, Card::Dignity);
    void instanceSlotTryTransferable(Card::Suit, Card::Dignity);


    //!Слоты [приложение -> сервер]
    void registrationSlotPlayerLogIn(const QString&, const QString&);
    void registrationSlotPlayerRegistration(const QString&, const QString&);

    void applicationSlotPlayerWantPlay(SettingsStruct);

    void applicationSlotPlayerDepositMoney(Cash);
    void applicationSlotPlayerWithdrawMoney(Cash);

    void messageSlotSendMessage(Canal, const QString&);
    //!



signals:
    //Эти сигналы вызываются для стола.
    //Решение, какой из них будет вызван,
    //присылается от сервера
    void signalInstancePlayerTakeAllCards(UserID);
    void signalInstancePlayerTossedCard(UserID, Card::Suit, Card::Dignity);
    void signalInstancePlayerBeatCard(UserID, PairID, Card::Suit, Card::Dignity);
    void signalInstancePlayerTransferable(UserID, Card::Suit, Card::Dignity);
    void signalInstanceThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void signalInstanceOtherPlayerTakeCardFromDeck(UserID);
    void signalInstanceSetNewMainPair(UserID, UserID);
    void signalInstanceMakeTurn();
    void signalInstanceEndOfMatch();

    void signalInstanceUnsuccesfullyAction();

    //нижняя (видимая) карта колоды, id ЭТОГО игрока, список id всех игроков, id первого ходящего и защищающегося, размер колоды
    void signalApplicationCreateGameInstance(Card::Suit, Card::Dignity, UserID, QList<UserInformation>, UserID, UserID, quint8);
    void signalApplicationMakeAlert(const QString&, const QString&);

    void registrationSignalSuccusfullyLogIn();
    void registrationSignalSuccusfullyRegistration();
    void registrationSignalUnsuccusfullyLogIn(const QString&);
    void registrationSignalUnsuccusfullyRegistration(const QString&);

    void messageSignalReceiveUserMessage(Canal, UserID, const QString&);
    void messageSignalReceiveServerMessage(const QString&);

};

#endif // APPLICATIONETHERNETCONTROLLER_H
