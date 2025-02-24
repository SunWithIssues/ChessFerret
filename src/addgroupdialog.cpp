#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

#include <algorithm>
#include <QFileDialog>
#include <QStringBuilder>
#include <QTextStream>
#include <QMessageBox>

AddGroupDialog::AddGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);


    //TODO: there must be a better method for this
    seps.insert(",", ',');
    seps.insert(";", ';');
    seps.insert("/", '/');
    seps.insert("\\t", '\t');


    list = seps.keys();
    std::sort(list.begin(), list.end()); //TODO: this might be reimplemented or deleted

    additionalUiSetup();
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::additionalUiSetup()
{
    // File Path Actions
    ui->filePathEdit->setReadOnly(true);
    connect(ui->toolButton, &QToolButton::clicked, this, &AddGroupDialog::onToolButtonClicked);

    // Header Related Actions
    ui->headersCheckBox->setChecked(false);

    // Field Separator
    ui->fieldSepComboBox->addItems(list);

    // Automate Button
    ui->autoButton->setDisabled(true);

    connect(ui->autoButton, &QPushButton::clicked, this, &AddGroupDialog::queryBuilding);

    // ButtonBox
    ui->buttonBox->setDisabled(true);

    // Verify Button
    ui->verifyButton->setDisabled(true);
    connect(ui->verifyButton, &QPushButton::clicked, this, &AddGroupDialog::verifyCombos);

}

void AddGroupDialog::verifyCombos()
{

    QList<QComboBox *> allCBoxes = ui->groupBox->findChildren<QComboBox *>();
    QSet<QString> chosen;
    QString txt;
    foreach (auto cb, allCBoxes) {
        txt = cb->currentText();
        qDebug() << txt;
        if (txt != ""){
            qDebug() << "not null";
            if(chosen.contains(txt))
            {
                qDebug() << "mBox called";
                // TODO: duplicate found
                QMessageBox mBox(this);
                mBox.setText("DUPLICATE FOUND: " % txt % "used more than once");
                // mBox.setDetailedText();
                mBox.exec();
                break;
            }
            chosen.insert(txt)
        }
    }



}



void AddGroupDialog::queryBuilding()
{
    QList<QString> q = QList<QString>();
    QString sepKey = ui->fieldSepComboBox->currentText();
    QString filepath = ui->filePathEdit->text();


    QStringList headers;

    // ----------------------------------
    // read csv
    // ----------------------------------
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "could not read file << " << filepath;
    }

    // ----------------------------------
    // create header if needed (create table ...)
    // ----------------------------------


    QTextStream stream(&file);

    QList<QString> row;
    QString line = stream.readLine();

    QString s;
    s.append("CREATE TABLE imported (");

    row.append(line.split(seps.value(sepKey)));

    if(ui->headersCheckBox->checkState() == Qt::Checked)
    {
        for(int i=0; i < row.count(); ++i){
            s.append("\n \"" % row.value(i) % "\" TEXT,"); // TODO: might need to use tostring
            headers.append(row.value(i));
        }
        s.removeLast();
        s.append(")");

        q.append(s);

    }
    else
    {
        QString s2;
        s2.append("INSERT INTO imported VALUES ( ");
        for(int i=1; i < row.count()+1; ++i){
            s.append("\n column" % QString::number(i) % " TEXT,");
            s2.append("\n \"" % row.value(i-1) % "\",");
            headers.append("column" % QString::number(i));
        }
        s.removeLast();
        s.append(")");

        s2.removeLast();
        s2.append(")");

        q.append(s);
        q.append(s2);
    }
    // ----------------------------------
    // loop (insert into ...)
    // ----------------------------------

    while (stream.atEnd() == false)
    {
        line = stream.readLine();
        row.clear();
        row.append(line.split(seps.value(sepKey)));

        s.clear();
        s.append("INSERT INTO imported VALUES ( ");
        for(int i=0; i < row.count(); ++i){
            s.append("\n \"" % row.value(i) % "\",");
        }
        s.removeLast();
        s.append(")");

        q.append(s);
    }


    // ----------------------------------
    // update ui => populate headers
    // ----------------------------------


    ui->buttonBox->setDisabled(false);
    ui->verifyButton->setDisabled(false);

    headers.prepend("");

    QList<QComboBox *> allCBoxes = ui->groupBox->findChildren<QComboBox *>();
    foreach (auto cb, allCBoxes) {
        cb->addItems(headers);
    }

    emit specialQuery(q);


}


void AddGroupDialog::onToolButtonClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Choose File"),
                                                    ui->filePathEdit->text(),
                                                    tr("Spreadsheet (*.csv *.tsv)"));


    if(filepath != ""){
        ui->filePathEdit->setText(filepath);

        //
        ui->autoButton->setDisabled(false);

        if(filepath.last(4) == ".tsv")
            ui->fieldSepComboBox->setCurrentIndex(3);
    }

}

