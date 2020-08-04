#pragma once
#include <QTabWidget>
#include <QPainter>
#include <QTabBar>



class CustomTabWidget : public QTabWidget
{
private:
    class CustomTabBar : public QTabBar
    {
        QSize m_size;
    public:
        CustomTabBar(QWidget*);
        QSize tabSizeHint(int) const;
        void setWidth(int);
    };

    CustomTabBar* m_tabBar;
public:
    CustomTabWidget(QWidget* = nullptr);

protected slots:
    virtual void resizeEvent(QResizeEvent*) override;
};
