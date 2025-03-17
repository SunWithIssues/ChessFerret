#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
// #include <QFont>

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
    QFont headerFonts;
    QFont cellFonts;

private slots:
    void displayTitle();

private:
    Ui::SetupDialog *ui;


    QString langDirectory();


};

#endif // SETUPDIALOG_H
