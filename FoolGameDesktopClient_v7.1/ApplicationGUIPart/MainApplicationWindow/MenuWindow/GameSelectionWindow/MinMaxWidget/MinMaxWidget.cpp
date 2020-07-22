#include "MinMaxWidget.h"


MinMaxWidget::MinMaxWidget(quint32 min, quint32 max, QWidget* parent)
    :QWidget{ parent },
     m_minSpinBox{ new QSpinBox },
     m_maxSpinBox{ new QSpinBox },
     m_textView{ new QLabel(QString("[%1:%2]").arg(min).arg(max)) }
    {
        if(min > max)
        {
            quint32 temp = max;
            max = min;
            min = temp;
        }
        QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* spinBoxeslayout = new QHBoxLayout;
                m_minSpinBox->setRange(min, max - (max * 10 / 100));
                m_minSpinBox->resize(m_minSpinBox->minimumSize());
                m_minSpinBox->setValue(min);

                m_maxSpinBox->setRange(m_minSpinBox->maximum(), max);
                m_maxSpinBox->resize(m_maxSpinBox->minimumSize());
                m_maxSpinBox->setValue(max);
                
            spinBoxeslayout->addWidget(m_minSpinBox, 1);
            spinBoxeslayout->addWidget(m_maxSpinBox, 1);

        layout->addLayout(spinBoxeslayout);
        layout->addWidget(m_textView, Qt::AlignmentFlag::AlignCenter);
        this->setLayout(layout);

        void(QSpinBox::*ptrFcn)(int) = &QSpinBox::valueChanged;
        QObject::connect(m_minSpinBox, ptrFcn, this, &MinMaxWidget::minSpinBoxValueChanged);
        QObject::connect(m_maxSpinBox, ptrFcn, this, &MinMaxWidget::maxSpinBoxValueChanged);


        minSpinBoxValueChanged();
        maxSpinBoxValueChanged();
    }

void MinMaxWidget::setNewMaximun(quint32 newMax)
{
    m_maxSpinBox->setMaximum(newMax);
}

quint32 MinMaxWidget::min() const
{
    return m_minSpinBox->value();
}
quint32 MinMaxWidget::max() const
{
    return m_maxSpinBox->value();
}

void MinMaxWidget::minSpinBoxValueChanged()
{
    m_maxSpinBox->setMinimum(m_minSpinBox->value() + 50);
    m_textView->setText(QString("[%1:%2]").arg(m_minSpinBox->value()).arg(m_maxSpinBox->value()));
}
void MinMaxWidget::maxSpinBoxValueChanged()
{
    m_minSpinBox->setMaximum(m_maxSpinBox->value() - 50);
    m_textView->setText(QString("[%1:%2]").arg(m_minSpinBox->value()).arg(m_maxSpinBox->value()));
}

