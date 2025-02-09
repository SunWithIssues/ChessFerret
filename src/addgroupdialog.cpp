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

void AddGroupDialog::init(QList<QString> headers){

}

void AddGroupDialog::additionalUiSetup()
{

    ui->filePathEdit->setReadOnly(true);

    connect(ui->toolButton, &QToolButton::clicked, this, &AddGroupDialog::onToolButtonClicked);

}


void AddGroupDialog::onToolButtonClicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Choose File"),
                                                    ui->filePathEdit->text(),
                                                    tr("Spreadsheet (*.csv *.tsv)"));


    ui->filePathEdit->setText(filepath);
}
