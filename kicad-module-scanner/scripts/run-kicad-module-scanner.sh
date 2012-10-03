#!/bin/sh
#this script sets LD_LIBRARY_PATH so the loader can find libFootprintWidget.so
PROG="/media/sf_quad-root/media/OneTouch4-Main/git/kicad-module-scanner/kicad-module-scanner/debug/kicad_module_scanner"
#DIR="/media/sf_quad-root/media/OneTouch4-Main/git/kicad-module-scanner/kicad-module-scanner"
echo "$PROG running in $DIR"
cd $DIR
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/root/Projects/kicad-module-scanner/FootprintWidget/debug
$PROG
