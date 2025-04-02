#include "headers/standards.h"

#include <QSpacerItem>
#include <QGridLayout>
#include <QString>

Standards::Standards() {}

QMessageBox* Standards::warning(QString msg, QString title)
{
    QMessageBox* mbox = new QMessageBox();

    mbox->setText(msg);
    mbox->setWindowTitle(title);

    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QGridLayout* layout = (QGridLayout*)mbox->layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    return mbox;
}
