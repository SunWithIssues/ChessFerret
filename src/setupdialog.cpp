#include "headers/setupdialog.h"
#include "ui_setupdialog.h"

#include <QDebug>
#include <QDir>

#include <QPushButton>


SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupDialog)
{
    ui->setupUi(this);

    // Set Title
    this->setWindowTitle(tr("Preferences"));

    // Search Filter LineEdit
    ui->searchLineEdit->setPlaceholderText(tr("Filter"));


    // Display First Row
    ui->titleLabel->setText(ui->listWidget->item(0)->text());
    ui->stackedWidget->setCurrentIndex(0);

    // Table Fonts
    QFont f("Ubuntu", 20, QFont::Bold);

    ui->headerFontComboBox->setCurrentFont(f);
    ui->headerFontSpinBox->setValue(f.pointSize());

    headerFonts = f;

    QFont f2("Ubuntu", 13);

    ui->cellsFontComboBox->setCurrentFont(f);
    ui->cellsFontSpinBox->setValue(f2.pointSize());

    cellFonts = f2;

    // Cell Height Size
    heightSize = 20;
    ui->heightSpinBox->setValue(heightSize);


    // Connections
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &SetupDialog::displayWidget);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &SetupDialog::valuesChanged);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &SetupDialog::onAccept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &SetupDialog::onClose);

    connect(ui->cellsFontComboBox, &QFontComboBox::currentFontChanged, this, [=](){ this->cellFonts.setFamily(ui->cellsFontComboBox->currentText()); });
    connect(ui->cellsFontSpinBox, &QSpinBox::valueChanged, this, [=](){ this->cellFonts.setPointSize(ui->cellsFontSpinBox->value()); });
    connect(ui->headerFontComboBox, &QFontComboBox::currentFontChanged, this, [=](){ this->headerFonts.setFamily(ui->headerFontComboBox->currentText()); });
    connect(ui->headerFontSpinBox, &QSpinBox::valueChanged, this, [=](){ this->headerFonts.setPointSize(ui->headerFontSpinBox->value()); });

    connect(ui->heightSpinBox, &QSpinBox::valueChanged, this, [=](){ this->heightSize = ui->heightSpinBox->value(); });

}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::onClose()
{
    this->reject();
}


void SetupDialog::onAccept()
{
    emit valuesChanged();
    this->accept();
}


void SetupDialog::displayWidget()
{


    auto idx = ui->listWidget->currentRow();
    ui->titleLabel->setText(ui->listWidget->item(idx)->text());
    ui->stackedWidget->setCurrentIndex(idx);
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



