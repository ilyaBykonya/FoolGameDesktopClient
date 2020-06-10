#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFrame>

class ChatWindow : public QFrame
{
    Q_OBJECT
public:
    enum Canal
    {
        InGame = 0,
        InApplication
    };
private:
    QTextEdit* m_messageScreen;
    QLineEdit* m_entryField;

    Canal m_chatCanal;

public:
    explicit ChatWindow(Canal, QWidget *parent = nullptr);

public slots:
    void slotReceiveMessage(Canal, const QString&);

protected slots:
    void slotSendMessage();

signals:
    void signalSendMessage(Canal, const QString&);

};

#endif // CHATWINDOW_H
