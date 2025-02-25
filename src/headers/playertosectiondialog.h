#ifndef PLAYERTOSECTIONDIALOG_H
#define PLAYERTOSECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerToSectionDialog;
}

class PlayerToSectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerToSectionDialog(QWidget *parent = nullptr);
    ~PlayerToSectionDialog();

private:
    Ui::PlayerToSectionDialog *ui;
};

#endif // PLAYERTOSECTIONDIALOG_H
