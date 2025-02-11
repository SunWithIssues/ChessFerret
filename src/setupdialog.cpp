#include "headers/setupdialog.h"
#include "ui_setupdialog.h"

#include <QDebug>
#include <QDir>

SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    // TODO: this is build location
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

// QString SetupDialog::langPath = QApplication::applicationDirPath().append("/.qm");

QList<QString> SetupDialog::populateLangChoices()
{
    // TODO::IMPORTANT:: I want langPath to be static, currently pointed to build
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



