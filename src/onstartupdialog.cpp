#include "headers/onstartupdialog.h"
#include "ui_onstartupdialog.h"

#include <QMessageBox>

OnStartUpDialog::OnStartUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OnStartUpDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &OnStartUpDialog::newTournamentClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &OnStartUpDialog::openTournamentClicked);
}

OnStartUpDialog::~OnStartUpDialog()
{
    delete ui;
}

