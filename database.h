#ifndef DATABASE_H
#define DATABASE_H

#include "addplayerdialog.h"
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>  // TODO: might remove later


class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool insert(AddPlayerDialog::playerInfo pi);
    bool remove();
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);

private:
    QSqlDatabase db;

    void closeDatabase();


};

#endif // DATABASE_H
