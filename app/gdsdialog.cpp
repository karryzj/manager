#include "gdsdialog.h"
#include "ui_gdsdialog.h"

GdsDialog::GdsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GdsDialog)
{
    ui->setupUi(this);
    ui->lineEdit_gdsnum->setText("aaa");
}

GdsDialog::~GdsDialog()
{
    delete ui;
}
