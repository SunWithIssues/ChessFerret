#include "headers/mainwindow.h"
#include "headers/onstartupdialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ChessFerret_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    OnStartUpDialog* dialog = new OnStartUpDialog();

    MainWindow w;
    w.setWindowTitle("ChessFerret");
    w.show(dialog);

    dialog->show();
    dialog->raise();
    dialog->activateWindow();



    qDebug() << "About to call a.exec()";
    return a.exec();
}
