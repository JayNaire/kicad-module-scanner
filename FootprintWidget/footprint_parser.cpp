
/* ROB: This file was made by qlalr from footprint.g"*/
#include "footprint_parser.h"
#include <QtDebug>
#include <cstdlib>
#include "ModView.h"
class Pad;
Pad *pad;
class Field;
Field *field;
void FootprintParser::consumeRule(int ruleno)
  {
  bool Ok;
    switch (ruleno) {

case 0:
	qDebug() << "parser Finished: Goal achieved!";
	break;

case 4:
	//name = sym(1); 
	qDebug() << "parser: seen Rule BeginModule\n\t Module Name is -->: " << sym(1);
	break;
/*Don't know what field HexOrNumber is used for*/case 26: {qDebug() << "parser:Cd:" << sym(1); break; /*returns whole line after Li*/}case 27: {qDebug() << "parser:Kw:" << sym(1); break; /*returns whole line after Li*/}
				//DS - draw segment
				case 30:{
					qDebug() << "parser:ModuleDS: adding segment";
					view->addSegment(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok));
					break;
				}
				
				//DC - draw circle
				case 31:{
					qDebug() << "parser:ModuleDC: adding circle";
					view->addCircle(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok));
					break;
				}
				
				//DA - draw arc
				case 32:{
					qDebug() << "parser:ModuleDA: adding arc";
					view->addArc(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok),sym(7).toInt(&Ok));
					break;
				}
				 /*REFDES*/
				case 33:{
					qDebug() << "parser:T0(refdes):" << sym(3);
					field->setText(sym(3));
					view->addField(field);
					break;
				}
				
				case 34:{
					qDebug() << "parser:creating new refdes field";
					field = new Field(Field::refdes);
					break;
				}
				 /*VALUE returns whole line after T1*/
				case 35: {
					qDebug() << "parser:T1(value):" << sym(2);
					field->setText(sym(2));
					view->addField(field);
					break;
				}
				
				case 36:{
					qDebug() << "parser:creating new value field";
					field = new Field(Field::value);
					break;
				}
				 /*TEXT FIELD returns whole line after Txx*/
				case 37: {
					qDebug() << "parser:Txx(textfield):" << sym(2);
					field->setText(sym(2));
					view->addField(field);
					break; }
				case 38:{
					qDebug() << "parser:creating new other field";
					field = new Field(Field::other);
					break;
				}
				
				//This is a fix as At SMD and At VIRTUAL (more?) are apparently valid at module level as well as pad level
				//although it's meaning is undocumented
				
case 42:
	qDebug() << "parser:EndModule:" << sym(2);
	break;

				case 43: { //ERROR HERE sym(1) is value for Ypos not Xpos etc.
					//                                   Xpos       Ypos     Xsize     Ysize Orientation   Width      N        visibility
					qDebug() << "parser:FieldRecord:" << sym(0) << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6) << sym(7);
					field->setParams(sym(0).toInt(&Ok),sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6),sym(7));
					break;
				}
				
				case 44: {
					qDebug() << "parser:FieldRecord:Layer" << sym(1);
					field->setLayer(sym(1).toInt(&Ok));
					break;
				}
				
				case 45: {
					qDebug() << "parser:FieldRecord:TextStyle" << sym(1);
					field->setTextStyle(sym(1));
					break;
				}
				
case 57:
	qDebug() << "parser:Pad: Seen a complete pad"; //OK
	view->addPad(pad);
	break;

case 59:
	qDebug() << "parser:PadRecords:"; //OK
	break;

case 66:
	qDebug() << "parser:PadShapeRecord: " << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6) << sym(7);
	pad->setShape( sym(1), sym(2), sym(3), sym(4), sym(5), sym(6), sym(7));
	break;
case 67: {qDebug() << "parser:TimeStamp"; break;}
case 70:
	qDebug() << "parser:PadRoundDrillRecord: " << sym(1) << sym(2) << sym(3);
	pad->setRoundDrill( sym(1), sym(2), sym(3));
	break;

case 71:
	qDebug() << "parser:PadOvalDrillRecord: " << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6);
	//rarely seen; padshape is always O (capital Oh not zero)
	pad->setOvalDrill( sym(1), sym(2), sym(3), sym(4), sym(5), sym(6));
	break;

case 72:
	//At STD N 00E0FFFF
	qDebug() << "parser:PadAttributes: " << sym(1) << sym(2) << sym(3);
	pad->setAttributes( sym(1), sym(2), sym(3));
	break;

case 73:
	qDebug() << "parser:PadNetReference: " << sym(1) << sym(2);
	pad->setNetReference( sym(1), sym(2));
	break;

case 74:
	qDebug() << "parser:PadPosition: " << sym(1) << sym(2);
	pad->setPosition( sym(1), sym(2));
	break;
case 75: {qDebug() << "parser:Angle"; break;}case 76: {qDebug() << "parser:Xpoint"; break;}case 77: {qDebug() << "parser:Ypoint"; break;}case 78: {qDebug() << "parser:Xcentre"; break;}case 79: {qDebug() << "parser:Ycentre"; break;}case 80: {qDebug() << "parser:Xstart"; break;}case 81: {qDebug() << "parser:Ystart"; break;}case 82: {qDebug() << "parser:Xend"; break;}case 83: {qDebug() << "parser:Yend"; break;}case 84: {qDebug() << "parser:Width"; break;}case 85: {qDebug() << "parser:Xpos: " << sym(1); break;}case 86: {qDebug() << "parser:Ypos" << sym(1); break;}case 87: {qDebug() << "parser:Xsize" << sym(1); break;}case 88: {qDebug() << "parser:Ysize" << sym(1); break;}case 89: {qDebug() << "parser:Xdelta"; break;}case 90: {qDebug() << "parser:Ydelta"; break;}case 91: {qDebug() << "parser:Orientation"; break;}case 92: {qDebug() << "parser:Diameter"; break;}case 93: {qDebug() << "parser:Xoffset"; break;}case 94: {qDebug() << "parser:Yoffset"; break;}case 95: {qDebug() << "parser:DrillX"; break;}case 96: {qDebug() << "parser:DrillY"; break;}case 97: {qDebug() << "parser:NetNumber"; break;}case 98: {qDebug() << "parser:Layer"; break;}case 105: {qDebug() << "parser:Identifier:" << sym(1); break;}
				case 106: {
					qDebug() << "parser:BeginPad";
					pad = new Pad();
					break;
					}
				case 107: {qDebug() << "parser:ModuleAttributes:" << sym(1); break;}
    } // switch
}
