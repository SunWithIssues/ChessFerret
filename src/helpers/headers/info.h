#ifndef INFO_H
#define INFO_H


#include <QString>
#include <QHash>
#include <QDate>
#include <QList>


struct PlayerInfo
{
    QString player_name;
    QDate birthdate;
    QString gender;
    QString id_national;
    int rtg_national;
    QString id_fide;
    int rtg_fide;
    QString section;
    QString teams;

};

struct SectionInfo
{
    int sectionId;

    QString sectionName;
    int numRounds;

    // Pairing Attributes
    // TODO: these are comboBoxes
    QString pairingRule;
    QString scoringStyle;

    // Database Validators
    int ratingRangeMin;
    int ratingRangeMax;

    // Printing Specific Attributes
    QString sectionNameForPrinting;
    QString timeControl;
};

struct TournamentInfo{
    QString tournamentName;
    QString federation;
    QString location;
    QDate beginDate;
    QDate endDate;
    QString filepath;
    bool isGameStarted;

    QList<int> sectionIds;
    QHash<int,SectionInfo> sections;
};


#endif // INFO_H
