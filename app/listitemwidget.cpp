#include "listitemwidget.h"
#include "styleframe.h"
#include <QHBoxLayout>
#include <QLabel>

ListItemWidget::ListItemWidget(const BorderStyle &style, const QString &text, QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    // Create the QFrame
    StyleFrame *frame = new StyleFrame(style, this);

    // Create the QLabel to display the text
    QLabel *label = new QLabel(text, this);

    // Add frame and label to the layout
    layout->addWidget(frame);
    layout->addWidget(label);
    layout->addStretch();

    setLayout(layout);
}
