#ifndef MERGEDIALOG_H
#define MERGEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class MergeDialog;
}

class MergeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MergeDialog(QWidget *parent = nullptr);
    ~MergeDialog();

    void init(QStringList section_names);

    QList<QListWidgetItem*> fromItems();
    QListWidgetItem* toItems();

private:
    Ui::MergeDialog *ui;
};

#endif // MERGEDIALOG_H
