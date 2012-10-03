kicad-module-scanner
===================

Date: Wed,3 Oct 2012

A Qt Project allowing you to find, view and copy Kicad footprints (aka modules).

This is currently working under linux only. It is not in a fit state for general release
and the documentation is non-existent but if you're comfortable with Eclipse/QT please
 feel free to tinker. 

This repository contains two Eclipse CDT / QT projects:

1. FootprintWidget - this is a library (libFootprintWidget.so) containing a custom widget that displays kicad footprints.
2. kicad-module-scanner - this is the main project (kicad-module-scanner) that requires the FootprintWidget above.

Sketchy notes on compilation are given in kicad-module-scanner/README.html and FootprintWidget/COMPILING.txt 


