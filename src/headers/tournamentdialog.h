#ifndef TOURNAMENTDIALOG_H
#define TOURNAMENTDIALOG_H

#include "info.h"

#include <QDialog>
#include <QDate>

namespace Ui {
class TournamentDialog;
}

class TournamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentDialog(QWidget *parent = nullptr);
    ~TournamentDialog();

    void init(TournamentInfo* ti);

    QString getTournamentName();
    QString getLocation();
    QDate getEndDate();
    QDate getBeginDate();
    QString getFilePath();
    TournamentInfo* getTournamentInfo();
    QHash<QString, SectionInfo> getSectionsInfo();
    QList<QString> getSectionNames();
    bool addSectionInfo(SectionInfo si);
    void replaceSectionInfo(SectionInfo si0, SectionInfo si1);

signals:

private slots:
    void on_buttonBox_accepted();
    void on_toolButton_clicked();

    void addSection();
    void removeSection();
    void viewSection();

private:
    Ui::TournamentDialog *ui;



    TournamentInfo* info;
    QList<QString> tempSectionNames;
    QHash<QString,SectionInfo> tempSections;


    QString forceDbEnding(QString filepath);
    void additionalUiSetup();
};

#endif // TOURNAMENTDIALOG_H
