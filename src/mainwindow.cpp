#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/tournamentdialog.h"
#include "headers/setupdialog.h"
#include "headers/sectiondialog.h"
#include "headers/addplayerdialog.h"
#include "headers/onstartupdialog.h"

#include <QMenu>
#include <QDebug>
#include <QTabWidget>
#include <QFileDialog>
#include <QTableWidget>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    createMenus();
    additionalUiSetup();

    db = new Database();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}


void MainWindow::show()
{
    qDebug() << "About to call QMainWindow::show()";
    QMainWindow::show();
    OnStartUpDialog dialog(this);

    connect(&dialog, &QDialog::rejected, qApp, QCoreApplication::quit);
    connect(&dialog, &OnStartUpDialog::newTournamentClicked, this, &MainWindow::newTournamentDialog);
    connect(&dialog, &OnStartUpDialog::openTournamentClicked, this, &MainWindow::loadExistingTournament);
    connect(this, &MainWindow::closeOnStartUp, &dialog, &QDialog::accept);

    qDebug() << "About to call OnStartUpDialog::exec()";
    dialog.show();
    qDebug() << "end of override show()";
}

void MainWindow::createMenus()
{
    // ----------------------------------------
    // File
    // ----------------------------------------
    QMenu *fileMenu = menuBar()->addMenu("File");

    auto *newTournamentAct = new QAction(tr("New Tournament"), this);
    auto *openTournamentAct = new QAction(tr("Open Tournament"), this);
    auto *saveAct = new QAction(tr("&Save"), this);
    auto *saveAsAct = new QAction(tr("Save As..."), this);
    auto *closeProgramAct = new QAction(tr("&Quit"), this);

    saveAsAct->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));

    // Add Actions
    fileMenu->addAction(newTournamentAct);
    fileMenu->addAction(openTournamentAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeProgramAct);

    // Connections
    connect(newTournamentAct, &QAction::triggered, this, &MainWindow::newTournamentDialog);
    connect(openTournamentAct, &QAction::triggered, this, &MainWindow::loadExistingTournament);
    connect(closeProgramAct, &QAction::triggered, qApp, QApplication::quit);

    // ----------------------------------------
    // Setup
    // ----------------------------------------
    QMenu *setupMenu = menuBar()->addMenu("Setup");

    auto playerHeaderAct = new QAction(tr("Player Header Preferences"));

    // Add Actions
    setupMenu->addAction(playerHeaderAct);

    // Connections
    connect(playerHeaderAct, &QAction::triggered, this, &MainWindow::openSetupDialog);

    // ----------------------------------------
    // Database
    // ----------------------------------------
    QMenu *databaseMenu = menuBar()->addMenu("Database");



    // ----------------------------------------
    // Players
    // ----------------------------------------
    QMenu *playersMenu = menuBar()->addMenu("Players");

    auto add1Act = new QAction(tr("Add"));
    auto addNAct = new QAction(tr("Add A Group"));
    auto remove1Act = new QAction(tr("Remove"));
    auto withdraw1Act = new QAction(tr("Withdraw"));
    auto listAct = new QAction(tr("List"));

    // Add Actions
    playersMenu->addAction(add1Act);
    playersMenu->addAction(addNAct);
    playersMenu->addSeparator();
    playersMenu->addAction(withdraw1Act);
    playersMenu->addAction(remove1Act);
    playersMenu->addAction(listAct);

    // Connections
    connect(add1Act, &QAction::triggered, this, &MainWindow::add1Player);


    // ----------------------------------------
    // Sections
    // ----------------------------------------
    QMenu *sectionsMenu = menuBar()->addMenu("Sections");

    auto add1SectionAct = new QAction(tr("Add"));
    auto mergeSectionAct = new QAction(tr("Merge"));
    auto removeSectionAct = new QAction(tr("Remove"));
    auto editSectionAct = new QAction(tr("Edit"));

    sectionsMenu->addAction(add1SectionAct);
    sectionsMenu->addSeparator();
    sectionsMenu->addAction(editSectionAct);
    sectionsMenu->addAction(mergeSectionAct);
    sectionsMenu->addAction(removeSectionAct);

    connect(add1SectionAct, &QAction::triggered, this, &MainWindow::newSection);
    connect(editSectionAct, &QAction::triggered, this, &MainWindow::viewSection);

    // ----------------------------------------
    // Teams
    // ----------------------------------------
    QMenu *teamsMenu = menuBar()->addMenu("Teams");

    auto addTeamsAct = new QAction(tr("Add Teams"));
    auto viewTeamsAct = new QAction(tr("View All"));

    teamsMenu->addAction(addTeamsAct);
    teamsMenu->addAction(viewTeamsAct);


    // ----------------------------------------
    // Reports
    // ----------------------------------------
    QMenu *reportsMenu = menuBar()->addMenu("Reports");


    // ----------------------------------------
    // Help
    // ----------------------------------------
    QMenu *helpMenu = menuBar()->addMenu("Help");

    auto documentationAct = new QAction(tr("Documentation"));
    auto aboutAct = new QAction(tr("About"));

    helpMenu->addAction(documentationAct);
    helpMenu->addAction(aboutAct);

}


