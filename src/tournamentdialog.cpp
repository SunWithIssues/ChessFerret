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



void TournamentDialog::init(TournamentInfo* ti)
{
    info = ti;
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
QHash<int,SectionInfo> TournamentDialog::getSectionsInfo()
{
    return info->sections;
}
QList<int> TournamentDialog::getSectionIds()
{
    return info->sectionIds;
}

QList<QString> TournamentDialog::getSectionNames()
{
    QList<QString> sn;
    for(auto id: info->sectionIds)
    {
        sn.append(info->sections.value(id).sectionName);
    }
    return sn;
}

void TournamentDialog::swapSectionIds(int index0, int index1)
{
    info->sectionIds.swapItemsAt(index0, index1);
}

void TournamentDialog::addSectionInfo(int id, SectionInfo si)
{
    info->sections.insert(id, si);
    info->sectionIds.append(id);
}

void TournamentDialog::replaceSectionInfo(int id, SectionInfo si)
{
    // Replaces old value at id
    info->sections.insert(id, si);

}

// -------------------------------------
// PRIVATE FUNCTIONS
// -------------------------------------
void TournamentDialog::additionalUiSetup()
{
    ui->savePathEdit->setText(QDir::homePath());
    connect(ui->addSectionButton, &QPushButton::released, this, &TournamentDialog::addSection);
    connect(ui->removeButton, &QPushButton::released, this, &TournamentDialog::removeSection);
    connect(ui->viewEditButton, &QPushButton::released, this, &TournamentDialog::viewSection);
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
    info->sectionIds = tempSectionIds;


    // Removes existing filepath for overwriting purposes in database.cpp
    if(QFile(info->filepath).exists()){
        QFile::remove(info->filepath);
    }
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
    int idx = ui->sectionsTreeWidget->currentIndex().row();
    int id = tempSectionIds.value(idx);
    SectionInfo si = tempSections.value(id);


    SectionDialog dialog(this);
    dialog.init(si);

    if(dialog.exec() == QDialog::Accepted)
    {
        if(dialog.info.sectionName != selected.at(0)->text(0)){
            // Update UI accordingly
            ui->sectionsTreeWidget->addTopLevelItem(new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr),
                QStringList() << dialog.info.sectionName
                ));
            delete selected.at(0);
        }


        tempSections.insert(id, dialog.info);


    }

}
void TournamentDialog::removeSection(){
    auto selected = ui->sectionsTreeWidget->selectedItems();
    if(selected.count() < 1){
        return;
    }

    int idx = ui->sectionsTreeWidget->currentIndex().row();
    int id = tempSectionIds.value(idx);

    tempSections.remove(id);
    tempSectionIds.remove(idx);

    delete selected.at(0);

}

void TournamentDialog::addSection()
{
    //Open New Section Dialog
    SectionDialog dialog(this);
    int idx = tempSectionIds.count() + 1;
    if(dialog.exec() == QDialog::Accepted)
    {
        // Add info to temporary section list
        tempSections.insert(idx, dialog.info);
        tempSectionIds.append(idx);

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

