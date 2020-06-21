#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../CanalsList.h"
class ChatWindow : public QWidget
{
    Q_OBJECT
public:
    static const QString colorsNamesArray[3];

private:
    QTextEdit* m_messageScreen;
    QLineEdit* m_entryField;

    Canal m_canal;
public:
    explicit ChatWindow(Canal, QWidget* = nullptr);
    Canal canal() const;

protected:
    QString templateHTMLString();

public slots:
    void slotReceiveMessage(const QString&);
    void slotReceiveMessage(const QString&, const QString&);

protected slots:
    void slotSendMessage();

signals:
    void signalSendMessage(Canal, const QString&);
};

#endif // CHATWINDOW_H