void MainWindow::additionalUiSetup()
{

    connect(ui->add1PlayerButton, &QPushButton::clicked, this, &MainWindow::add1Player);

}



void MainWindow::add1Player()
{

    AddPlayerDialog dialog(this);

    if (!tDialog)
    {
        qDebug() << "Tournament Not Initialized";
        return;
    }

    dialog.init(tDialog->getSectionNames());
    dialog.exec();

    QList<PlayerInfo> players = dialog.getPlayers();

    // Inserts a player if they exist
    foreach (auto player, players) {
        db->insertPlayer(player);
    }

    // Updates Table Views Accordingly
    updateTableViews();

}

void MainWindow::updateTableViews()
{

    QTabWidget *tabWidget = ui->sectionTabWidget;
    // tabWidget->
}


void MainWindow::viewSection()
{
    QTabWidget *tabWidget = ui->sectionTabWidget;

    auto sectionNames = tDialog->getSectionNames();

    QString tabLabel = tabWidget->tabText(tabWidget->currentIndex());

    if(sectionNames.contains(tabLabel))
    {
        auto si0 = tDialog->getSectionsInfo().value(tabLabel);

        SectionDialog dialog(this);
        dialog.init(si0);

        if(dialog.exec() == QDialog::Accepted)
        {
            tDialog->replaceSectionInfo(si0, dialog.info);
            tabWidget->setTabText(tabWidget->currentIndex(), dialog.info.sectionName);
        }
    }
    else
    {
        QMessageBox mbox;

        mbox.setText(tr("ALL is not a section."));
        mbox.setWindowTitle(tr("Warning"));

        QSpacerItem* horizontalSpacer = new QSpacerItem(300, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);
        QGridLayout* layout = (QGridLayout*)mbox.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());


        mbox.exec();
    }



}

void MainWindow::newSection()
{
    QTabWidget *tabWidget = ui->sectionTabWidget;

    //Open New Section Dialog
    SectionDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        tDialog->addSectionInfo(dialog.info);

        //Populate section name, setup preferences, etc
        auto tableWidget = new QTableWidget(this);
        tableWidget->setRowCount(10);
        tabWidget->addTab(tableWidget, dialog.info.sectionName);
        db->insertSection(dialog.info);

    }

}


void MainWindow::openSetupDialog()
{
    sDialog = new SetupDialog(this);
    sDialog->show();



    //TODO::IMPORTANT
}

void MainWindow::newTournamentDialog()
{
    auto dialog = new TournamentDialog(this);
    dialog->setModal(true);

    if (dialog->exec() == QDialog::Accepted){
        ui->tournamentName->setText(dialog->getTournamentName());

        if(tDialog)
        {
            for (int i = ui->sectionTabWidget->count()-1; i > 0; i--) {
                ui->sectionTabWidget->removeTab(i);
            }

            delete db;
            db = new Database();
        }

        db->newDatabase(dialog->getFilePath());

        db->insertTournament(dialog->getTournamentInfo());

        foreach (auto section, dialog->getSectionsInfo()) {
            ui->sectionTabWidget->addTab(new QWidget(), section.sectionName);
            db->insertSection(section);
        }


        tDialog = dialog;
        emit closeOnStartUp();
    }



}

void MainWindow::loadExistingTournament()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Database (*.db)"));

    QStringList filepaths;
    if (!dialog.exec())
    {
        // TODO: what to do on cancel
        return;
    }
    filepaths = dialog.selectedFiles();

    // Retrieve info from database
    db->openDatabase(filepaths[0]);
    auto ti = db->setupTournament();

    // Initilize tournament with info
    tDialog = new TournamentDialog(this);
    tDialog->init(ti);

    // UI. Add Tabs
    foreach (auto si, ti->sections) {
        ui->sectionTabWidget->addTab(new QWidget(), si.sectionName);
    }

    // UI. Update Tables
    updateTableViews();

    qDebug() << "emit closeStartUp()";
    emit closeOnStartUp();

}

