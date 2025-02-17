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

private slots:
    void onToolButtonClicked();
    void shouldDisableHeaderStyle();


private:
    Ui::AddGroupDialog *ui;

    void additionalUiSetup();

};

#endif // ADDGROUPDIALOG_H
