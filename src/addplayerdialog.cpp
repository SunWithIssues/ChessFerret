#include "headers/addplayerdialog.h"
#include "ui_addplayerdialog.h"

#include <QDate>

AddPlayerDialog::AddPlayerDialog(QWidget *parent, QList<QString> sectionNames)
    : QDialog(parent), AddPlayer(sectionNames)
    , ui(new Ui::AddPlayerDialog)
{
    ui->setupUi(this);

    ui->birthDateEdit->setDisplayFormat("MM/dd/yyyy");
    ui->birthDateEdit->setMaximumDate(QDate::currentDate());

    ui->sectionComboBox->addItems(sectionNames);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &AddPlayerDialog::onAccepted);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &AddPlayerDialog::onApplied);
    connect(ui->nameLineEdit, &QLineEdit::textEdited, this, &AddPlayerDialog::shouldDisableButtons);

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

    ui->buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

void AddPlayerDialog::onAccepted()
{
    PlayerInfo pi = getUiPlayerInfo();
    if(!pi.player_name.isEmpty()){
        addPlayerToList(pi);
    }

}
void AddPlayerDialog::onApplied()
{
    PlayerInfo pi = getUiPlayerInfo();
    if(!pi.player_name.isEmpty()){
        addPlayerToList(pi);
    }

    additionalUiSetup();
}

PlayerInfo AddPlayerDialog::getUiPlayerInfo()
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

    return pi;
}

void AddPlayerDialog::shouldDisableButtons(QString s){
    if (!s.isEmpty()){
        ui->buttonBox->button(QDialogButtonBox::Apply)->setDisabled(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }else{
        ui->buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}
