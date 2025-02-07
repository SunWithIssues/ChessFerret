#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H

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

    struct playerInfo
    {
        QString player_name;
        QDate birthdate;
        QString gender;
        QString id_national;
        int rtg_national;
        QString id_fide;
        int rtg_fide;
        QString section;
        QString teams;

    };


    QList<AddPlayerDialog::playerInfo> getPlayers();
    void init(QList<QString> sectioinNames);


private:
    Ui::AddPlayerDialog *ui;
    QList<AddPlayerDialog::playerInfo> players;

    void onAccepted();
    void onApplied();
    void additionalUiSetup();
    void addPlayerToList();
};

#endif // ADDPLAYERDIALOG_H
