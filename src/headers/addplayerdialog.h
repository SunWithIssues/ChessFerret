#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H


#include "../helpers/headers/addplayer.h"

#include <QDialog>
#include <QDate>
#include <QList>

namespace Ui {
class AddPlayerDialog;
}

class AddPlayerDialog : public QDialog, public AddPlayer
{
    Q_OBJECT

public:
    explicit AddPlayerDialog(QWidget *parent = nullptr, QList<QString> sectionNames = QList<QString>());
    ~AddPlayerDialog();


private:
    Ui::AddPlayerDialog *ui;

    void additionalUiSetup();
    PlayerInfo getUiPlayerInfo();

private slots:
    void onAccepted();
    void onApplied();
    void shouldDisableButtons(QString s);


};

#endif // ADDPLAYERDIALOG_H
