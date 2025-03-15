#include "headers/setupdialog.h"
#include "ui_setupdialog.h"

#include <QDebug>
#include <QDir>

SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Preferences"));

    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &SetupDialog::displayWidget);

}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::displayWidget()
{
    auto twi = ui->treeWidget->currentItem();
    QString txt = twi->text(0);
    if(twi->parent()){
        txt.prepend(twi->parent()->text(0) + " - ");
    }
    ui->titleLabel->setText(txt);

}

QList<QString> SetupDialog::populateLangChoices()
{
    QString langPath = QApplication::applicationDirPath();
    langPath.append("/.qm");


    QDir dir(langPath);
    QStringList fileNames = dir.entryList(QStringList("ChessFerret_*.qm"));

    QList<QString> translations;
    QString t, lang;
    for (int i = 0; i < fileNames.size(); ++i) {
        t = fileNames[i];
        t.truncate(t.lastIndexOf('.'));
        t.remove(0, t.indexOf('_')+1);
        lang = QLocale::languageToString(QLocale(t).language());
        translations.append(lang);
    }

    return translations;
}



