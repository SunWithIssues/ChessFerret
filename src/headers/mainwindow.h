#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tournamentdialog.h"
#include "setupdialog.h"
#include "database.h"
#include "onstartupdialog.h"

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

    void show(OnStartUpDialog* dialog);

    void init();

    struct headerPreferences
    {
        QHash<QString, QString> *roster;
        QHash<QString, QString> *round;
        QHash<QString, QString> *pairings;
    };


signals:
    void closeOnStartUp();

public slots:



private slots:
    void newTournamentDialog();
    void loadExistingTournament();
    void openAboutDialog();
    void newSection();
    void viewSection();


    void add1Player();
    void addNPlayers();
    void withdrawPlayer();
    void removePlayer();

    void fullRedraw();

private:
    void createMenus();
    void createEmptyRoster();
    void additionalUiSetup();
    void updateTableViews();
    void resetUi();

    QWidget* emptyTabQWidget();
    void formatTableView(QTableView *tv);

    void populateHeaderPreferences();

    void debug(QModelIndex qmi, QTableView *tv);

    Ui::MainWindow *ui;
    TournamentDialog *tDialog;
    SetupDialog *sDialog;
    Database *db;
    headerPreferences *hp;

};
#endif // MAINWINDOW_H
