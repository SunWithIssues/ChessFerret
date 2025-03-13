#include "headers/aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDebug>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QPixmap logo(":/images/chessFerret-logo.png");
    ui->logoLabel->setPixmap(logo);

    ui->versionDetailLabel->setText(tr("Version:"));
    ui->versionNumberLabel->setText("0.0 Beta"); //TODO: pull from somewhere

    ui->detailLabel->setText("Created by Anya E. \nLicensed under GNU General Public License, Version 3.");
    ui->detailLabel->setAlignment(Qt::AlignCenter);

    ui->hyperlinkLabel->setText("<a href=\"https://github.com/SunWithIssues/ChessFerret\">Source Code</a>");
    ui->hyperlinkLabel->setTextFormat(Qt::RichText);
    ui->hyperlinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->hyperlinkLabel->setOpenExternalLinks(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
