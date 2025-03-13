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

public slots:
    // void reject();

signals:
    void newTournamentClicked();
    void openTournamentClicked();
    void closeMainWindow();

private:
    Ui::OnStartUpDialog *ui;

};

#endif // ONSTARTUPDIALOG_H
