#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include "../helpers/headers/addplayer.h"

#include <QDialog>

namespace Ui {
class AddGroupDialog;
}

class AddGroupDialog : public QDialog, public AddPlayer
{
    Q_OBJECT

public:
    explicit AddGroupDialog(QWidget *parent = nullptr, QList<QString> sectionNames = QList<QString>());
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
