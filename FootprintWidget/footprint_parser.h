
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
class FootprintParser: public QParser<FootprintParser, footprint_grammar, QString> /*QString - this typename will be returned by sym(n)*/
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
