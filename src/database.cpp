#include "headers/database.h"
#include "headers/info.h"


#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


#define CONNECTION_NAME "FC_DB"

Database::Database(QObject *parent)
    : QObject{parent}
{}

Database::~Database()
{

    closeDatabase();

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
        qDebug() << "Did not insert <section>";
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();
        return false;
    }
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
    return false;
}

TournamentInfo Database::setupTournament()
{

    TournamentInfo tInfo;


    //TODO::IMPORTANT:: get the info from tables <sections> and <tournament>
    return tInfo;
}


bool Database::newDatabase(QString filepath)
{

    if (openDatabase(filepath)){
        QSqlQuery query(db);
        QString q = "CREATE TABLE players"
                    "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "ranking INTEGER, "
                    "name VARCHAR(100),"
                    "birthdate DATE,"
                    "gender VARCHAR(3),"
                    "id_national VARCHAR(30),"
                    "rtg_national INTEGER,"
                    "id_fide VARCHAR(30),"
                    "rtg_fide INTEGER,"
                    "section TEXT NOT NULL,"
                    "teams VARCHAR(100))";

        if(!query.exec(q))
        {
            qDebug() << "DataBase <players>: error of create ";
            qDebug() << query.lastError().text();
            return false;
        };

        q = "CREATE TABLE sections"
            "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "section_name TEXT NOT NULL,"
            "section_name_print TEXT,"
            "num_rounds INTEGER,"
            "pairing_style TEXT,"
            "scoring_style TEXT,"
            "min_rtg INTEGER,"
            "max_rtg INTEGER,"
            "time_control TEXT))";

        if(!query.exec(q))
        {
            qDebug() << "DataBase <sections>: error of create ";
            qDebug() << query.lastError().text();
            return false;
        };

        q = "CREATE TABLE tournament"
            "(tournament_name TEXT NOT NULL,"
            "location TEXT,"
            "begin_date DATE,"
            "end_date DATE))";

        if(!query.exec(q))
        {
            qDebug() << "DataBase <tournament>: error of create ";
            qDebug() << query.lastError().text();
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
