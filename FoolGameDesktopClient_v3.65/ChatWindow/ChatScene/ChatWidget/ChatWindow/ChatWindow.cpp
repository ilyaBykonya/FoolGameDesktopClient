#include "ChatWindow.h"


ChatWindow::ChatWindow(Canal chatCanal, QWidget* parent)
    :QWidget{ parent },
     m_messageScreen{ new QTextEdit },
     m_entryField{ new QLineEdit },
     m_canal{ chatCanal }
    {
        m_messageScreen->setReadOnly(true);
        QVBoxLayout* layout = new QVBoxLayout;
            layout->addWidget(m_messageScreen);
            layout->addWidget(m_entryField);
        this->setLayout(layout);
        QObject::connect(m_entryField, &QLineEdit::returnPressed, this, &ChatWindow::slotSendMessage, Qt::ConnectionType::UniqueConnection);
    }

Canal ChatWindow::canal() const
{
    return m_canal;
}


QString ChatWindow::templateHTMLString()
{
    return "<div><font color = %1>%2</font></div>";
}
void ChatWindow::slotReceiveMessage(const QString& message)
{
    slotReceiveMessage(message, colorsNamesArray[m_canal]);
}
void ChatWindow::slotReceiveMessage(const QString& message, const QString& colorString)
{
    m_messageScreen->append(templateHTMLString().arg(colorString).arg(message));
}


void ChatWindow::slotSendMessage()
{
    emit this->signalSendMessage(m_canal, m_entryField->text());
    m_entryField->clear();
    this->update();
}


const QString ChatWindow::colorsNamesArray[3] =
{
    "#00FF00",
    "#0000FF",
    "#FF0000"
};
