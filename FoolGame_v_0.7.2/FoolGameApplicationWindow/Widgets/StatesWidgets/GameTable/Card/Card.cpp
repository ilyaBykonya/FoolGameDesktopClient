#include "Card.h"


Card::Card(Suit s, Dignity dig, QWidget* parent)
    :QWidget{ parent },
     m_dignity{ dig },
     m_suit{ s }
    {
        m_pictureCard =  QPixmap(QString("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/%1_%2.png").arg(m_suit).arg(m_dignity));
        m_shirtCard = QPixmap("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg");
        this->resize(65, 90);
        this->show();
    }

Card::LocationState Card::location() const
{
    return m_location;
}
void Card::setNewLocation(LocationState newLoc)
{
    m_location = newLoc;
    this->update();
}

Card::Dignity Card::dignity() const
{
    return m_dignity;
}
Card::Suit Card::suit() const
{
    return m_suit;
}


const QPixmap& Card::getPixmapForPrint()
{
    switch(m_location)
    {
        case InUserHand                 :
        case InBattlePlace              :
        case InPlayerDeck               :
        {
            return this->m_pictureCard;
        }

        case InStartDeck                :
        case InHangUp                   :
        case InOtherPlayerDeck          :
        {
            return this->m_shirtCard;
        }

        default                         :
        {
            return this->m_shirtCard;
        }
    }
}
void Card::doAnimationOnPoint(QPoint p)
{
    this->show();


    QSize diff(p.x() - this->x(), p.y() - this->y());
    quint16 lengthOfPath = sqrt(pow(diff.width(), 2) + pow(diff.height(), 2));

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry", this);
    animation->setEndValue(QRect(p, QSize(65, 90)));
    animation->setDuration(lengthOfPath / 2);
    QObject::connect(animation, &QPropertyAnimation::finished, [this](){ emit this->endOfAnimation(this); });

    animation->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);
}


void Card::mousePressEvent(QMouseEvent *event)
{
    if((m_location != LocationState::InPlayerDeck))
        return;

    m_lastClick = event->pos();
    this->setNewLocation(LocationState::InUserHand);
    emit dragThisElement(this);
}
void Card::mouseMoveEvent(QMouseEvent *event)
{
    if(m_location != LocationState::InUserHand)
        return;

    this->move(this->pos() + event->pos() - m_lastClick);
    emit this->movingThisElement(this, this->pos() + m_lastClick);
}
void Card::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_location != LocationState::InUserHand)
        return;

    emit dropThisElement(this, this->pos() + event->pos());
}
void Card::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(QRect({0, 0}, this->size()), this->getPixmapForPrint());
}


bool Card::less(const Card* c1, const Card* c2)
{
    if(c1->dignity() < c2->dignity())
    {
        return true;
    }
    else if(c1->dignity() == c2->dignity())
    {
        if(c1->suit() < c2->suit())
        {
            return true;
        }
        else
        {
            return false;
        }
    } else
    {
        return false;
    }
}
