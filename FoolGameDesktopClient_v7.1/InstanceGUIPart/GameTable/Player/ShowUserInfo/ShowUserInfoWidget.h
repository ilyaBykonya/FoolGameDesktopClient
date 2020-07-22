#pragma once
#include "TypesAliases.h"
#include <QMessageBox>
#include <QPainter>

class ShowUserInfoWidget : public QWidget
{
    Q_OBJECT
private:
    UserID m_userID;
    QString m_userName;

    QPixmap m_avatar;
public:
    explicit ShowUserInfoWidget(UserID, const QString&, QWidget *parent = nullptr);

    UserID userID() const;
    const QString& userName() const;

protected:
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;
};

