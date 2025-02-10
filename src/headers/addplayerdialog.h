#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H

#include "info.h"

#include <QDialog>
#include <QDate>
#include <QList>

namespace Ui {
class AddPlayerDialog;
}

class AddPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayerDialog(QWidget *parent = nullptr);
    ~AddPlayerDialog();




    QList<PlayerInfo> getPlayers();
    void init(QList<QString> sectioinNames);


private:
    Ui::AddPlayerDialog *ui;
    QList<PlayerInfo> players;

    void onAccepted();
    void onApplied();
    void additionalUiSetup();
    void addPlayerToList();
};

#endif // ADDPLAYERDIALOG_H
