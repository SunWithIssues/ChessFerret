#include "headers/mergedialog.h"
#include "ui_mergedialog.h"

#include "helpers/headers/standards.h"


MergeDialog::MergeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MergeDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Merge Sections"));

    ui->fromListWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    auto f = ui->label->font();
    f.setItalic(true);
    ui->label->setFont(f);

    ui->label->setText(tr("Unpaired section is speciality section filled with all players who are not in playing section."));
}

MergeDialog::~MergeDialog()
{
    delete ui;
}

void MergeDialog::init(QStringList section_names){
    ui->fromListWidget->addItem("UNPAIRED SECTION");

    QListWidgetItem* lwi = ui->fromListWidget->item(0);
    auto f = lwi->font();
    f.setItalic(true);
    lwi->setFont(f);

    ui->fromListWidget->addItems(section_names);
    ui->toListWidget->addItems(section_names);
}

void MergeDialog::accept()
{
    if(ui->toListWidget->selectedItems().length() < 1 || ui->fromListWidget->selectedItems().length() < 1)
    {
        auto mbox = Standards::warning(tr("Must select items from both sides."));
        mbox->exec();
        delete mbox;
        return;
    }
    QDialog::accept();
}


QListWidgetItem* MergeDialog::toItem()
{
    return ui->toListWidget->currentItem();
}

QList<QListWidgetItem*> MergeDialog::fromItems()
{
    return ui->fromListWidget->selectedItems();
}

