#ifndef TOURNAMENTDIALOG_H
#define TOURNAMENTDIALOG_H

#include "sectiondialog.h"

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

    void init(TournamentDialog::Info ti);

    QString getTournamentName();
    QString getLocation();
    QDate getEndDate();
    QDate getBeginDate();
    QString getFilePath();
    QHash<QString, SectionDialog::SectionInfo> getSectionsInfo();
    QList<QString> getSectionNames();
    bool addSectionInfo(SectionDialog::SectionInfo si);
    void replaceSectionInfo(SectionDialog::SectionInfo si0, SectionDialog::SectionInfo si1);

signals:

private slots:
    void on_buttonBox_accepted();
    void on_toolButton_clicked();

    void addSection();
    void removeSection();
    void viewSection();

private:
    Ui::TournamentDialog *ui;

    struct Info{
        QString tournamentName;
        QString location;
        QDate beginDate;
        QDate endDate;
        QString filepath;
        // QList<SectionDialog::SectionInfo> sections;
        QHash<QString,SectionDialog::SectionInfo> sections;
    };

    Info* info;
    QHash<QString,SectionDialog::SectionInfo> tempSections;


    QString forceDbEnding(QString filepath);
    void additionalUiSetup();
};

#endif // TOURNAMENTDIALOG_H
