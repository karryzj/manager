#include "colorlabel.h"

void ColorLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit doubleClicked();
    }
}
