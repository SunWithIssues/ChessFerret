#include "headers/database.h"
#include "headers/addplayerdialog.h"


#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMessageBox>
#include <QDebug>

Database::Database(QObject *parent)
    : QObject{parent}
{}

Database::~Database()
{}


bool Database::selectAll(QTableView *view)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM players");
    if (model->lastError().isValid())
    {
        qDebug() << "table could not be retrived";
        qDebug() << model->lastError().databaseText() << model->lastError().driverText();        return false;
        return false;
    }

    view->setModel(model);
    return true;

}

bool Database::insert(AddPlayerDialog::playerInfo pi)
{
    QSqlQuery query;
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
    // TODO:
    return false;
}

bool Database::newDatabase(QString filepath)
{

    if (openDatabase(filepath)){
        QSqlQuery query;
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
    db = QSqlDatabase::addDatabase("QSQLITE");
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
}
