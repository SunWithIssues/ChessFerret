#include "headers/database.h"

#include "headers/info.h"


#include <QStringBuilder>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>




Database::Database(QObject *parent)
    : QObject{parent}
{
    sectionSeq = 0; // TODO: maybe better inside newTournament

    CONNECTION_NAME = "FC_DB";
    TBL_SECTIONS = "sections";
    TBL_TOURNAMENT = "tournament";
    TBL_PLAYERS = "players";

    cols_tournament = {
        header{"tournament_name", "TEXT"}, header{"location", "TEXT"}, header{"begin_date","DATE"},
        header{"end_date", "DATE"}
    };
    cols_sections = {
        header{"section_name", "TEXT"}, header{"section_name_print", "TEXT"},
        header{"num_rounds", "INTEGER"}, header{"pairing_style", "TEXT"},
        header{"scoring_style", "TEXT"}, header{"min_rtg", "INTEGER"},
        header{"max_rtg", "INTEGER"}, header{"time_control", "TEXT"}
    };
    cols_players = {
        header{"name", "TEXT"}, header{"ranking", "INTEGER"}, header{"birthdate", "DATE"},
        header{"gender", "TEXT"}, header{"id_national", "TEXT"},
        header{"rtg_national ","INTEGER"}, header{"id_fide","TEXT"},
        header{"rtg_fide","INTEGER"}, header{"section", "TEXT"}, header{"teams", "TEXT"}
    };
}

Database::~Database()
{
    closeDatabase();
}

int Database::getSectionsSeq(){
    return sectionSeq;
}

QList<Database::header> Database::getColsPlayers()
{
    return cols_players;
}

bool runSpecialQueries(QList<QString> queries)
{
    QString connection = "CSV_DB";
    QSqlDatabase dbTemp = QSqlDatabase::addDatabase("QSQLITE", connection);
    if(!dbTemp.open()){
        qDebug() << "special query failed: no connection ";
        return false;
    }


    QSqlQuery query(dbTemp);
    qDebug() << "queries " << queries;
    foreach(auto q, queries){
        query.prepare(q);
        if(!query.exec()){
            qDebug() << "special query failed" << q;
            dbTemp.close();
            QSqlDatabase::removeDatabase(connection);
            return false;
        }
    }

    dbTemp.close();
    QSqlDatabase::removeDatabase(connection);
    return true;
}

QAbstractItemModel* Database::selectPlayersFromSection(QString section_name)
{
    QString q = "SELECT * FROM players WHERE section = '" % section_name % "'";
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q, db);
    if (model->lastError().isValid())
    {
        qDebug() << "table could not be retrived";
        qDebug() << model->lastError().databaseText() << model->lastError().driverText();
        return nullptr;
    }
    return model;
}

QAbstractItemModel* Database::selectAll()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM players", db);
    if (model->lastError().isValid())
    {
        qDebug() << "table could not be retrived";
        qDebug() << model->lastError().databaseText() << model->lastError().driverText();
        return nullptr;
    }
    return model;

}


bool Database::insertTournament(TournamentInfo *ti)
{
    QSqlQuery query(db);
    QString q = "INSERT INTO tournament ( tournament_name,"
                "location, "
                "begin_date, "
                "end_date )"
                "VALUES (:tName, :loc, :bDate, :eDate)";

    query.prepare(q);
    query.bindValue(":tName", ti->tournamentName);
    query.bindValue(":loc", ti->location);
    query.bindValue(":bDate", ti->beginDate);
    query.bindValue(":eDate", ti->endDate);

    if(!query.exec())
    {
        qDebug() << "Did not insert:" << TBL_TOURNAMENT;
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();
        return false;
    }
    return true;

}
bool Database::insertSection(SectionInfo si)
{
    QSqlQuery query(db);
    QString q = "INSERT INTO sections ( section_name,"
                                        "section_name_print,"
                                        "num_rounds,"
                                        "pairing_style,"
                                        "scoring_style,"
                                        "min_rtg,"
                                        "max_rtg,"
                                        "time_control )"
                "VALUES (:sName, :sNamePrint, :nRounds, :pStyle, :sStyle, "
                        ":minRtg, :maxRtg, :tControl)";

    query.prepare(q);
    query.bindValue(":sName", si.sectionName);
    query.bindValue(":sNamePrint", si.sectionNameForPrinting);
    query.bindValue(":nRounds", si.numRounds);
    query.bindValue(":pStyles", si.pairingRule);
    query.bindValue(":sStyle", si.scoringStyle);
    query.bindValue(":minRtg", si.ratingRangeMin);
    query.bindValue(":maxRtg", si.ratingRangeMax);
    query.bindValue(":tControl", si.timeControl);

    if(!query.exec())
    {
        qDebug() << "Did not insert:" << TBL_SECTIONS;
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();
        return false;
    }

    sectionSeq++;

    return true;
}
bool Database::insertPlayer(PlayerInfo pi)
{
    QSqlQuery query(db);
    QString q = "INSERT INTO players (  birthdate, "
                                        "name,"
                                        "gender,"
                                        "id_national,"
                                        "rtg_national,"
                                        "id_fide,"
                                        "rtg_fide,"
                                        "section ,"
                                        "teams )"
                "VALUES (:birthdateVal, :nameVal, :genderVal, :id_nationlVal,  "
                        ":rtg_nationalVal, :id_fideVal, :rtg_fideVal, :sectionVal, "
                        ":teamsVal)";

    query.prepare(q);
    query.bindValue(":birthdateVal", pi.birthdate);
    query.bindValue(":nameVal", pi.player_name);
    query.bindValue(":genderVal", pi.gender);
    query.bindValue(":id_nationalVal", pi.id_national);
    query.bindValue(":rtg_nationalVal", pi.rtg_national);
    query.bindValue(":id_fideVal", pi.id_fide);
    query.bindValue(":rtg_fideVal", pi.rtg_fide);
    query.bindValue(":sectionVal", pi.section);
    query.bindValue(":teamsVal", pi.teams);

    if(!query.exec())
    {
        qDebug() << "Did not insert <player>";
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();
        return false;
    }
    return true;

}
bool Database::removePlayer()
{
    // TODO:
    return false;
}



