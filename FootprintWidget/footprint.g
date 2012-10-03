%parser footprint_grammar
%decl footprint_parser.h
%impl footprint_parser.cpp

%token_prefix Token_


%token number
%token float
%token index
%token name
%token keywords
%token beginmodule
%token endmodule
%token beginindex
%token endindex
%token beginpad
%token quotedstring
%token endpad
%token padshape
%token padattribute
%token beginshape3d
%token endshape3d
%token identifier
%token hex
%token moduleattributes
%token N
%token V
%token I
%token Po
%token Li
%token Cd
%token Kw
%token Sc
%token Op
%token Ne
%token Dr
%token At
%token Sh
%token Na
%token Of
%token Ro
%token AR

%token T0
%token T1
%token T
%token DS
%token DA
%token DC
%start Goal


/:
/* ROB: This file was made by qlalr from footprint.g"*/
#ifndef FOOTPRINTPARSER_H
#define FOOTPRINTPARSER_H
#include <QtGui>
#include "qparser.h"
#include "footprint_grammar_p.h"
//#include "ModView.h"
class ModView;
class Pad;
extern char* footprinttext;
class FootprintParser: public QParser<FootprintParser, $table, QString> /*QString - this typename will be returned by sym(n)*/
{
public:
	FootprintParser() : QParser(){};
	int nextToken();
	void consumeRule(int ruleno);
	void setView(ModView *view){this->view = view;};
private:
	ModView *view;
	Pad *pad;
};

#endif // FOOTPRINTPARSER_H
:/


/.
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
./

Goal: Footprint ;
/.
case $rule_number:
	qDebug() << "parser Finished: Goal achieved!";
	break;
./

Footprint	:	BeginModule EndModule
			|	BeginModule ModuleRecords EndModule
			|	
			;

BeginModule	:	beginmodule Identifier
			;
/.
case $rule_number:
	//name = sym(1); 
	qDebug() << "parser: seen Rule BeginModule\n\t Module Name is -->: " << sym(1);
	break;
./

ModuleRecords	: ModuleRecord
				| ModuleRecords ModuleRecord
				;

ModuleRecord	: Pad
				| ModulePosition
				| ModuleLi
				| ModuleAR
				| ModuleCd
				| ModuleKw
				| ModuleSc
				| ModuleOp
				| ModuleDS
				| ModuleDC
				| ModuleDA
				| ModuleT0
				| ModuleT1
				| ModuleT
				| ModuleAt
				| Shape3d
				;
				
ModulePosition	: Po Xpos Ypos Orientation Layer TimeStamp HexOrNumber ModuleAttributes /./*Don't know what field HexOrNumber is used for*/./
				;

ModuleLi		: Li Identifier
				;
					
ModuleAR		: AR Identifier
				;
					
ModuleCd		: Cd  /.case $rule_number: {qDebug() << "parser:Cd:" << sym(1); break; /*returns whole line after Li*/}./
				;
						 
ModuleKw		: Kw  /.case $rule_number: {qDebug() << "parser:Kw:" << sym(1); break; /*returns whole line after Li*/}./
				;

ModuleSc		: Sc TimeStamp
				;
				
ModuleOp		: Op number number number
				;

ModuleDS		: DS Xstart Ystart Xend Yend Width Layer
				;
				/.
				//DS - draw segment
				case $rule_number:{
					qDebug() << "parser:ModuleDS: adding segment";
					view->addSegment(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok));
					break;
				}
				./

ModuleDC		: DC Xcentre Ycentre Xpoint Ypoint Width Layer
				;
				/.
				//DC - draw circle
				case $rule_number:{
					qDebug() << "parser:ModuleDC: adding circle";
					view->addCircle(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok));
					break;
				}
				./
						 
ModuleDA		: DA  Xstart Ystart Xend Yend Angle Width Layer
				;
				/.
				//DA - draw arc
				case $rule_number:{
					qDebug() << "parser:ModuleDA: adding arc";
					view->addArc(sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6).toInt(&Ok),sym(7).toInt(&Ok));
					break;
				}
				./
						 
ModuleT0		: BeginT0 FieldRecord quotedstring
				/. /*REFDES*/
				case $rule_number:{
					qDebug() << "parser:T0(refdes):" << sym(3);
					field->setText(sym(3));
					view->addField(field);
					break;
				}
				./
				;
BeginT0			: T0
				/.
				case $rule_number:{
					qDebug() << "parser:creating new refdes field";
					field = new Field(Field::refdes);
					break;
				}
				./
				;
										 
