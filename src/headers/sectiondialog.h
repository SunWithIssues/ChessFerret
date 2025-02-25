#ifndef SECTIONDIALOG_H
#define SECTIONDIALOG_H

#include "../helpers/headers/info.h"

#include <QDialog>


// Pairing
#define SWISS 0
#define DOUBLE_SWISS 7
#define ROUND_ROBIN 1
#define LADDER 2

// Pairing - Teams
#define SWISS_PLUS_TWO 5 // see section 28N1, USCF 7th Ed


// Scoring Style
#define REGULAR 6

// Scoring Style - Teams (Focused)
#define ROLLINS_MILITARY 3 // see section 31A1, USCF 7th Ed
#define TOP_SCORE 4 // see section 28N, USCF 7th Ed

namespace Ui {
class SectionDialog;
}

class SectionDialog : public QDialog
{
    Q_OBJECT

public:


    // TODO: plan is to update section table of the database
    SectionInfo info;


    explicit SectionDialog(QWidget *parent = nullptr);
    ~SectionDialog();

    void init(SectionInfo si);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::SectionDialog *ui;
    QHash<int, QString> pairingStyles;
    QHash<int, QString> scoringstyles;

    void additionalUiSetup();



};

#endif // SECTIONDIALOG_H