TournamentInfo* Database::setupTournament()
{

    QSqlQuery query(db);

    QString q = "SELECT seq FROM sqlite_sequence WHERE name = " % TBL_SECTIONS;
    query.prepare(q);
    if(query.exec()){
        sectionSeq = query.value(0).toInt();
    }
    else{ sectionSeq = 0; }

    q = "SELECT * FROM " % TBL_SECTIONS;
    query.prepare(q);
    query.exec();

    SectionInfo si;
    int idx, id;
    QHash<int, SectionInfo> sections;
    QList<int> sectionIds;
    while(query.next())
    {
        idx = query.record().indexOf("section_name");
        si.sectionName = query.value(idx).toString();

        idx = query.record().indexOf("section_name_print");
        si.sectionNameForPrinting = query.value(idx).toString();

        idx = query.record().indexOf("num_rounds");
        si.numRounds = query.value(idx).toInt();

        idx = query.record().indexOf("pairing_style");
        si.pairingRule = query.value(idx).toString();

        idx = query.record().indexOf("scoring_style");
        si.scoringStyle = query.value(idx).toString();

        idx = query.record().indexOf("min_rtg");
        si.ratingRangeMin = query.value(idx).toInt();

        idx = query.record().indexOf("max_rtg");
        si.ratingRangeMax = query.value(idx).toInt();

        idx = query.record().indexOf("time_control");
        si.timeControl = query.value(idx).toString();

        idx = query.record().indexOf("id");
        id = query.value(idx).toInt();

        sections.insert(id, si);
        sectionIds.append(id);
    }



    q = "SELECT * FROM " % TBL_TOURNAMENT;
    query.prepare(q);
    query.exec();

    if(!query.next())
    {
        qDebug() << "could not read:" << TBL_TOURNAMENT;
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();
        return nullptr;
    }

    TournamentInfo *ti = new TournamentInfo();

    idx = query.record().indexOf("begin_date");
    ti->beginDate = query.value(idx).toDate();

    idx = query.record().indexOf("end_date");
    ti->endDate = query.value(idx).toDate();

    idx = query.record().indexOf("tournament_name");
    ti->tournamentName = query.value(idx).toString();

    idx = query.record().indexOf("location");
    ti->location= query.value(idx).toString();

    ti->sections = sections;
    ti->sectionIds = sectionIds;
    ti->filepath = db.databaseName();

    return ti;
}


bool Database::newDatabase(QString filepath)
{

    if (openDatabase(filepath)){
        QSqlQuery query(db);
        QString q = "CREATE TABLE players"
                    "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT,"
                    "ranking INTEGER, "
                    "birthdate DATE,"
                    "gender TEXT,"
                    "id_national TEXT,"
                    "rtg_national INTEGER,"
                    "id_fide TEXT,"
                    "rtg_fide INTEGER,"
                    "section TEXT NOT NULL,"
                    "teams TEXT)";

        if(!query.exec(q))
        {
            qDebug() << "DataBase " % TBL_PLAYERS % ": error of create ";
            qDebug() << query.lastError().databaseText() << query.lastError().driverText();
            return false;
        };


        q = "CREATE TABLE sections "
            "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "section_name PRIMARY KEY,"
            "section_name_print TEXT,"
            "num_rounds INTEGER,"
            "pairing_style TEXT,"
            "scoring_style TEXT,"
            "min_rtg INTEGER,"
            "max_rtg INTEGER,"
            "time_control TEXT)";

        if(!query.exec(q))
        {
            qDebug() << "DataBase " % TBL_SECTIONS % ": error of create ";
            qDebug() << query.lastError().databaseText() << query.lastError().driverText();
            return false;
        };


        q = "CREATE TABLE tournament"
            "(tournament_name TEXT NOT NULL,"
            "location TEXT,"
            "begin_date DATE,"
            "end_date DATE)";

        if(!query.exec(q))
        {
            qDebug() << "DataBase " % TBL_TOURNAMENT % ": error of create ";
            qDebug() << query.lastError().databaseText() << query.lastError().driverText();
            return false;
        };

        return true;
    }
    return false;
}
bool Database::openDatabase(QString filepath)
{
    //TODO: figure out what I am doing here
    db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    db.setDatabaseName(filepath);
    if(db.open()){
        return true;
    } else {
        qDebug() << "Did not open database at " << filepath;
        return false;
    }
}

void Database::closeDatabase()
{
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(CONNECTION_NAME);
}
