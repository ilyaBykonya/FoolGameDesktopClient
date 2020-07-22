#include "CustomTabWidget.h"



CustomTabWidget::CustomTabBar::CustomTabBar(QWidget* parent)
    :QTabBar(parent)
    {
        setWidth(size().width());
    }

QSize CustomTabWidget::CustomTabBar::tabSizeHint(int) const
{
    return QSize(_size.width()/(count()?count():1), /*size().height()*/16);
}
void CustomTabWidget::CustomTabBar::setWidth(int a_width)
    {
        _size = QSize(a_width, size().height());
        QTabBar::resize(_size);
    }



CustomTabWidget::CustomTabWidget(QWidget* parent)
    :QTabWidget{ parent }
    {
        setTabBar(m_tabBar);
    }

void CustomTabWidget::resizeEvent(QResizeEvent *e)
{
    m_tabBar->setWidth(size().width());
    QTabWidget::resizeEvent(e);
}


