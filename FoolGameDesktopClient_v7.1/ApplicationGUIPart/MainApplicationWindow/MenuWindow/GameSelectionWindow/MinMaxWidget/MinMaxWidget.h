#ifndef MINMAXWIDGET_H
#define MINMAXWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
class MinMaxWidget: public QWidget
{
private:
    QSpinBox* m_minSpinBox;
    QSpinBox* m_maxSpinBox;

    QLabel* m_textView;

public:
    MinMaxWidget(quint32 = 50, quint32 = 5000, QWidget* = nullptr);

    quint32 min() const;
    quint32 max() const;

    void setNewMaximun(quint32);
protected slots:
    void minSpinBoxValueChanged();
    void maxSpinBoxValueChanged();
};

#endif // MINMAXWIDGET_H
