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

    QAbstractItemModel* selectAll();
    QAbstractItemModel* selectPlayersFromSection(QString section_name);


    int getSectionsSeq();


    bool insertTournament(TournamentInfo* ti);
    bool insertSection(SectionInfo si);
    bool insertPlayer(PlayerInfo pi);
    bool removePlayer(int id);
    bool withdrawPlayer(int id);
    bool removeSection(int id);
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);
    void closeDatabase();


    TournamentInfo* setupTournament();

public slots:
    void runSpecialQueries(QList<QString> queries);


private:
    QSqlDatabase db;

    int sectionSeq;

    QString CONNECTION_NAME;
    QString TBL_SECTIONS ;
    QString TBL_TOURNAMENT ;
    QString TBL_PLAYERS ;
    int WITHDRAW_VALUE;


};

#endif // DATABASE_H
