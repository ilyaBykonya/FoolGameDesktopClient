#include "Card.h"


Card::Card(Suit s, Dignity dig, QObject* parent)
    :QObject{ parent },
     m_dignity{ dig },
     m_suit{ s }
    {
        m_pictureCard =  QPixmap("D:\\FoolGame\\FoolGameDesktopClient\\pictures\\Cards\\" + QString::number(m_suit) + "_" + QString::number(m_dignity) + ".png");
        m_shirtCard = QPixmap("D:\\FoolGame\\FoolGameDesktopClient\\pictures\\Cards\\cardShirt.jpg");
    }

bool Card::operator<(const Card* other)
{
    if(this->suit() < other->suit())
        return true;
    else if(this->suit() > other->suit())
        return false;
    else
        return (this->dignity() < other->dignity());
}

const QPixmap& Card::getPixmapForPrint()
{

    switch(m_location)
    {
        case InBattlePlace           :
        case FirstCardInStartDeck    :
        case InPlayerDeck            :
        {
            return this->m_pictureCard;
        }
        case InStartDeck             :
        case InHangUp                :
        {
            return this->m_shirtCard;
        }
    }
}