ModuleT1		: BeginT1 FieldRecord quotedstring
				/. /*VALUE returns whole line after T1*/
				case $rule_number: {
					qDebug() << "parser:T1(value):" << sym(2);
					field->setText(sym(2));
					view->addField(field);
					break;
				}
				./
				;
						 
BeginT1			: T1
				/.
				case $rule_number:{
					qDebug() << "parser:creating new value field";
					field = new Field(Field::value);
					break;
				}
				./
				;
										 
ModuleT			: BeginT FieldRecord quotedstring
				/. /*TEXT FIELD returns whole line after Txx*/
				case $rule_number: {
					qDebug() << "parser:Txx(textfield):" << sym(2);
					field->setText(sym(2));
					view->addField(field);
					break; }./
				;
						 
BeginT			: T
				/.
				case $rule_number:{
					qDebug() << "parser:creating new other field";
					field = new Field(Field::other);
					break;
				}
				./
				;
										 
ModuleAt		: At	padattribute
				| At	identifier
				/.
				//This is a fix as At SMD and At VIRTUAL (more?) are apparently valid at module level as well as pad level
				//although it's meaning is undocumented
				./
				;
						 
EndModule	:	endmodule
			|	endmodule identifier
			;
/.
case $rule_number:
	qDebug() << "parser:EndModule:" << sym(2);
	break;
./

FieldRecord		: Xpos Ypos Xsize Ysize Orientation Width N Visibility
				/.
				case $rule_number: { //ERROR HERE sym(1) is value for Ypos not Xpos etc.
					//                                   Xpos       Ypos     Xsize     Ysize Orientation   Width      N        visibility
					qDebug() << "parser:FieldRecord:" << sym(0) << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6) << sym(7);
					field->setParams(sym(0).toInt(&Ok),sym(1).toInt(&Ok),sym(2).toInt(&Ok),sym(3).toInt(&Ok),sym(4).toInt(&Ok),sym(5).toInt(&Ok),sym(6),sym(7));
					break;
				}
				./
				| FieldRecord Layer
				/.
				case $rule_number: {
					qDebug() << "parser:FieldRecord:Layer" << sym(1);
					field->setLayer(sym(1).toInt(&Ok));
					break;
				}
				./
				| FieldRecord TextStyle
				/.
				case $rule_number: {
					qDebug() << "parser:FieldRecord:TextStyle" << sym(1);
					field->setTextStyle(sym(1));
					break;
				}
				./
				;
				
Visibility		:	V
				|	I
				;
								
TextStyle		: 	N
				|	I
				;
								
Shape3d			: beginshape3d ShapeRecords endshape3d
				;
ShapeRecords	: ShapeRecord
				| ShapeRecords ShapeRecord
				;
ShapeRecord		: Na quotedstring
				| Sc float float float
				| Of float float float
				| Ro float float float
				;


			
Pad				: BeginPad PadRecords endpad;
/.
case $rule_number:
	qDebug() << "parser:Pad: Seen a complete pad"; //OK
	view->addPad(pad);
	break;
./
	 	
PadRecords	: PadRecord
			| PadRecords PadRecord
			;
/.
case $rule_number:
	qDebug() << "parser:PadRecords:"; //OK
	break;
./
			
PadRecord		: PadShapeRecord
				| PadRoundDrillRecord
				| PadOvalDrillRecord
				| PadAttributes
				| PadNetReference
				| PadPosition
				;
			
			
PadShapeRecord	: Sh PadName PadShape Xsize Ysize Xdelta Ydelta Orientation 
				;
/.
case $rule_number:
	qDebug() << "parser:PadShapeRecord: " << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6) << sym(7);
	pad->setShape( sym(1), sym(2), sym(3), sym(4), sym(5), sym(6), sym(7));
	break;
./

TimeStamp		:	HexOrNumber /.case $rule_number: {qDebug() << "parser:TimeStamp"; break;}./
				;
HexOrNumber			: hex
					| number
					;

PadRoundDrillRecord	: Dr Diameter Xoffset Yoffset
					;
/.
case $rule_number:
	qDebug() << "parser:PadRoundDrillRecord: " << sym(1) << sym(2) << sym(3);
	pad->setRoundDrill( sym(1), sym(2), sym(3));
	break;
./

PadOvalDrillRecord	: Dr Diameter Xoffset Yoffset padshape DrillX DrillY
					;

