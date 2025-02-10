#ifndef DATABASE_H
#define DATABASE_H

<<<<<<< HEAD
#include "addplayerdialog.h"

#include <QObject>

#include <QTableView>
#include <QSqlDatabase>
// #include <QDebug>  // TODO: might remove later

=======
#include "info.h"

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
>>>>>>> main

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

<<<<<<< HEAD
    struct header
    {
        QString name;
        QString type;
        int *character_limit;
    };

    QAbstractItemModel* selectAll();
    bool insert(AddPlayerDialog::playerInfo pi);
    bool remove();
=======
    bool insertTournament(TournamentInfo* ti);
    bool insertSection(SectionInfo si);
    bool insertPlayer(PlayerInfo pi);
    bool removePlayer();
    bool removeSection();
>>>>>>> main
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);
    void closeDatabase();

    TournamentInfo* setupTournament();


private:
    QSqlDatabase db;




};

#endif // DATABASE_H
