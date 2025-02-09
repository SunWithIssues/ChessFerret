#include "headers/database.h"
#include "headers/addplayerdialog.h"

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


bool Database::insert(AddPlayerDialog::playerInfo pi)
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
        qDebug() << "Did not insert";
        qDebug() << query.lastError().databaseText() << query.lastError().driverText();        return false;
    }
    return true;

}
bool Database::remove()
{
    return false;
}

bool Database::newDatabase(QString filepath)
{

    // TODO:
    // Update database with information

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
                    "section VARCHAR(50) NOT NULL,"
                    "teams VARCHAR(100))";

        if(!query.exec(q))
        {
            qDebug() << "DataBase: error of create ";
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
        qDebug() << "Did not open database " << filepath;
        return false;
    }
}

void Database::closeDatabase()
{
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(CONNECTION_NAME);
}
