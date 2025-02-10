#ifndef DATABASE_H
#define DATABASE_H

#include "addplayerdialog.h"
#include "sectiondialog.h"
#include "tournamentdialog.h"

#include <QObject>
#include <QSqlDatabase>
#include <QFile>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool insertSection(SectionDialog::SectionInfo si);
    bool insertPlayer(AddPlayerDialog::playerInfo pi);
    bool removePlayer();
    bool removeSection();
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);
    void closeDatabase();

    TournamentDialog::Info setupTournament();


private:
    QSqlDatabase db;




};

#endif // DATABASE_H
