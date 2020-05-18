#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>
#include <QPushButton>

class OptionsWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_exitButton;
public:
    explicit OptionsWindow(QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);
};

#endif // OPTIONSWINDOW_H
