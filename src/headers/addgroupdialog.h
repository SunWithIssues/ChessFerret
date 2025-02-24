#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include "addplayerdialog.h"

#include <QDialog>

namespace Ui {
class AddGroupDialog;
}

class AddGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGroupDialog(QWidget *parent = nullptr);
    ~AddGroupDialog();

signals:
    void specialQuery(QList<QString> queries);

private slots:
    void onToolButtonClicked();
    void queryBuilding();
    void verifyCombos();

private:
    Ui::AddGroupDialog *ui;

    QHash<QString, char> seps;
    QList<QString> list;

    void additionalUiSetup();



};

#endif // ADDGROUPDIALOG_H
