#ifndef DATABASE_H
#define DATABASE_H

#include "info.h"

#include <QObject>
#include <QTableView>
#include <QSqlDatabase>
#include <QFile>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();


    struct header
    {
        QString name;
        QString type;
        int *character_limit;
    };

    QAbstractItemModel* selectAll();

    bool insertTournament(TournamentInfo* ti);
    bool insertSection(SectionInfo si);
    bool insertPlayer(PlayerInfo pi);
    bool removePlayer();
    bool removeSection();
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);
    void closeDatabase();

    TournamentInfo* setupTournament();


private:
    QSqlDatabase db;




};

#endif // DATABASE_H
