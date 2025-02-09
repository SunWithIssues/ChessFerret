#ifndef DATABASE_H
#define DATABASE_H

#include "addplayerdialog.h"

#include <QObject>

#include <QTableView>
#include <QSqlDatabase>
// #include <QDebug>  // TODO: might remove later


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
    bool insert(AddPlayerDialog::playerInfo pi);
    bool remove();
    bool openDatabase(QString filepath);
    bool newDatabase(QString filepath);

private:
    QSqlDatabase db;

    void closeDatabase();


};

#endif // DATABASE_H
