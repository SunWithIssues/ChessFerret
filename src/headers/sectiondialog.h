#ifndef SECTIONDIALOG_H
#define SECTIONDIALOG_H

#include <QDialog>

// Pairing
#define SWISS 0
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
    struct SectionInfo
    {
        int sectionId;

        QString sectionName;
        int numRounds;

        // Pairing Attributes
        // TODO: these are comboBoxes
        QString pairingRule;
        QString scoringStyle;

        // Database Validators
        int ratingRangeMin;
        int ratingRangeMax;

        // Printing Specific Attributes
        QString sectionNameForPrinting;
        QString timeControl;
    };

    // TODO: plan is to update section table of the database
    SectionInfo info;


    explicit SectionDialog(QWidget *parent = nullptr);
    ~SectionDialog();

    void init(SectionDialog::SectionInfo si);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::SectionDialog *ui;

    void additionalUiSetup();



};

#endif // SECTIONDIALOG_H
