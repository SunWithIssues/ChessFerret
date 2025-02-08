#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}
