#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "headers/tournamentdialog.h"
#include "headers/setupdialog.h"
#include "headers/sectiondialog.h"
#include "headers/addplayerdialog.h"
#include "headers/onstartupdialog.h"
#include "headers/aboutdialog.h"


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

    tDialog = nullptr;
    sDialog = new SetupDialog(this);
    db = new Database();

    createMenus();
    additionalUiSetup();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
    delete tDialog;
    delete sDialog;
}


void MainWindow::show(OnStartUpDialog* dialog)
{
    QMainWindow::show();

    connect(dialog, &QDialog::rejected, qApp, QCoreApplication::quit);
    connect(dialog, &OnStartUpDialog::newTournamentClicked, this, &MainWindow::newTournamentDialog);
    connect(dialog, &OnStartUpDialog::openTournamentClicked, this, &MainWindow::loadExistingTournament);
    connect(this, &MainWindow::closeOnStartUp, dialog, &QDialog::accept);

    dialog->setModal(true);
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
    QMenu *setupMenu = menuBar()->addMenu(tr("Setup"));

    auto *prefAct = new QAction(tr("Preferences"));

    // Add Actions
    setupMenu->addAction(prefAct);

    // Connections
    connect(prefAct, &QAction::triggered, sDialog, &SetupDialog::show);


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
    connect(withdraw1Act, &QAction::triggered, this, &MainWindow::withdrawPlayer);
    connect(remove1Act, &QAction::triggered, this, &MainWindow::removePlayer);

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

    connect(aboutAct, &QAction::triggered, this, &MainWindow::openAboutDialog);

}


void MainWindow::additionalUiSetup()
{

    ui->sectionTabWidget->setMovable(true);
    connect(ui->add1PlayerButton, &QPushButton::clicked, this, &MainWindow::add1Player);
    connect(ui->withdraw1PlayerButton, &QPushButton::clicked, this, &MainWindow::withdrawPlayer);
    connect(sDialog, &SetupDialog::valuesChanged, this, &MainWindow::fullRedraw);
}

void MainWindow::fullRedraw()
{
    QTableView *tv;
    int len = ui->sectionTabWidget->count();
    for(int i=0; i < len; i++)
    {
        tv = (QTableView*)ui->sectionTabWidget->widget(i)->children().value(1);
        formatTableView(tv);
    }


}

void MainWindow::populateHeaderPreferences()
{

    // TODO::IMPORTANT:: this is a quick dirty method for associating
    //   database attributes with columns headers. will prob change in future


    hp = new headerPreferences();

    auto cols = db->getColsPlayers();
    auto r = new QHash<QString, QString>({
        {tr("Name"), cols.at(0).name}, {tr("Ranking"), cols.at(1).name},
        {tr("Birthdate"), cols.at(2).name}, {tr("Gender"), cols.at(3).name},
        {tr("ID National"), cols.at(4).name}, {tr("Rating National"), cols.at(5).name},
        {tr("ID FIDE"), cols.at(6).name}, {tr("Rating FIDE"), cols.at(7).name},
        {tr("Section"), cols.at(8).name}, {tr("Teams"), cols.at(9).name}
    });

    hp->roster = r;


}



void MainWindow::addNPlayers()
{

    if (!tDialog)
    {
        qDebug() << "Tournament Not Initialized";
        return;
    }

    updateTableViews();

}

void MainWindow::add1Player()
{



    if (!tDialog)
    {
        qDebug() << "Tournament Not Initialized";
        return;
    }

    AddPlayerDialog dialog(this, tDialog->getSectionNames());
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


    QAbstractItemModel *model_ptr;

    QTableView *tv;
    QString tn;
    int len = ui->sectionTabWidget->count();
    for(int i=0; i < len; i++)
    {
        tv = (QTableView*)ui->sectionTabWidget->widget(i)->children().value(1);
        tn = ui->sectionTabWidget->tabText(i);

        // All TableView
        if (tv == ui->currentAllView){
            model_ptr = db->selectAll();
        }
        else // Section TableView
        {
            model_ptr = db->selectPlayersFromSection(tn);
        }

        tv->setModel(model_ptr);
        formatTableView(tv);
    }


}


void MainWindow::removePlayer(){
    auto tab = ui->sectionTabWidget->currentWidget();
    auto tv = (QTableView*) tab->children().value(1);
    auto qmi = tv->currentIndex();


}

