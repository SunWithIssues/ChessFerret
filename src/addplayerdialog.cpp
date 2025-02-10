#include "headers/addplayerdialog.h"
#include "ui_addplayerdialog.h"


#include <QDate>


AddPlayerDialog::AddPlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPlayerDialog)
{
    ui->setupUi(this);

    ui->birthDateEdit->setDisplayFormat("MM/dd/yyyy");
    ui->birthDateEdit->setMaximumDate(QDate::currentDate());

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &AddPlayerDialog::onAccepted);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &AddPlayerDialog::onApplied);

    additionalUiSetup();
}

AddPlayerDialog::~AddPlayerDialog()
{
    delete ui;
}

void AddPlayerDialog::additionalUiSetup(){

    ui->nameLineEdit->setText("");
    ui->rtgFideLineEdit->setText("");
    ui->rtgLineEdit->setText("");
    ui->birthDateEdit->setDate(QDate(2000,1,1));
    ui->genderEdit->setText("");
    ui->fideIDEdit->setText("");
    ui->natIdEdit->setText("");
    ui->teamsEdit->setText("");

}

void AddPlayerDialog::init(QList<QString> sectionNames)
{
    ui->sectionComboBox->addItems(sectionNames);
}

void AddPlayerDialog::onAccepted()
{
    addPlayerToList();

}
void AddPlayerDialog::onApplied()
{
    addPlayerToList();
    additionalUiSetup();
}

QList<PlayerInfo> AddPlayerDialog::getPlayers()
{
    return players;
}


void AddPlayerDialog::addPlayerToList()
{
    PlayerInfo pi;

    pi.birthdate = ui->birthDateEdit->date();
    pi.gender = ui->genderEdit->text();
    pi.id_fide = ui->fideIDEdit->text();
    pi.id_national = ui->natIdEdit->text();
    pi.player_name = ui->nameLineEdit->text();
    pi.rtg_fide = ui->rtgFideLineEdit->text().toInt();
    pi.rtg_national = ui->rtgLineEdit->text().toInt();
    pi.section = ui->sectionComboBox->currentText();
    pi.teams = ui->teamsEdit->text();

    players.append(pi);
}
