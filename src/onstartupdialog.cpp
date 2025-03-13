#include "headers/onstartupdialog.h"
#include "ui_onstartupdialog.h"

#include "headers/setupdialog.h"

OnStartUpDialog::OnStartUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OnStartUpDialog)
{
    ui->setupUi(this);
    ui->langComboBox->addItems(SetupDialog::populateLangChoices());

    connect(ui->newButton, &QPushButton::clicked, this, &OnStartUpDialog::newTournamentClicked);
    connect(ui->openButton, &QPushButton::clicked, this, &OnStartUpDialog::openTournamentClicked);
}

OnStartUpDialog::~OnStartUpDialog()
{
    delete ui;
}



