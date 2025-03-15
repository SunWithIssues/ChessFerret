#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();

    static QList<QString> populateLangChoices();

private slots:
    void displayWidget();

private:
    Ui::SetupDialog *ui;

    QString langDirectory();


};

#endif // SETUPDIALOG_H