void MainWindow::withdrawPlayer(){
    int idx = ui->sectionTabWidget->currentIndex();
    QTableView* tv = (QTableView*) ui->sectionTabWidget->widget(idx)->children().value(1);
    QModelIndex qmi = tv->currentIndex();

    QVariant v(-1);
    QVariant s("nb");
    qDebug() << tv->model()->setData(qmi.sibling(qmi.row(), 2), v);
    qDebug() << tv->model()->setData(qmi.sibling(qmi.row(), 4), s);
    qDebug() << tv->model()->sibling(qmi.row(), 0, qmi).data();
    qDebug() << qmi.data();
    qDebug() << qmi.sibling(qmi.row(), 2).data();

    // if(tv == ui->currentAllView)
    // {
    //     db->withdrawPlayer(qmi.row());
    // }else{
    //     db->withdrawPlayer(qmi.row(), ui->sectionTabWidget->tabText(idx));
    // }

}



void MainWindow::viewSection()
{
    QTabWidget *tabWidget = ui->sectionTabWidget;

    int idx = tabWidget->currentIndex();


    if(idx != 0)
    {
        QList<int> ids = tDialog->getSectionIds();

        int selectedId = ids.value(idx-1);
        SectionInfo si0 = tDialog->getSectionsInfo().value(selectedId);

        SectionDialog dialog(this);
        dialog.init(si0);

        if(dialog.exec() == QDialog::Accepted)
        {
            tDialog->replaceSectionInfo(selectedId, dialog.info);
            tabWidget->setTabText(idx, dialog.info.sectionName);
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
        // Update DB then add to tDialog
        db->insertSection(dialog.info);
        tDialog->addSectionInfo(db->getSectionsSeq(), dialog.info);

        // Change UI Accordingly
        auto w = emptyTabQWidget();
        tabWidget->addTab(w, dialog.info.sectionName);

    }

}

void MainWindow::openAboutDialog()
{
    AboutDialog dialog(this);

    dialog.exec();
}

void MainWindow::newTournamentDialog()
{
    auto dialog = new TournamentDialog(this);
    dialog->setModal(true);

    if (dialog->exec() == QDialog::Accepted){
        ui->tournamentName->setText(dialog->getTournamentName());

        if(tDialog)
        {
            resetUi();
        }

        db->newDatabase(dialog->getFilePath());
        db->insertTournament(dialog->getTournamentInfo());

        // Populate Header Preferences b4 tabwidget decisions
        populateHeaderPreferences();

        QString sn;
        QHash<int, SectionInfo> si = dialog->getSectionsInfo();
        foreach (auto id, dialog->getSectionIds()) {
            sn = si.value(id).sectionName;
            auto w = emptyTabQWidget();

            ui->sectionTabWidget->addTab(w, sn);
            db->insertSection(si.value(id));
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


    if(tDialog){
        resetUi();
    }

    // Retrieve info from database
    db->openDatabase(filepaths[0]);
    auto ti = db->setupTournament();

    // Initilize tournament with info
    tDialog = new TournamentDialog(this);
    tDialog->init(ti);

    // Populate Header Preferences b4 tabwidget decisions
    populateHeaderPreferences();

    // UI. Tournament Name.
    ui->tournamentName->setText(ti->tournamentName);

    // UI. Add Tabs
    QString sn;
    foreach (auto id, ti->sectionIds) {

        sn = ti->sections.value(id).sectionName;
        auto w = emptyTabQWidget();

        ui->sectionTabWidget->addTab(w, sn);
    }

    // UI. Update Tables
    updateTableViews();

    emit closeOnStartUp();

}

void MainWindow::resetUi()
{
    for (int i = ui->sectionTabWidget->count()-1; i > 0 ; --i) {
        delete ui->sectionTabWidget->widget(i);
        ui->sectionTabWidget->removeTab(i);
    }

    delete db;
    db = new Database();
}

QWidget* MainWindow::emptyTabQWidget(){
    QWidget *w = new QWidget();
    QGridLayout *l = new QGridLayout(w);
    l->addWidget(new QTableView(), 0,0);

    return w;
}

void MainWindow::formatTableView(QTableView *tv){
    tv->horizontalHeader()->setStretchLastSection(true);
    tv->verticalHeader()->hide();
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *verticalHeader = tv->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(sDialog->heightSize); // TODO: name of variable might change

    verticalHeader->setFont(sDialog->headerFonts);
    tv->setFont(sDialog->cellFonts);
}

