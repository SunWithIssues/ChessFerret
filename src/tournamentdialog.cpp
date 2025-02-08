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
    connect(ui->addSectionButton, &QPushButton::released, this, &TournamentDialog::addSection);
    connect(ui->removeButton, &QPushButton::released, this, &TournamentDialog::removeSection);
    connect(ui->viewEditButton, &QPushButton::released, this, &TournamentDialog::viewSection);
}


void TournamentDialog::on_buttonBox_accepted()
{
    info = new Info;
    info->tournamentName = ui->tournamentNameEdit->text();
    info->location = ui->locationEdit->text();
    info->beginDate = ui->beginDateEdit->date();
    info->endDate = ui->endDateEdit->date();
    info->filepath = forceDbEnding(ui->savePathEdit->text());
    info->sections = tempSections;


    // TODO::IMPORTANT:: check if filepath exist on this level
    // if(!QFile(filepath).exists()){
    //     // Give warning overriding existing tournament
    //     QMessageBox msgBox;
    //     msgBox.setText("You are about to override an existing tournament.");
    //     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    //     if(msgBox.exec() == QMessageBox::Cancel){
    //         return false;
    //     }
    // }
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

QHash<QString,SectionDialog::SectionInfo> TournamentDialog::getSectionsInfo()
{
    return info->sections;
}

QList<QString> TournamentDialog::getSectionNames()
{
    return info->sections.keys();
}


bool TournamentDialog::addSectionInfo(SectionDialog::SectionInfo si)
{
    if(!info)
    {
        qDebug() << "Tournament Not Initialized";
        return false;
    }

    info->sections.insert(si.sectionName, si);
    return true;
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
    SectionDialog::SectionInfo si = tempSections.value(selected.at(0)->text(0));

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
    }
}

QString TournamentDialog::forceDbEnding(QString filepath){
    if(!filepath.endsWith(".db")){
        filepath.append(".db");
    }

    return filepath;
}

