#include "ShowUserInfoWidget.h"
ShowUserInfoWidget::ShowUserInfoWidget(UserID id, const QString& name, QWidget *parent)
    :QWidget{ parent },
     m_userID{ id },
     m_userName{ name },
     m_avatar(QString("../pictures/user_avatars/%1.png").arg(rand() % 3))
    {

    }

UserID ShowUserInfoWidget::userID() const
{
    return m_userID;
}
const QString& ShowUserInfoWidget::userName() const
{
    return m_userName;
}

void ShowUserInfoWidget::mousePressEvent(QMouseEvent*)
{
    QMessageBox::information(this, "User info:", QString("Name: %1\n"
                                                         "ID  : %2").arg(m_userName).arg(m_userID));
}
void ShowUserInfoWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(255, 100, 0)));
        painter.drawRect(this->rect());
        painter.drawPixmap(this->rect(), m_avatar);
}
