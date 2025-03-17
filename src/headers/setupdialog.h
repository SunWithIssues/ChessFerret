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
    int heightSize;

signals:
    void valuesChanged();

private slots:
    void displayWidget();
    void onClose();
    void onAccept();

private:
    Ui::SetupDialog *ui;


    QString langDirectory();


};

#endif // SETUPDIALOG_H
