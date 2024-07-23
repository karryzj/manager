#ifndef STYLEDIALOG_H
#define STYLEDIALOG_H

#include <QDialog>
#include <QObject>
#include "pdk_info.h"

class StyleDialog final : public QDialog
{
    Q_OBJECT
public:
    explicit StyleDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    StyleDialog(const BorderStyle &style, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~StyleDialog(void) override;

    BorderStyle getData(void);
    void setData(const BorderStyle &style);
private:
    void setupUi(void);
    void setupUi(const BorderStyle &style);

// signals:
//     void dataChanged();

private:
    BorderStyle m_border_style;
};

#endif // STYLEDIALOG_H
