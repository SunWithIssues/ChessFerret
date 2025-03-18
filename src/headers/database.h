#ifndef DATABASE_H
#define DATABASE_H

#include "../helpers/headers/info.h"

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
    };

    QAbstractItemModel* selectAll();
    QAbstractItemModel* selectPlayersFromSection(QString section_name);


    int getSectionsSeq();




    bool insertTournament(TournamentInfo* ti);
    bool insertSection(SectionInfo si);
    bool insertPlayer(PlayerInfo pi);
    bool removePlayer();
    bool withdrawPlayer(int row, QString section="");
    bool removeSection();
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);
    void closeDatabase();

    QList<header> getColsPlayers();

    TournamentInfo* setupTournament();

public slots:
    void runSpecialQueries(QList<QString> queries);


private:
    QSqlDatabase db;

    QList<header> cols_players;
    QList<header> cols_sections;
    QList<header> cols_tournament;

    int sectionSeq;

    QString CONNECTION_NAME;
    QString TBL_SECTIONS ;
    QString TBL_TOURNAMENT ;
    QString TBL_PLAYERS ;


};

#endif // DATABASE_H