/.
case $rule_number:
	qDebug() << "parser:PadOvalDrillRecord: " << sym(1) << sym(2) << sym(3) << sym(4) << sym(5) << sym(6);
	//rarely seen; padshape is always O (capital Oh not zero)
	pad->setOvalDrill( sym(1), sym(2), sym(3), sym(4), sym(5), sym(6));
	break;
./

PadAttributes		: At padattribute N LayerMask
					;
/.
case $rule_number:
	//At STD N 00E0FFFF
	qDebug() << "parser:PadAttributes: " << sym(1) << sym(2) << sym(3);
	pad->setAttributes( sym(1), sym(2), sym(3));
	break;
./

PadNetReference		: Ne NetNumber NetName
					;
/.
case $rule_number:
	qDebug() << "parser:PadNetReference: " << sym(1) << sym(2);
	pad->setNetReference( sym(1), sym(2));
	break;
./

PadPosition			: Po Xpos Ypos
					;
/.
case $rule_number:
	qDebug() << "parser:PadPosition: " << sym(1) << sym(2);
	pad->setPosition( sym(1), sym(2));
	break;
./
				
Angle			:	number /.case $rule_number: {qDebug() << "parser:Angle"; break;}./
				;
Xpoint			:	number /.case $rule_number: {qDebug() << "parser:Xpoint"; break;}./
				;
Ypoint			:	number /.case $rule_number: {qDebug() << "parser:Ypoint"; break;}./
				;
Xcentre			:	number /.case $rule_number: {qDebug() << "parser:Xcentre"; break;}./
				;
Ycentre			:	number /.case $rule_number: {qDebug() << "parser:Ycentre"; break;}./
				;
Xstart			:	number /.case $rule_number: {qDebug() << "parser:Xstart"; break;}./
				;
Ystart			:	number /.case $rule_number: {qDebug() << "parser:Ystart"; break;}./
				;
Xend			:	number /.case $rule_number: {qDebug() << "parser:Xend"; break;}./
				;
Yend			:	number /.case $rule_number: {qDebug() << "parser:Yend"; break;}./
				;
Width			:	number /.case $rule_number: {qDebug() << "parser:Width"; break;}./
				;
Xpos			:	number /.case $rule_number: {qDebug() << "parser:Xpos: " << sym(1); break;}./
				;
Ypos			:	number /.case $rule_number: {qDebug() << "parser:Ypos" << sym(1); break;}./
				;	
Xsize			:	number /.case $rule_number: {qDebug() << "parser:Xsize" << sym(1); break;}./
				; 
Ysize			:	number /.case $rule_number: {qDebug() << "parser:Ysize" << sym(1); break;}./
				;
Xdelta			:	number /.case $rule_number: {qDebug() << "parser:Xdelta"; break;}./
				;
Ydelta			:	number /.case $rule_number: {qDebug() << "parser:Ydelta"; break;}./
				;
Orientation		:	number /.case $rule_number: {qDebug() << "parser:Orientation"; break;}./
				;
Diameter		:	number /.case $rule_number: {qDebug() << "parser:Diameter"; break;}./
				;
Xoffset			:	number /.case $rule_number: {qDebug() << "parser:Xoffset"; break;}./
				;
Yoffset			:	number /.case $rule_number: {qDebug() << "parser:Yoffset"; break;}./
				;
DrillX			:	number /.case $rule_number: {qDebug() << "parser:DrillX"; break;}./
				;
DrillY			:	number /.case $rule_number: {qDebug() << "parser:DrillY"; break;}./
				;
NetNumber		:	number /.case $rule_number: {qDebug() << "parser:NetNumber"; break;}./
				;
Layer			:	number /.case $rule_number: {qDebug() << "parser:Layer"; break;}./
				;
				
NetName			:	quotedstring
				;
PadName			:	quotedstring
				;
				
PadShape		:	padshape
				;
				
LayerMask		:	hex
				|	number
				;
				
Identifier		:	
				| identifier /.case $rule_number: {qDebug() << "parser:Identifier:" << sym(1); break;}./
				;

BeginPad		:	beginpad 
				;
				/.
				case $rule_number: {
					qDebug() << "parser:BeginPad";
					pad = new Pad();
					break;
					}
				./
				
ModuleAttributes: moduleattributes /.case $rule_number: {qDebug() << "parser:ModuleAttributes:" << sym(1); break;}./
				;

/.
    } // switch
}
./