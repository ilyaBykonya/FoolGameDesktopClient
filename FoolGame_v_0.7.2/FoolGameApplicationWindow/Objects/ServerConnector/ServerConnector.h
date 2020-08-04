#pragma once
#include "FoolGameApplicationWindow/Objects/UsersInformation/GameUserInformation/GameUserInformation.h"
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/Card/Card.h"
#include "FoolGameApplicationWindow/Files/SettingsStruct.h"
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include "FoolGameApplicationWindow/Files/ChatCanals.h"
#include <QWebSocket>

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
                PlayerExitFromWaitingRoom,

                PlayerDepositMoney,
                PlayerWithdrawMoney,

                MessageSignal,
                UpdateUserAvatar
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
                TryRegistration,
                LogOut
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
                YouAreAddedToTheQueue = 0,
                YouAreRemovedFromTheQueue,

                GetAllPlayInstanceOptions,


                AlertMessage,

                UserMessageSignal,
                ServerMessageSignal,


                UpdateUserInformation
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
                SuccesfullySignIn = 0,
                UnsuccesfullySignIn,
                LogOut
            };
        }
    }
}

class ServerConnector: public QObject
{
    Q_OBJECT
private:
    QWebSocket* m_webSocket;
    UserID m_ID;

public:
    explicit ServerConnector(const QString&, quint16, QObject* parent = nullptr);

public slots:
    //================================================================
    //приём сигналов сервера
    void serverSlotReadyRead(const QByteArray&);
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
    void registrationSlotPlayerLogOut();

    void applicationSlotPlayerWantPlay(SettingsStruct);
    void applicationSlotPlayerExitFromWaitingRoom();

    void financeSlotPlayerDepositWallet(Cash);
    void financeSlotPlayerWithdrawWallet(Cash);

    void messageSlotSendMessage(Canal, const QString&);


    void slotUpdateUserAvatar(const QPixmap&);
    //!



signals:
    void registrationSignalSuccusfullySignIn(UserID, const QString&, Cash, Cash, quint32, quint32, const QPixmap&);
    void registrationSignalUnsuccusfullySignIn(const QString&);
    void registrationSignalConfirmLogOut();



    void queueSignalUserAddedToWaitingRoom();
    void queueSignalUserRemovedFromWaitingRoom();



    void messageSignalReceiveUserMessage(Canal, UserID, const QString&);
    void messageSignalReceiveServerMessage(const QString&);



    //Эти сигналы вызываются для стола.
    //Решение, какой из них будет вызван,
    //присылается от сервера
    void signalInstancePlayerTossedCard(UserID, Card::Suit, Card::Dignity);
    void signalInstancePlayerBeatCard(UserID, PairID, Card::Suit, Card::Dignity);
    void signalInstancePlayerTransferable(UserID, Card::Suit, Card::Dignity);
    void signalInstanceUnsuccesfullyAction();

    void signalInstancePlayerTakeAllCards(UserID);
    void signalInstanceThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void signalInstanceOtherPlayerTakeCardFromDeck(UserID);

    void signalInstanceSetNewMainPair(UserID, UserID);
    void signalInstanceMakeTurn();

    void signalInstanceEndOfMatch(QList<GameUserInformation*>);


    //нижняя (видимая) карта колоды, id ЭТОГО игрока, список id всех игроков, id первого ходящего и защищающегося, размер колоды
    void signalApplicationCreateGameInstance(Card::Suit, Card::Dignity, UserID, QList<GameUserInformation*>, UserID, UserID, DeckSize);
    void signalApplicationMakeAlert(const QString&, const QString&);






    void signalUpdateThisUserFullInformation(const QString&, Cash, Cash, quint32, quint32);
};
