#ifndef GDSDIALOG_H
#define GDSDIALOG_H

#include <QDialog>

namespace Ui {
class GdsDialog;
}

class GdsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GdsDialog(QWidget *parent = nullptr);
    ~GdsDialog();

private:
    Ui::GdsDialog *ui;
};

#endif // GDSDIALOG_H
