#include "headers/addgroupdialog.h"
#include "ui_addgroupdialog.h"

#include <QFileDialog>
#include <QStringBuilder>

AddGroupDialog::AddGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
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
    QStringList seps = {",", ";", "/", "\\t"};
    ui->fieldSepComboBox->addItems(seps);
    ui->fieldSepComboBox->setEditable(true);

    // Automate Button
    ui->autoButton->setDisabled(true);

    connect(ui->autoButton, &QPushButton::clicked, this, &AddGroupDialog::queryBuilding);

}

void AddGroupDialog::queryBuilding()
{
    QStringList q;
    QString sep = ui->fieldSepComboBox->currentText();
    QString filepath = ui->filePathEdit->text();


    q.append(".mode csv");

    // TODO::IMPORTANT:: check if this works for all cases
    // Put string double quotes around for safety
    q.append(".separator \"" % sep % "\"");


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

        QStringList row1;
        QByteArray line = file.readLine();
        row1.append(line.split(QChar(sep)));

        QString s;
        s.append("CREATE TABLE imported (");
        for(int i=1; i < row1.count()+1; ++i){
            s.append("column" % QString(i) % " TEXT, ");
        }
        s.removeLast();
        s.append(")");

        q.append(s);

        q.append(".import " % filepath % " imported");
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
