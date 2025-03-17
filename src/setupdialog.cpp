#include "headers/setupdialog.h"
#include "ui_setupdialog.h"

#include <QDebug>
#include <QDir>

SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupDialog)
{
    ui->setupUi(this);

    // Set Title
    this->setWindowTitle(tr("Preferences"));

    // // Display First Row
    // ui->titleLabel->setText(ui->listWidget->item(0)->text());
    // ui->stackedWidget->setCurrentIndex(0);

    // Table Fonts
    QFont f("Ubuntu", 20, QFont::Bold);

    ui->headerFontComboBox->setCurrentFont(f);
    ui->headerFontSpinBox->setValue(f.pixelSize());

    headerFonts = f;

    QFont f2("Ubuntu", 10);

    ui->cellsFontComboBox->setCurrentFont(f);
    ui->cellsFontSpinBox->setValue(f2.pixelSize());

    cellFonts = f2;

    // Connections
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &SetupDialog::displayTitle);
    connect(ui->listWidget, &QListWidget::currentRowChanged, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
}

SetupDialog::~SetupDialog()
{
    delete ui;
}


void SetupDialog::displayTitle()
{

    auto idx = ui->listWidget->currentRow();
    ui->titleLabel->setText(ui->listWidget->item(idx)->text());
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



