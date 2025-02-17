#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

#include <QFileDialog>

AddGroupDialog::AddGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
    additionalUiSetup();
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::init(QList<QString> headers)
{

}

void AddGroupDialog::additionalUiSetup()
{
    // File Path Actions
    ui->filePathEdit->setReadOnly(true);
    connect(ui->toolButton, &QToolButton::clicked, this, &AddGroupDialog::onToolButtonClicked);

    // Header Related Actions
    ui->headersCheckBox->setChecked(false);
    ui->vRadioButton->setDisabled(true);
    ui->hRadioButton->setDisabled(true);

    connect(ui->headersCheckBox, &QCheckBox::stateChanged, this, &AddGroupDialog::shouldDisableHeaderStyle);

    // Field Separator
    QStringList seps = {",", ";", "/", tr("tab")};
    ui->fieldSepComboBox->addItems(seps);
    ui->fieldSepComboBox->setEditable(true);

    // Automate Button
    ui->autoButton->setDisabled(true);

}


void AddGroupDialog::onToolButtonClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Choose File"),
                                                    ui->filePathEdit->text(),
                                                    tr("Spreadsheet (*.csv *.tsv)"));


    if(filepath != ""){
        ui->filePathEdit->setText(filepath);

        //
        ui->autoButton->setDisabled(false);

        if(filepath.last(4) == ".tsv")
            ui->fieldSepComboBox->setCurrentIndex(3);
    }

}

void AddGroupDialog::shouldDisableHeaderStyle()
{
    if(ui->headersCheckBox->checkState() == Qt::Checked){
        ui->hRadioButton->setDisabled(false);
        ui->vRadioButton->setDisabled(false);
    }
    else
    {
        ui->hRadioButton->setDisabled(true);
        ui->vRadioButton->setDisabled(true);
    }
}
