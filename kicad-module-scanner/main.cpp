#include "kicad_module_scanner.h"

#include <QtGui>
#include <QApplication>
#include "main.h"
QSettings *settings; //must be instantiated external to main window, otherwise closeEvent save actions will not work
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,"TinTrayProductions","KicadFootprintViewer");
    kicad_module_scanner w;
    w.show();
    return a.exec();
}
