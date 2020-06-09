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
        CustomTabBar(QWidget*);
        QSize tabSizeHint(int) const;
        void setWidth(int);
    };

    CustomTabBar* m_tabBar = new CustomTabBar(this);
public:
    CustomTabWidget(QWidget* = nullptr);

    void resizeEvent(QResizeEvent *e);
};


#endif // CUSTOMTABWIDGET_H
