#include "CustomTabWidget.h"

CustomTabWidget::CustomTabBar::CustomTabBar(QWidget* parent)
    :QTabBar{ parent }
    {
        this->setWidth(size().width());
    }

QSize CustomTabWidget::CustomTabBar::tabSizeHint(int) const
{
    return QSize((m_size.width() / (count() ? count() : 1)), 18);/*size().height() можно вместо "16"*/
}
void CustomTabWidget::CustomTabBar::setWidth(int newWidth)
{
    m_size = QSize(newWidth, size().height());
    QTabBar::resize(m_size);
}



CustomTabWidget::CustomTabWidget(QWidget* parent)
    :QTabWidget{ parent },
     m_tabBar{ new CustomTabBar(this) }
    {
        this->setTabBar(m_tabBar);
    }

void CustomTabWidget::resizeEvent(QResizeEvent *e)
{
    m_tabBar->setWidth(size().width());
    QTabWidget::resizeEvent(e);
}

