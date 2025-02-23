#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

#include <algorithm>
#include <QFileDialog>
#include <QStringBuilder>

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
    std::sort(list.begin(), list.end());

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
    ui->fieldSepComboBox->setEditable(true);

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


    q.append(".mode csv");

    // TODO::IMPORTANT:: check if this works for all cases
    // Put string double quotes around for safety
    q.append(".separator \"" % sepKey % "\"");


    // there is a header
    if(ui->headersCheckBox->checkState() == Qt::Checked)
    {
        q.append(".import " % filepath % " imported");

        // TODO::IMPORTANT:: the csv needs to be transposed
        if(ui->hRadioButton->isChecked()){

        }

    }
    else{ // there is NO HEADER
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly)){
            qDebug() << "could not read file << " << filepath;
        }
        QList<QByteArray> row1;
        QByteArray line = file.readLine();

        row1.append(line.split(seps.value(sepKey)));

        QString s;
        s.append("CREATE TABLE imported (");
        for(int i=1; i < row1.count()+1; ++i){
            s.append("\n column" % QString::number(i) % " TEXT,");
        }
        s.removeLast();
        s.append(")");

        q.append(s);

        q.append(".import " % filepath % " imported");
    }


    ui->buttonBox->setDisabled(false);

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
