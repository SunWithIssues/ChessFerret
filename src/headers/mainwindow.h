#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tournamentdialog.h" //TODO: name change in the future
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

    struct header
    {
        QString name;
        QString type;
    };

    struct headerPreferences
    {
        QVector<header> *roster;
        QVector<header> *round;
        QVector<header> *pairings;
    };


signals:
    void closeOnStartUp();

public slots:


private slots:
    void newTournamentDialog();
    void add1Player();
    void openSetupDialog();
    void openAboutDialog();
    void newSection();
    void viewSection();
    void loadExistingTournament();

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
