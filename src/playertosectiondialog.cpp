#include "playertosectiondialog.h"
#include "ui_playertosectiondialog.h"

PlayerToSectionDialog::PlayerToSectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerToSectionDialog)
{
    ui->setupUi(this);
}

PlayerToSectionDialog::~PlayerToSectionDialog()
{
    delete ui;
}
