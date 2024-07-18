#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class ColorLabel : public QLabel
{
    Q_OBJECT

public:
    ColorLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setStyleSheet("border: 2px solid black; padding: 5px;");
    }

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void doubleClicked();
};
#endif // COLORLABEL_H
