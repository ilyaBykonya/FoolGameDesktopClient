#include "InfoPanel.h"


InfoPanel::InfoPanel(const QPixmap& pix, QWidget* parent)
    :QWidget{ parent },
     m_pixmap{ pix },
     m_value()
    {
        this->setObjectName("InfoPanel");
        this->setAutoFillBackground(true);
        this->setMinimumSize(10, 15);
    }

InfoPanel::InfoPanel(QWidget* parent)
    :QWidget{ parent },
     m_pixmap(),
     m_value()
    {
        this->setAutoFillBackground(true);
        this->setMinimumSize(10, 15);
    }

const QString& InfoPanel::value() const
{
    return m_value;
}
void InfoPanel::setValue(const QString& newValue)
{
    m_value = newValue;
    this->update();
}
void InfoPanel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if(!m_pixmap.isNull())
    {
    painter.drawPixmap(QRect(QPoint(2, 2), m_pixmap.size()), m_pixmap);
    painter.drawText(QRect(25, 2, this->width() - 25, 20),
                     Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter,
                     m_value);
    }
    else
    {
        painter.drawText(this->rect(),
                         Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter,
                         m_value);
    }
}
