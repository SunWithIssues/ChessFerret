#include "headers/sectiondialog.h"
#include "ui_sectiondialog.h"

SectionDialog::SectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SectionDialog)
{
    pairingStyles = {
            {SWISS, "Swiss"}, {DOUBLE_SWISS, "Double Swiss"},
            {ROUND_ROBIN, "Round Robin"}, {LADDER, "Ladder"},
            {SWISS_PLUS_TWO, "Swiss Plus Two"}
    };
    scoringstyles = {
        {REGULAR, "Regular"}, {ROLLINS_MILITARY, "Rollins Military"},
        {TOP_SCORE, "Top Score"}
    };

    ui->setupUi(this);
    additionalUiSetup();

}

void SectionDialog::init(SectionInfo si)
{

    ui->nameEdit->setText(si.sectionName);
    ui->maxSpinBox->setValue(si.ratingRangeMax);
    ui->minSpinBox->setValue(si.ratingRangeMin);
    ui->roundsSpinBox->setValue(si.numRounds);
    ui->printNameEdit->setText(si.sectionNameForPrinting);
    ui->timeControlEdit->setText(si.timeControl);
    ui->pairingComboBox->setCurrentIndex(ui->pairingComboBox->findText(si.pairingRule));

}


SectionDialog::~SectionDialog()
{
    delete ui;
}


void SectionDialog::on_buttonBox_accepted()
{
    info.sectionName = ui->nameEdit->text();
    info.numRounds = ui->roundsSpinBox->value();
    info.ratingRangeMax = ui->maxSpinBox->value();
    info.ratingRangeMin = ui->minSpinBox->value();
    info.sectionNameForPrinting = ui->printNameEdit->text();
    info.timeControl = ui->timeControlEdit->text();
    info.pairingRule = ui->pairingComboBox->currentText();
}

void SectionDialog::additionalUiSetup()
{
    ui->rtgLabel->setText(tr("Rating Range"));

    ui->maxLabel->setText(tr("Max"));
    ui->maxSpinBox->setMinimum(0);
    ui->maxSpinBox->setMaximum(9999);
    ui->maxSpinBox->setValue(9999);

    ui->minLabel->setText(tr("Min"));
    ui->minSpinBox->setMinimum(0);
    ui->minSpinBox->setMaximum(9999);
    ui->minSpinBox->setValue(0);

    ui->roundsLabel->setText(tr("Rounds"));
    ui->roundsSpinBox->setMinimum(1);
    ui->roundsSpinBox->setMaximum(999);
    ui->roundsSpinBox->setValue(4);

    ui->pairingComboBox->addItems(pairingStyles.values());
    ui->pairingComboBox->setCurrentIndex(ui->pairingComboBox->findText(
        pairingStyles.value(SWISS)
        ));

}



