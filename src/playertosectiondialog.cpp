#include "headers/playertosectiondialog.h"
#include "ui_playertosectiondialog.h"

PlayerToSectionDialog::PlayerToSectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerToSectionDialog)
{
    ui->setupUi(this);
    this->windowTitle(tr("Match Players to Sections"));
}

PlayerToSectionDialog::~PlayerToSectionDialog()
{
    delete ui;
}
