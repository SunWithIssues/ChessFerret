#ifndef TOURNAMENTDIALOG_H
#define TOURNAMENTDIALOG_H

#include "../helpers/headers/info.h"

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

    QHash<int, SectionInfo> getSectionsInfo();
    QList<int> getSectionIds();
    QList<QString> getSectionNames();

    void swapSectionIds(int index0, int index1);
    void addSectionInfo(int id, SectionInfo si);
    void replaceSectionInfo(int id, SectionInfo si);

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
    QList<int> tempSectionIds;
    QHash<int,SectionInfo> tempSections;


    QString forceDbEnding(QString filepath);
    void additionalUiSetup();
};

#endif // TOURNAMENTDIALOG_H
