#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tournamentdialog.h"
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
        QHash<QString, QString> *roster;
        QHash<QString, QString> *round;
        QHash<QString, QString> *pairings;
    };


protected:

public slots:


private slots:
    void newTournamentDialog();
    void loadExistingTournament();
    void openSetupDialog();

    void newSection();
    void viewSection();


    void add1Player();
    void addNPlayers();



private:
    void createMenus();
    void createEmptyRoster();
    void additionalUiSetup();
    void restartUiState();
    void updateTableViews();
    QWidget* emptyTabQWidget();
    void formatTableView(QTableView *tv);

    void populateHeaderPreferences();


    Ui::MainWindow *ui;
    TournamentDialog *tDialog;
    SetupDialog *sDialog;
    Database *db;
    headerPreferences *hp;

};
#endif // MAINWINDOW_H
