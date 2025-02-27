#include "headers/tournamentdialog.h"
#include "ui_tournamentdialog.h"
#include "headers/sectiondialog.h"


#include <QDir>
#include <QList>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFileDialog>


TournamentDialog::TournamentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TournamentDialog)
{
    ui->setupUi(this);
    additionalUiSetup();
}

TournamentDialog::~TournamentDialog()
{
    delete ui;
}

void TournamentDialog::additionalUiSetup()
{
    ui->savePathEdit->setText(QDir::homePath());

    ui->beginDateEdit->setDisplayFormat("MM/dd/yyyy");
    ui->endDateEdit->setDisplayFormat("MM/dd/yyyy");

    ui->beginDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate());

    ui->buttonBox->setDisabled(true);

    connect(ui->addSectionButton, &QPushButton::released, this, &TournamentDialog::addSection);
    connect(ui->removeButton, &QPushButton::released, this, &TournamentDialog::removeSection);
    connect(ui->viewEditButton, &QPushButton::released, this, &TournamentDialog::viewSection);

}

void TournamentDialog::init(TournamentInfo* ti)
{
    info = ti;
}
void TournamentDialog::on_buttonBox_accepted()
{
    // Sets Tournament Info
    info = new TournamentInfo;
    info->tournamentName = ui->tournamentNameEdit->text();
    info->location = ui->locationEdit->text();
    info->beginDate = ui->beginDateEdit->date();
    info->endDate = ui->endDateEdit->date();
    info->filepath = forceDbEnding(ui->savePathEdit->text());
    info->sections = tempSections;
    info->federation = ui->fedComboBox->currentText();


    // Removes existing filepath for overwriting purposes in database.cpp
    if(QFile(info->filepath).exists()){
        QFile::remove(info->filepath);
    }
}
TournamentInfo* TournamentDialog::getTournamentInfo()
{
    return info;
}
QString TournamentDialog::getTournamentName()
{
    return info->tournamentName;
}
QString TournamentDialog::getLocation()
{
    return info->location;
}
QDate TournamentDialog::getEndDate()
{
    return info->endDate;
}
QDate TournamentDialog::getBeginDate()
{
    return info->beginDate;
}
QString TournamentDialog::getFilePath()
{
    return info->filepath;
}
QHash<QString,SectionInfo> TournamentDialog::getSectionsInfo()
{
    return info->sections;
}
QList<QString> TournamentDialog::getSectionNames()
{
    return info->sections.keys();
}


bool TournamentDialog::addSectionInfo(SectionInfo si)
{
    if(!info)
    {
        qDebug() << "Tournament Not Initialized";
        return false;
    }

    info->sections.insert(si.sectionName, si);
    return true;
}

void TournamentDialog::replaceSectionInfo(SectionInfo si0, SectionInfo si1)
{
    // Remove
    info->sections.remove(si0.sectionName);
    // Add
    info->sections.insert(si1.sectionName, si1);
}


void TournamentDialog::on_toolButton_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                ui->savePathEdit->text(),
                                tr("Database (*.db)"));


    ui->savePathEdit->setText(forceDbEnding(filepath));
}






void TournamentDialog::viewSection()
{
    auto selected = ui->sectionsTreeWidget->selectedItems();
    if(selected.count() < 1){
        return;
    }
    SectionInfo si = tempSections.value(selected.at(0)->text(0));

    SectionDialog dialog(this);
    dialog.init(si);

    if(dialog.exec() == QDialog::Accepted)
    {
        if(dialog.info.sectionName == selected.at(0)->text(0)){
            tempSections[selected.at(0)->text(0)] = dialog.info;
        }
        else{

            //-----
            // ADD NEW NAME
            //-----

            // Add info to temporary section list
            tempSections.insert(dialog.info.sectionName, dialog.info);

            // Update UI accordingly
            ui->sectionsTreeWidget->addTopLevelItem(new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr),
                QStringList() << dialog.info.sectionName
                ));

            //-----
            // REMOVE OLD NAME
            //-----
            tempSections.remove(selected.at(0)->text(0));
            delete selected.at(0);


        }

    }

}
void TournamentDialog::removeSection(){
    auto selected = ui->sectionsTreeWidget->selectedItems();
    if(selected.count() < 1){
        return;
    }
    if(tempSections.count() == 1)
    {
        ui->buttonBox->setDisabled(true);
    }

    tempSections.remove(selected.at(0)->text(0));
    delete selected.at(0);


}

void TournamentDialog::addSection()
{
    //Open New Section Dialog
    SectionDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        // Add info to temporary section list
        tempSections.insert(dialog.info.sectionName, dialog.info);

        // Update UI accordingly
        ui->sectionsTreeWidget->addTopLevelItem(new QTreeWidgetItem(
                        static_cast<QTreeWidget *>(nullptr),
                        QStringList() << dialog.info.sectionName
            ));

        ui->buttonBox->setDisabled(false);
    }
}

QString TournamentDialog::forceDbEnding(QString filepath){
    if(!filepath.endsWith(".db")){
        filepath.append(".db");
    }

    return filepath;
}

