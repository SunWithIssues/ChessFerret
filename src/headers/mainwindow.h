#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tournamentdialog.h" //TODO: name change in the future
#include "setupdialog.h"
#include "database.h"

#include <QMainWindow>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct headerPreferences
    {
        QVector<Database::header> *roster;
        QVector<Database::header> *round;
        QVector<Database::header> *pairings;
    };


protected:

public slots:


private slots:
    void newTournamentDialog();
<<<<<<< HEAD
=======
    void add1Player();
    void openSetupDialog();
    void newSection();
    void viewSection();
>>>>>>> main
    void loadExistingTournament();

    void openSetupDialog();

    void add1Player();
    void addNPlayers();

    void newSection();


private:
    void createMenus();
    void createEmptyRoster();
    void additionalUiSetup();
    void updateTableViews();
    QVector<headerPreferences> populateHeaderPreferences();


    Ui::MainWindow *ui;
    TournamentDialog *tDialog;
    SetupDialog *sDialog;
    Database *db;

};
#endif // MAINWINDOW_H
