#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/tournamentdialog.h"
#include "headers/setupdialog.h"
#include "headers/sectiondialog.h"
#include "headers/addplayerdialog.h"
#include "headers/addgroupdialog.h"

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
    connect(addNAct, &QAction::triggered, this, &MainWindow::addNPlayers);

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


void MainWindow::addNPlayers()
{
    AddGroupDialog dialog(this);
    if (!tDialog)
    {
        qDebug() << "Tournament Not Initialized";
        return;
    }

    // TODO::IMPORTANT:: have the comboboxes be populated with possible headers
    dialog.init(QList<QString>());
    dialog.show();


    // updateTableViews();

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

    QList<AddPlayerDialog::playerInfo> players = dialog.getPlayers();

    // Inserts a player if they exist
    foreach (auto player, players) {
        db->insert(player);
    }

    // Updates Table Views Accordingly
    updateTableViews();

}

void MainWindow::updateTableViews()
{

    auto *tableWidget = ui->currentAllView; //
    // QTableView *newTableWidget = new QTableView;

    // qDebug() << "row count (b4)" << tableWidget->model()->rowCount();
    // qDebug() << "row count (new)" << newTableWidget->model()->rowCount();

    delete tableWidget->model();

    qDebug() << "row count (deletion)" << tableWidget->model()->rowCount();

    auto model_ptr = db->selectAll();
    if(!model_ptr){
        qDebug() << "did not work";
        return;
    }

    qDebug() << "it worked?";
    // qDebug() << "row count (old)" << tableWidget->model()->rowCount();
    // qDebug() << "row count (new)" << newTableWidget->model()->rowCount();
    // tableWidget->show();
    ui->currentAllView->setModel(model_ptr);

    qDebug() << "row count (after)" << ui->currentAllView->model()->rowCount();


}




void MainWindow::newSection(){
    QTabWidget *tabWidget = ui->sectionTabWidget;

    //TODO::IMPORTANT:: this whole code logic is repeated in tournament dialog
    //  should be a public function SectionDialog

    //Open New Section Dialog
    SectionDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        //
        tDialog->addSectionInfo(dialog.info);

        //Populate section name, setup preferences, etc
        auto tableWidget = new QTableWidget(this);
        tableWidget->setRowCount(10);
        tabWidget->addTab(tableWidget, dialog.info.sectionName);

    }

}


void MainWindow::openSetupDialog(){
    sDialog = new SetupDialog(this);
    sDialog->show();



    //TODO::IMPORTANT
}

void MainWindow::newTournamentDialog()
{

    //TODO::IMPORTANT:: figure out what to do if they open a new tournament
    //  db must close b4hand, old tDialog might be needed if they cancel, etc

    tDialog = new TournamentDialog(this);
    tDialog->setModal(true);

    if (tDialog->exec() == QDialog::Accepted){
        ui->tournamentName->setText(tDialog->getTournamentName());

        foreach (auto section, tDialog->getSectionsInfo()) {
            ui->sectionTabWidget->addTab(new QWidget(), section.sectionName);
        }

        db->newDatabase(tDialog->getFilePath());

    }



}

void MainWindow::loadExistingTournament()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Database (*.db)"));

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    //TODO: read file info

    //TODO: set file info in dialog
    tDialog = new TournamentDialog(this);

    //TODO: setup database
    db->openDatabase(tDialog->getFilePath());

    //TODO: read header preferences for view displaying

    //TODO: update window w/ additional ui setup

}

