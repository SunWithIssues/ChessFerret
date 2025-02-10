#ifndef ONSTARTUPDIALOG_H
#define ONSTARTUPDIALOG_H

#include <QDialog>

namespace Ui {
class OnStartUpDialog;
}

class OnStartUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnStartUpDialog(QWidget *parent = nullptr);
    ~OnStartUpDialog();

signals:
    void newTournamentClicked();
    void openTournamentClicked();

private:
    Ui::OnStartUpDialog *ui;
};

#endif // ONSTARTUPDIALOG_H
