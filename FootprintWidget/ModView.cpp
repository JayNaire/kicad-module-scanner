/*
 * ModView.cpp
 *
 *  Created on: 28 Apr 2012
 *      Author: root
 */

#include <QtGui>
#include <QMetaObject>
#include "footprint_lex.h"
#include "footprint_parser.h"
#include "ModView.h"
#include <math.h>
#define PI (3.14159)
#define TEXT_SCALE (20)

/////////////////////////////////////////PAD/////////////////////////////////
/**
 * @brief Pad::prepareItems: called just before being added to a scene to set up child QGraphicsItems
 * Pad is derived from QGraphicsItemGroup.
 * We create the pad outline, drill hole and pin name graphics items and add them to this group.
 * Our caller will then add us to ModView::scene
 */
void Pad::prepareItems()
{
	QPen pen(QBrush(Qt::red), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush brush;
	//qDebug() << "attribute = " << attribute;
	if (attribute == "HOLE" || name == "HOLE"){ //name defines a hole more than attribute (At) it seems
		brush.setStyle(Qt::Dense5Pattern);
		brush.setColor(Qt::black);
	}
	else{
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::red);
	}
	this->childItems().clear();
	QGraphicsItem *item;
	switch (type){
	case circular:{
		qreal r = sizeX/2; //sqrt(pow(offsetX - sizeX, 2) + pow(offsetY - sizeY, 2));
		item = new QGraphicsEllipseItem(-r , -r, 2*r, 2*r);
		((QGraphicsEllipseItem*)item)->setPen(pen);
		((QGraphicsEllipseItem*)item)->setBrush(brush);
		break;
	}
	case rectangular:{
		qreal cX = sizeX/2;
		qreal cY = sizeY/2;
		item = new QGraphicsRectItem(-cX + offsetX,-cY + offsetY,sizeX, sizeY);
		((QGraphicsRectItem*)item)->setPen(pen);
		((QGraphicsRectItem*)item)->setBrush(brush);
		break;
	}
	case oblong:{
		//oblong means a rectangular pad with rounded ends eg:
		// -----
		//(  o  )
		// -----
		qreal width, height;
		//width is normally sizeX, height is sizeY, but I'll bet that is not always the case esp. with converted footprints
		//which swap width for height instead of rotating the pad - may need following code in that case?
//		if ( sizeX < sizeY ){
//			width = sizeX;
//			height = sizeY;
//		}
//		else{
//			width = sizeY;
//			height = sizeX;
//		}
		width = sizeX;
		height = sizeY;
		qreal x1,y1,x2,y2;
		x1 = offsetX;
		y1 = offsetY - (height/2) + (width/2);
		x2 = x1;
		y2 = y1 + height - width;
		//fake a rounded pad with a fat line having rounded ends
		QPen pen1(brush, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		item = new QGraphicsLineItem(x1,y1,x2,y2);
		((QGraphicsLineItem*)item)->setPen(pen1);
		break;
	}
	case trapezoidal:
		qDebug() << "\t\t\tPad::PrepareItems: trapezoidal pad type - not implemented";
		return;
		break;
	default:
		qDebug() << "\t\t\tPad::PrepareItems: Unknown pad type";
		return;
		break;
	}
	//that's the landing pads done now for the drill holes
	QPen drillPen(QBrush(Qt::black), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush drillBrush(Qt::black,Qt::SolidPattern);
	if (attribute != "SMD"){
		if (drillHoleIsSlotted){
			QGraphicsLineItem *holeItem;
			qreal width, height;
			width = drillEllipticalX;
			height = drillEllipticalY;
			qreal x1,y1,x2,y2;
			x1 = drillOffsetX;
			y1 = drillOffsetY - (height/2) + (width/2);
			x2 = x1;
			y2 = y1 + height - width;
			//fake a slotted hole with a fat line having rounded ends
			QPen slottedDrillPen(QBrush(Qt::black), drillDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
			holeItem = new QGraphicsLineItem(x1,y1,x2,y2);
			holeItem->setPen(slottedDrillPen);
			holeItem->setParentItem(item);
//			holeItem->moveBy(drillOffsetX, drillOffsetY);
		}
		else{
			QGraphicsEllipseItem *holeItem;
			qreal r = drillDiameter/2;
			holeItem = new QGraphicsEllipseItem(-r , -r, 2*r, 2*r);
			holeItem->setPen(drillPen);
			holeItem->setBrush(drillBrush);
			holeItem->setParentItem(item);
			holeItem->moveBy(drillOffsetX, drillOffsetY);
		}
	}
	//drill holes done now pin names
	QGraphicsTextItem *t = new QGraphicsTextItem();
	QFont font("Times", 10, QFont::Bold);
	t->setFont(font);
	t->setDefaultTextColor(Qt::green);
	t->setParentItem(item);
	t->setPlainText(name);
	t->setScale(20);
//	moveBy: Moves the item by dx points horizontally, and dy point vertically.
	t->setTransformOriginPoint(t->boundingRect().width()/2,t->boundingRect().height()/2);
	t->moveBy(-t->boundingRect().width()/2, -t->boundingRect().height()/2);
	t->rotate(orientation/10); //cancel any pad orientation so text is always vertical
	t->setZValue(20);

	//all done now move ourselves to the correct position in the footprint
	item->rotate(-orientation/10);
	addToGroup(item);
	moveBy(padCentreX, padCentreY);
}

/////////////////////////////////////////MODVIEW/////////////////////////////////
void ModView::init(){ //called from constructors only
	gridUnits = mil;
	gridIsDrawnIn = none;
	footprintParser.setView(this);
	parseOk = false;
	parserHasRun = false;
	padOpacity = 1;
	scene = new QGraphicsScene(this);
	setScene(scene);
	grid=0;
	showGrid = false;
	updateScene();
}
void ModView::updateScene()
{
	scene->clear();
	if (data.length()){ //data has been set but didn't parse or hasn't been parsed yet
		if (parserHasRun){
			if (! parseOk){
				scene->addText(QString("Parse failed.\n%1").arg(footprintParser.getErrorMessage()));
//				return;
			}
			else{
				drawSegments();
				drawCircles();
				drawArcs();
				drawPads();
				drawFields();

				drawGrid();
				grid->setVisible(showGrid);

				//TEST ONLY centre pip - quite useful so leave in!
//				int radius = 100;
//				int width = 0;
//				QBrush brush(Qt::gray);
//				QPen pen(brush, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//				QGraphicsItemGroup *pip = new QGraphicsItemGroup();
//				QGraphicsLineItem *hor = new QGraphicsLineItem(-radius,0,radius,0);
//				QGraphicsLineItem *ver = new QGraphicsLineItem(0,-radius,0,radius);
//				QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-radius, -radius, 2*radius, 2*radius);
//				hor->setPen(pen);
//				ver->setPen(pen);
//				item->setPen(pen);
//				hor->setParentItem(pip);
//				pip->setZValue(100);
//				ver->setParentItem(pip);
//				item->setParentItem(pip);
//				pip->setToolTip("Footprint origin");

//				pip->setAcceptedMouseButtons(Qt::LeftButton);
//				pip->setFlag(QGraphicsItem::ItemIsMovable);
//				connect (pip, SIGNAL(),this,SLOT(onPipMousePressEvent()))
//				circles.append(item);
				measuringPip1 = new Pip(Qt::magenta);
				scene->addItem(measuringPip1);
				measuringPip2 = new Pip(Qt::cyan);
				scene->addItem(measuringPip2);
				connect(measuringPip1, SIGNAL(positionChanged(QPointF)),this,SLOT(measuringPipPositionChanged(QPointF)));
				connect(measuringPip2, SIGNAL(positionChanged(QPointF)),this,SLOT(measuringPipPositionChanged(QPointF)));
			}
		}
		else{
			scene->addText(QString("Data not parsed yet."));
//			return;
		}
	}
	else{ //data not initialised yet
		scene->addText(QString("No data."));
//		return;
	}
	update();
}

ModView::ModView() {
	init();
}
ModView::ModView(QGraphicsScene *scene, QWidget *w) : QGraphicsView(scene,w){
	init();
}
ModView::ModView(QWidget *w) : QGraphicsView(w){
	init();
}

ModView::~ModView() {
	// TODO Auto-generated destructor stub
}

void ModView::addSegment(int xStart, int yStart, int xEnd, int yEnd, int width, int layer){
	QGraphicsLineItem *item = new QGraphicsLineItem(xStart, yStart, xEnd, yEnd);
	item->setPen(QPen(QBrush(Qt::blue), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	segments.append(item);
};

void ModView::addField(Field *field){
	qDebug() << "physicalDpiX():" << this->physicalDpiX() << "physicalDpiY():" << physicalDpiY(); //physicalDpiX():  96 physicalDpiY():  96
	qDebug() << "logicalDpiX():" << this->logicalDpiX() << "logicalDpiY():" << logicalDpiY();     //logicalDpiX():  96 logicalDpiY():  96
	QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem(field->text);
	item->setBrush(QBrush(Qt::blue));
	QFont f;
	//we want a font that is ySize/10000 inches tall (cannot cope with xSize being different from ySize, just take the largest)
	qDebug() << "field->xSize" << field->xSize << "field->ySize" << field->ySize;
	qreal fontSize = field->xSize > field->ySize ? field->xSize : field->ySize;
//	fontSize /= 10000; //fontsize is now in inches
//	fontSize *= 72/10000; //fontsize is now in points (72 points per inch)
	f.setPointSizeF(fontSize);
	qDebug() << "f.pointSize():" << f.pointSize() << "f.pixelSize():" << f.pixelSize();//f.pointSize():  10 f.pixelSize():  -1
	//the fields xSize and ySize are the width and height in tenths of a mil of an "M" character
	QFontInfo fi(f);
	qDebug() << "fi.pointSize():" << fi.pointSize() << "fi.pixelSize():" << fi.pixelSize();//fi.pointSize():  10 fi.pixelSize():  13
//	f.setPixelSize(fi.pixelSize());
//	f.setPointSize(f.pointSize()*10);
	qDebug() << "f.pointSize():" << f.pointSize() << "f.pixelSize():" << f.pixelSize();//f.pointSize():  10 f.pixelSize():  -1
	f.setItalic(field->textStyle == "I");
	item->setFont(f);
//	item->setTextWidth(field->width);
	qreal centreX = item->boundingRect().width()/2;
	qreal centreY = item->boundingRect().height()/2;
	item->moveBy(field->xPos - centreX, field->yPos - centreY);
	fields.append(item);
}

void ModView::addCircle(int xCentre, int  yCentre, int  xPoint, int  yPoint, int  width, int layer){
	qreal radius = sqrt(pow(xPoint - xCentre, 2) + pow(yPoint - yCentre, 2));
	QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-radius + xCentre, -radius + yCentre, 2*radius, 2*radius);
	item->setPen(QPen(QBrush(Qt::blue), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	circles.append(item);
};

void ModView::addArc(int xCentre, int yCentre, int xEnd, int yEnd, int angle, int width, int layer){
	//if angle is positive arc should be drawn anticlockwise from the endpoint
	//if angle (in tenths of a degree) is > 3600:
	// in Kicad only the overlap is drawn whereas Qt draws the whole circle...
	//...so we make sure the angle is between 0-3600
	int theAngle = angle % 3600;
	qreal radius = sqrt(pow(xEnd - xCentre, 2) + pow(yEnd - yCentre, 2));
	double length;
	length = yEnd - yCentre;
	qreal startAngle= atan2( -length , (double)(xEnd - xCentre) )*(180 / PI); //radians->degrees
	qreal endAngle = ( -(theAngle/10)); //angle is in tenths of a degree;
	QPainterPath path;
	path.arcMoveTo(-radius + xCentre, -radius + yCentre, 2*radius, 2*radius, startAngle);
	path.arcTo    (-radius + xCentre, -radius + yCentre, 2*radius, 2*radius, startAngle, endAngle);
	QGraphicsPathItem *item1 = new QGraphicsPathItem(path);
	item1->setPen(QPen(QBrush(Qt::blue), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	arcs.append(item1);
}

void ModView::drawSegments()
{
	for (int i = 0; i < segments.count(); i++){
		scene->addItem(segments.at(i));
		segments.at(i)->setZValue(10);
	}
}

void ModView::drawCircles()
{
	for (int i = 0; i < circles.count(); i++){
		scene->addItem(circles.at(i));
		circles.at(i)->setZValue(10);
	}
}

void ModView::drawArcs()
{
	for (int i = 0; i < arcs.count(); i++){
		scene->addItem(arcs.at(i));
		arcs.at(i)->setZValue(10);
	}
}

void ModView::drawFields()
{
	for (int i = 0; i < fields.count(); i++){
		scene->addItem(fields.at(i));
		fields.at(i)->setZValue(10);
	}
}

void ModView::drawPads()
{
//	pinNames = new QGraphicsItemGroup();
	for (int i=0; i<pads.count(); i++){
		pads.at(i)->prepareItems();
		pads.at(i)->setOpacity(padOpacity);
		scene->addItem(pads.at(i));
		pads.at(i)->setZValue(10);
	}
}

/**
 * Grid:
 * We draw everything at the dimensions given in the .mod file
 * which represent tenths of a mil. Therefore 10 units = 1 mil, 100 units = 10 mil etc.
 * For a metric grid; 1mm = 39.3700787mil (1mil = 0.0254000000259mm)
 */
#define UNITS_IN_A_MM (393.700787) //a unit is a tenth of a mil ie:the raw units found in a .mod file
#define GRID_SIZE_MIL (100) //pixels = 10mil
#define GRID_SIZE_MM (UNITS_IN_A_MM / 2) //1mm = 39.37mil = 393.7 tenths of a mil; so /2 means 1 minor grid (green) every half mm
#define MAJOR_GRID_INTERVAL (5) //red gridline every n lines = every n*10mil or every n*0.5mm
#define GRID_LINE_WIDTH (0) //cosmetic
#define GRID_BORDER (gridSize * MAJOR_GRID_INTERVAL)
void ModView::drawGrid()
{
	if (grid){
		if (gridIsDrawnIn == gridUnits){
			grid->setVisible(showGrid);
			return;
		}
		//grid is not drawn in requested units, delete and remake it
		if (scene->items().contains(grid)) scene->removeItem(grid);
		delete grid;
	}
	qreal gridSize;
	gridSize = gridUnits == mil ? GRID_SIZE_MIL : GRID_SIZE_MM;
	grid = new QGraphicsItemGroup();
	grid->setFlag(QGraphicsItem::ItemIsMovable);
	QPen pGreen(QBrush(Qt::green), GRID_LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QPen pRed(QBrush(Qt::red), GRID_LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QPen pBlack(QBrush(Qt::black), GRID_LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	qreal topY = scene->sceneRect().top()-GRID_BORDER;
	qreal bottomY = scene->sceneRect().bottom()+GRID_BORDER;
	QGraphicsLineItem *item;
	//	draw Y axis in black
	item = new QGraphicsLineItem(0, topY, 0, bottomY);
	item->setPen(pBlack);
	grid->addToGroup(item);

	//draw vertical grid lines
	int j;
	qreal i;

	for (i=gridSize, j=1; i<scene->sceneRect().right(); i+=gridSize, j++){
		item = new QGraphicsLineItem(i, topY, i, bottomY);
		if (i==0) item->setPen(pBlack);
		else{
			if (j % MAJOR_GRID_INTERVAL == 0) item->setPen(pRed);
			else item->setPen(pGreen);
		}
		grid->addToGroup(item);
	}
	for (i=-gridSize, j=1; i>scene->sceneRect().left(); i-=gridSize, j++){
		item = new QGraphicsLineItem(i, topY, i, bottomY);
		if (j % MAJOR_GRID_INTERVAL == 0) item->setPen(pRed);
		else item->setPen(pGreen);
//		scene->addItem(item);
		grid->addToGroup(item);
	}

	qreal leftX = scene->sceneRect().left()-GRID_BORDER;
	qreal rightX = scene->sceneRect().right()+GRID_BORDER;
	//	draw X axis in black
	item = new QGraphicsLineItem(leftX, 0, rightX, 0);
	item->setPen(pBlack);
	grid->addToGroup(item);

	//draw horizontal grid lines
	for (i=gridSize, j=1; i<scene->sceneRect().bottom(); i+=gridSize, j++){
		item = new QGraphicsLineItem(leftX, i, rightX, i);
		if (i==0) item->setPen(pBlack);
		else{
			if (j % MAJOR_GRID_INTERVAL == 0) item->setPen(pRed);
			else item->setPen(pGreen);
		}
		grid->addToGroup(item);
	}
	for (i=-gridSize, j=1; i>scene->sceneRect().top(); i-=gridSize, j++){
		item = new QGraphicsLineItem(leftX, i, rightX, i);
		if (j % MAJOR_GRID_INTERVAL == 0) item->setPen(pRed);
		else item->setPen(pGreen);
//		scene->addItem(item);
		grid->addToGroup(item);
	}
	scene->addItem(grid);
	grid->setZValue(0); //send to back
	grid->setVisible(showGrid);
	gridIsDrawnIn = gridUnits;
}

void ModView::setData(const QString & data)
{
	this->data = data;
	parserHasRun = false;
	update();
}

QString ModView::getData() const
{
    return data;
}

void ModView::paintEvent(QPaintEvent *e)
{
	QGraphicsView::paintEvent(e);
}

bool ModView::parse()
{
	segments.clear();
	circles.clear();
	arcs.clear();
	pads.clear();
	fields.clear();
	scene->clear(); //also removes grid items
	gridIsDrawnIn = none;
	grid = 0;
	scene = new QGraphicsScene(this); //must do this to reset sceneRect properly
	setScene(scene);
//	setSceneRect(QRectF());
//	qDebug() << scene->items().count();
//	qDebug() << scene->sceneRect();
//	qDebug() << sceneRect();
//	scene->setSceneRect(QRectF(0,0,10,10));
	QByteArray ba = data.toLocal8Bit();
	const char *cstr = ba.data();
	footprint_scan_string(cstr); //if you keep the returned YY_BUFFER_STATE you can check various parser things if scan fails
	parseOk = footprintParser.parse();
	parserHasRun = true;
	updateScene();
//	qDebug() << scene->sceneRect();
//	qDebug() << sceneRect();
	zoomToFit(); //doesn't work from constructor
	return parseOk;
}

/**
 *
 * @param position is the position of one of two pips but we don't use it
 * @warning This function is called with a null position @see gridUnitsInMil
 */
void ModView::measuringPipPositionChanged(QPointF position){
	(void) position;
//	qDebug() << "ModView::measuringPipPositionChanged:" << position;
	QPointF p1,p2;
	if (gridUnits == mm){ // send dimensions in mm
		p1 = measuringPip1->pos()/UNITS_IN_A_MM;
		p2 = measuringPip2->pos()/UNITS_IN_A_MM;
	}
	else{ // send dimensions in mil
		p1 = measuringPip1->pos()/10;
		p2 = measuringPip2->pos()/10;
	}
	emit measurementChanged(p1,p2);
}








