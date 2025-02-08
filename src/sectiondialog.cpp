#include "headers/sectiondialog.h"
#include "ui_sectiondialog.h"

SectionDialog::SectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SectionDialog)
{
    ui->setupUi(this);
    additionalUiSetup();


}

void SectionDialog::init(SectionDialog::SectionInfo si)
{

    ui->nameEdit->setText(si.sectionName);
    ui->maxSpinBox->setValue(si.ratingRangeMax);
    ui->minSpinBox->setValue(si.ratingRangeMin);
    ui->roundsSpinBox->setValue(si.numRounds);
    ui->printNameEdit->setText(si.sectionNameForPrinting);

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

}



