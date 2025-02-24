#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

#include <algorithm>
#include <QFileDialog>
#include <QStringBuilder>
#include <QTextStream>

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

void AddGroupDialog::init(QList<QString> headers)
{

}

void AddGroupDialog::additionalUiSetup()
{
    // File Path Actions
    ui->filePathEdit->setReadOnly(true);
    connect(ui->toolButton, &QToolButton::clicked, this, &AddGroupDialog::onToolButtonClicked);

    // Header Related Actions
    ui->headersCheckBox->setChecked(false);
    ui->vRadioButton->setDisabled(true);
    ui->hRadioButton->setDisabled(true);

    connect(ui->headersCheckBox, &QCheckBox::checkStateChanged, this, &AddGroupDialog::shouldDisableHeaderStyle);

    // Field Separator
    ui->fieldSepComboBox->addItems(list);

    // Automate Button
    ui->autoButton->setDisabled(true);

    connect(ui->autoButton, &QPushButton::clicked, this, &AddGroupDialog::queryBuilding);

    // ButtonBox
    ui->buttonBox->setDisabled(true);

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

    headers.prepend("");

    ui->fideIdComboBox->addItems(headers);
    ui->birthDateComboBox->addItems(headers);
    ui->fideRtgComboBox->addItems(headers);
    ui->nameComboBox->addItems(headers);
    ui->natIdComboBox->addItems(headers);
    ui->natRtgComboBox->addItems(headers);
    ui->sectionComboBox->addItems(headers);

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

void AddGroupDialog::shouldDisableHeaderStyle()
{
    if(ui->headersCheckBox->checkState() == Qt::Checked){
        ui->hRadioButton->setDisabled(false);
        ui->vRadioButton->setDisabled(false);
    }
    else
    {
        ui->hRadioButton->setDisabled(true);
        ui->vRadioButton->setDisabled(true);
    }
}
