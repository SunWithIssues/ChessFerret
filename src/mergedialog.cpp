#include "headers/mergedialog.h"
#include "ui_mergedialog.h"

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

    ui->label->setText(tr("Multiple selection is possible. "));
}

MergeDialog::~MergeDialog()
{
    delete ui;
}

void MergeDialog::init(QStringList section_names){
    ui->fromListWidget->addItems(section_names);
    ui->toListWidget->addItems(section_names);
}

// TODO: none selected
QListWidgetItem* MergeDialog::toItems()
{
    return ui->toListWidget->currentItem();
}

// TODO: none selected
QList<QListWidgetItem*> MergeDialog::fromItems()
{

    return ui->fromListWidget->selectedItems();
}

