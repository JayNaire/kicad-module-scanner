
%option noyywrap
%{ 
//%option header-file="footprint_lex.h"
//footprint.l - flex turns this file into footprint_lex.cpp 
//tokens are defined in footprint_parser_p.h which is included with footprint_parser.h
#include "footprint_parser.h" 
#include <QtCore>
//footprint_parser.h is produced by qlalr from module.g
//it declares class FootprintParser with members:
// nextToken (see YY_DECL)
// consumeRule

#include <cstdlib>
static QString getToEol();
//int line = 1;
#define YY_DECL int FootprintParser::nextToken()
%}

%%

[ \t\r]		{ /* eat me (\r ignore carriage returns on DOS files*/ }
[\n]			{footprintset_lineno(footprintget_lineno()+1); qDebug() << "lexer:line =" << footprintget_lineno(); /* eat me */ }
^"$MODULE"  	{qDebug() << "lexer: seen $MODULE"; return Token_beginmodule;} 
^"$EndMODULE"	{qDebug() << "lexer: seen $EndMODULE"; return Token_endmodule;}
^"$INDEX"		{return Token_index;}
^"$EndINDEX"		{return Token_endindex;}
^"$PAD"			{qDebug() << "lexer: seen $PAD"; return Token_beginpad;}
^"$EndPAD"		{return Token_endpad;}
^"$SHAPE3D"		{return Token_beginshape3d;}
^"$EndSHAPE3D"	{return Token_endshape3d;}
^"Po"			{return Token_Po;}
^"Li"			{return Token_Li;}
^"Cd"			{sym(1) = getToEol(); return Token_Cd;}
^"Kw"			{sym(1) = getToEol(); return Token_Kw;}
^"Sc"			{return Token_Sc;}
^"Op"			{return Token_Op;}
^"Ne"			{return Token_Ne;}
^"Sh"			{qDebug() << "lexer: seen Sh"; return Token_Sh;}
^"Dr"			{return Token_Dr;}
^"At"			{return Token_At;}
^"Na"			{return Token_Na;}
^"Of"			{return Token_Of;}
^"Ro"			{return Token_Ro;}


[CROT]{1}		{qDebug() << "line:" << footprintget_lineno() << "lexer: seen padshape"; sym(1) = yytext; return Token_padshape;}
^"T0"			{
					qDebug() << "line:" << footprintget_lineno() << "lexer: seen T0";
					//sym(1) = getToEol();
					return Token_T0;
				}
^"T1"			{
					qDebug() << "line:" << footprintget_lineno() << "lexer: seen T1";
					//sym(1) = getToEol();
					return Token_T1;
				}
^"T"[1-9]+[0-9]*		{
							qDebug() << "line:" << footprintget_lineno() << "lexer: seen T[2-99]";
							//sym(1) = getToEol();
							return Token_T;
						}
^"DS"			{qDebug() << "line:" << footprintget_lineno() << "lexer: seen DS"; return Token_DS;}
^"DA"			{return Token_DA;}
^"DC"			{qDebug() << "line:" << footprintget_lineno() << "lexer: seen DC"; return Token_DC;}
^"AR"			{return Token_AR;}

[V]{1}			{qDebug() << "lexer: seen visibility"; sym(1) = QString(yytext); return Token_V;}

[I]{1}			{qDebug() << "lexer: seen visibility"; sym(1) = QString(yytext); return Token_I;}

[N]{1}			{qDebug() << "lexer: seen textstyle"; sym(1) = QString(yytext); return Token_N;}

[FP~]{2}		{
					qDebug() << "lexer: seen moduleattributes";
					sym(1) = QString(yytext);
					return Token_moduleattributes;
				}
[-]{0,1}[0-9]+	{
					qDebug() << "lexer: seen number";
					sym(1) = QString(yytext);
					return Token_number;
				}
[-]{0,1}[0-9]*[.][0-9]+	{
					qDebug() << "lexer: seen float";
					sym(1) = QString(yytext);
					return Token_float;
				}
\"[^"]*\"		{	//any string in quotes (including empty string) - WARNING can match EOL
					QStringList sl = QString(yytext).split('"',QString::SkipEmptyParts); //strip quotes
					sym(1) = sl.count() ? sl.at(0) : QString("");
					qDebug() << "lexer: seen quoted string: " << sym(1);
					return Token_quotedstring;
				}
[^[:space:]"]+ 	{	//any string not including a quote or :space: class character
					/*yylval = yytext; no yylval ??*/
					sym(1) = QString(yytext);
					qDebug() << "lexer: seen string: " << sym(1);
					if ( (sym(1) == "STD") | (sym(1) == "SMD") | (sym(1) == "CONN") | (sym(1) == "HOLE") | (sym(1) == "MECA") ){
						qDebug() << "lexer: returning Token_padattribute";
						return Token_padattribute; //note SMD is also valid at module level if it follows an At
					}
					else if(sym(1).contains( QRegExp("[^0-9A-Fa-f]+") ) ){ //any non-hex character (:isxdigit:)
						qDebug() << "lexer: returning Token_identifier";
						return Token_identifier;
					}
					else{
						qDebug() << "lexer: returning Token_hex";
						return Token_hex;
					}
				}

%%
static QString getToEol(){
	//read remaining characters until EOL (or EOF)
	register int c;
	QString buf;
	while ( ((c = yyinput()) != (int)'\n') && (c != EOF) ){
		buf += c;
	}
	if (c == (int)'\n') footprintset_lineno(footprintget_lineno()+1); //adjust line counting; [\n] rule won't be seen for this \n
	return buf.simplified();
}
		/* graveyard
			sym(1) = atoi (yytext);
		*/
