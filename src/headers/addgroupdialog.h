#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

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

    void init(QList<QString> headers);

signals:
    void specialQuery(QStringList queries);

private slots:
    void onToolButtonClicked();
    void shouldDisableHeaderStyle();
    void queryBuilding();


private:
    Ui::AddGroupDialog *ui;

    void additionalUiSetup();

};

#endif // ADDGROUPDIALOG_H
