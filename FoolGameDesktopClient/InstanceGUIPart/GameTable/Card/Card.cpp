#include "Card.h"


Card::Card(Suit s, Dignity dig, QWidget* parent)
    :QWidget{ parent },
     m_dignity{ dig },
     m_suit{ s },
     m_location{ LocationState::InStartDeck },
     m_timer{ nullptr },
     m_targetPos{0, 0},
     m_sizeOfStep{0, 0},
     m_countOfSteps{ 0 },
     m_maxSteps{ 0 }
    {
        m_pictureCard =  QPixmap("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/" + QString::number(m_suit) + "_" + QString::number(m_dignity) + ".png");
        m_shirtCard = QPixmap("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg");
        this->resize(m_pictureCard.size());
    }


const QPixmap& Card::getPixmapForPrint()
{
    switch(m_location)
    {
        case InUserHand              :
        case InBattlePlace           :
        case FirstCardInStartDeck    :
        case InPlayerDeck            :
        {
            return this->m_pictureCard;
        }
        case InStartDeck             :
        case InHangUp                :
        case InOtherPlayerDeck       :
        {
            return this->m_shirtCard;
        }
    }
}


void Card::moveThisCard(QPoint p)
{
    if(m_timer != nullptr)
    {
        this->reset();
        emit endOfAnimation(this);
    }

    m_startPosition = p;
    this->move(p);
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
}
void Card::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_location != LocationState::InUserHand)
        return;

    emit dropThisElement(this, this->pos() + event->pos());
}
void Card::successDrop()
{
    m_startPosition = this->pos();
}
void Card::unsuccessDrop()
{
    this->move(m_startPosition);
}

bool Card::less(const Card* c1, const Card* c2)
{
    if(c1->suit() < c2->suit())
        return true;
    else if(c1->suit() == c2->suit())
        if(c1->dignity() < c2->dignity())
            return true;
        else
            return false;
    else
        return false;
}

void Card::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(QRect({0, 0}, this->getPixmapForPrint().size()), this->getPixmapForPrint());
}

void Card::setNewLocation(LocationState newLoc)
{
    m_location = newLoc;
}

void Card::doAnimationOnPoint(QPoint p)
{
    if(m_timer != nullptr)
    {
        this->reset();
        emit endOfAnimation(this);
    }


    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, &Card::moveForAnimation);

    m_targetPos = p;

    QPoint diff = (m_targetPos - this->pos());
    m_maxSteps = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2)) / 12;//12 - кол-во пикселов/3мс
    m_sizeOfStep = diff / m_maxSteps;
    m_timer->start(5);
}

void Card::moveForAnimation()
{

    if(m_countOfSteps == m_maxSteps)
    {
        this->reset();
        emit endOfAnimation(this);
        return;
    }

    this->move(this->pos() + m_sizeOfStep);
    ++m_countOfSteps;
}

void Card::reset()
{
    if(m_timer)
    {
        delete m_timer;
        m_timer = nullptr;
    }
    this->move(m_targetPos);
    m_startPosition = this->pos();
    m_targetPos = {0, 0};
    m_sizeOfStep = {0, 0};
    m_countOfSteps = 0;
    m_maxSteps = 0;
}
