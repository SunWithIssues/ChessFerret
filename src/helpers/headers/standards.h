#ifndef STANDARDS_H
#define STANDARDS_H


#include <QMessageBox>

class Standards
{
public:
    Standards();

    static QMessageBox* warning(QString msg = "", QString title = "Warning");
    static QMessageBox* warningYesNo(QString msg= "", QString title= "Warning");
};

#endif // STANDARDS_H
