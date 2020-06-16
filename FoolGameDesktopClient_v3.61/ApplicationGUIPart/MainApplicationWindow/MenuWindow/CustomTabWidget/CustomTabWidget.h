#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H
#include <QTabWidget>
#include <QTabBar>

class CustomTabWidget : public QTabWidget
{
    class CustomTabBar : public QTabBar
    {
        QSize _size;
    public:
        CustomTabBar(QWidget* parent)
            :QTabBar(parent)
            {
                setWidth(size().width());
            }
        QSize tabSizeHint(int) const
        {
            return QSize(_size.width()/(count()?count():1), size().height());
        }
        void setWidth(int a_width)
        {
            _size = QSize(a_width, size().height());
            QTabBar::resize(_size);
        }
    };

    CustomTabBar* m_tabBar = new CustomTabBar(this);
public:
    CustomTabWidget(QWidget* parent = nullptr)
        :QTabWidget(parent)
        {
            setTabBar(m_tabBar);
        }

protected slots:
    virtual void resizeEvent(QResizeEvent *e) override
    {
        m_tabBar->setWidth(size().width());
        QTabWidget::resizeEvent(e);
    }
};




#endif // CUSTOMTABWIDGET_H
