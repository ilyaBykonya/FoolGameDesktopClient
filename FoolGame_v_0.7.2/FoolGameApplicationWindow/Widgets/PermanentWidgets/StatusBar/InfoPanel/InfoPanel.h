#pragma once
#include <QPainter>
#include <QWidget>

class InfoPanel : public QWidget
{
    Q_OBJECT
private:
    QPixmap m_pixmap;
    QString m_value;

public:
    explicit InfoPanel(const QPixmap&, QWidget* = nullptr);
    explicit InfoPanel(QWidget* = nullptr);

    const QString& value() const;
    void setValue(const QString&);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

};

