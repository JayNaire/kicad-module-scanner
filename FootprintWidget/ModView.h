/*
 * ModWidget.h
 *
 *  Created on: 28 Apr 2012
 *      Author: root
 */

#ifndef MODVIEW_H_
#define MODVIEW_H_
#include <QtGui>
#include "qparser.h"
#include "Pip.h"
/////////////////////////////////////// Class Field //////////////////////////////////////
class Field{
friend class ModView; //access to protected members in ModView::addField
public:
	enum type{
		refdes,
		value,
		other
	};
	Field(enum type t){this->fieldType = t;};

	virtual ~Field(){};
	void setParams(int Xpos, int Ypos, int Xsize, int Ysize, int Orientation, int Width, QString N, QString Visibility){
		(void) N; //??
		xPos = Xpos;
		yPos = Ypos;
		xSize = Xsize; //width of character "M" in tenths of a mil
		ySize = Ysize; //height of character "M" in tenths of a mil
		orientation = Orientation;
		width = Width;
		visibility = Visibility;
	};
	void setLayer(int Layer){ layer = Layer;};
	void setText(QString Text){ text = Text;};
	void setTextStyle(QString TextStyle){ textStyle = TextStyle;};

protected:
	enum type fieldType;
	int xPos;
	int yPos;
	int xSize;
	int ySize;
	int orientation;
	int width;
	QString textStyle; //I or N
	QString visibility;
	int layer;
	QString text;
};

/////////////////////////////////////// Class Pad //////////////////////////////////////
class Pad: public QGraphicsItemGroup {
public:
	Pad(): QGraphicsItemGroup(){drillHoleIsSlotted = false; attribute = "";};
	Pad(const QString name): QGraphicsItemGroup(){this->name = name;drillHoleIsSlotted = false;}
	virtual ~Pad(){};
	enum PadType{
		circular,
		rectangular,
		oblong,
		trapezoidal,
		unknown
	};
    void setType(QString strType){
    	if      (strType == "C") type = circular;
    	else if (strType == "R") type = rectangular;
    	else if (strType == "O") type = oblong;
    	else if (strType == "T") type = trapezoidal;
    	else type = unknown;
    }
    void setShape(QString PadName, QString PadShape, QString Xsize, QString Ysize, QString Xdelta, QString Ydelta, QString Orientation){
    	//this is a "Sh" record. PadName can be anything including "HOLE" which is very confusing with an "At" record. Xsize = width, Ysize = height
    	bool Ok;
    	name = PadName;
    	setType(PadShape);
    	sizeX = Xsize.toInt(&Ok);
    	sizeY = Ysize.toInt(&Ok);
    	offsetX = Xdelta.toInt(&Ok);
    	offsetY = Ydelta.toInt(&Ok);
    	orientation = Orientation.toInt(&Ok);
    }
    void setRoundDrill(QString Diameter, QString Xoffset, QString Yoffset){
    	bool Ok;
    	drillDiameter = Diameter.toInt(&Ok);
    	drillOffsetX = Xoffset.toInt(&Ok);
    	drillOffsetY = Yoffset.toInt(&Ok);
    }
    void setOvalDrill(QString Diameter, QString Xoffset, QString Yoffset, QString padshape, QString DrillX, QString DrillY){
    	bool Ok;
    	drillDiameter = Diameter.toInt(&Ok);
    	drillOffsetX = Xoffset.toInt(&Ok);
    	drillOffsetY = Yoffset.toInt(&Ok);
    	//ignore padshape - it's always capital Oh
    	drillEllipticalX = DrillX.toInt(&Ok);
    	drillEllipticalY = DrillY.toInt(&Ok);
    	drillHoleIsSlotted = true;
    }
    void setAttributes(QString padattribute, QString identifier, QString LayerMask){
    	attribute = padattribute;
    	//ignore identifier
    	layerMask = LayerMask;
    }
    void setNetReference(QString NetNumber, QString NetName){
    	netName = NetName;
    	netNumber = NetNumber;
    }
    void setPosition(QString x, QString y){
    	bool Ok;
    	padCentreX = x.toInt(&Ok);
    	padCentreY = y.toInt(&Ok);
    }
    void prepareItems();

private:
	QWidget* parent;
	PadType type;
	QString attribute; //"STD" "SMD" "CONN" "HOLE" "MECA" //if "HOLE" this doesn't define a hole actually, that's done by setting the pad name to "HOLE" in a "Sh" record
	QString layerMask; //we record it but do nothing with it yet
	QString name;
	QString netName;
	QString netNumber;
	int padCentreX;			//x of nominal centre (Po) relative to the parent module position
	int padCentreY;			//y of nominal centre (Po) relative to the parent module position
	int orientation;		//in tenths of a degree (Sh)
	int sizeX;				//diameter of a round pad, x length or width of other pads (Sh)
	int sizeY;				//y length or height of other pads (Sh)
	int offsetX;			//padoffset from (nominal X centre) padCentreX (Sh)
	int offsetY;			//padoffset from (nominal Y centre) padCentreY (Sh)
	int drillDiameter;		//(Dr)
	int drillOffsetX;		//drill centre offset from padCentreX
	int drillOffsetY;		//drill centre offset from padCentreY
	int drillEllipticalX;	//slotted hole x length (width?)
	int drillEllipticalY;	//slotted hole y length (height?
	bool drillHoleIsSlotted;//set by setOvalDrill; cleared by constructors

};
#include "footprint_parser.h"

/////////////////////////////////////// Class ModView //////////////////////////////////////
class ModView: public QGraphicsView {
	Q_OBJECT
public:
	ModView();
	ModView(QGraphicsScene *scene, QWidget *w);
	ModView(QWidget *w);
	virtual ~ModView();
	void setData(const QString &data);
    QString getData() const;
	bool parse();
    FootprintParser footprintParser;
    enum  gridUnits{
    	mm,
    	mil,
    	none
    } gridUnits;
public:
    QList<QGraphicsLineItem*> segments;
    QList<QGraphicsEllipseItem*> circles;
    QList<QGraphicsPathItem*> arcs;
    QList<QGraphicsSimpleTextItem*> fields;

    //! AddSegments - called from footprint_parser.cpp to add segments to footprint object
    void addSegment(int xStart, int yStartY, int xEnd, int yEnd, int width, int layer);
    void addCircle(int xCentre, int  yCentre, int  xPoint, int  yPoint, int  width, int layer);
    void addArc(int xCentre, int yCentre, int xEnd, int yEnd, int angle, int width, int layer);
    void addPad(Pad *pad){pads.append(pad); qDebug() << "Added pad";}
    void addField(Field *field); //{fields.append(field); qDebug() << "Added field";}

public slots:
	void zoomIn() { scale(1.2, 1.2); }
	void zoomOut() { scale(1 / 1.2, 1 / 1.2); }
	void zoomToFit() { fitInView(0, 0, scene->width(), scene->height(), Qt::KeepAspectRatio); update();}
	void zoomReset(){
		resetMatrix();
	}
	void toggleShowGrid(bool b){
		showGrid = b;
		drawGrid();
	}

	void gridUnitsInMil(bool b){
		gridUnits = b ? mil : mm; //! if b is true (mil) grid shows green lines at 10mil intervals; if false (mm) grid shows green lines at 0.5mm intervals
		drawGrid();
		measuringPipPositionChanged(QPointF()); //OK to use a null point, it's not used
	}
	void setPadOpacity(int opacity){ //opacity slider = 0 to 100
		padOpacity = (qreal)opacity/100;
		for (int i = 0; i<pads.count(); i++){
			pads.at(i)->setOpacity(padOpacity); //0 to 1.0
		}
	}
	void measuringPipPositionChanged(QPointF position);

public: signals:
	/**
	 * @brief we emit this whenever a measurement pip changes position.
	 *  values are pip centres in mil or mm depending on the setting of gridUnits
	 */
	void measurementChanged(QPointF, QPointF);

private:
     void init();
     void drawSegments(); //draw $DSs adds segments to scene
     void drawArcs(); //draw $DAs
     void drawCircles(); //draw $DCs
     void drawPads(); //draw $PADs
     void drawFields(); //draw $T0,$T1,$Txx
     void drawGrid();
     void paintEvent(QPaintEvent *e);
     void updateScene();

     QGraphicsScene *scene;
     bool parserHasRun; //! set false by setData(), set true by parse(),, used by paintEvent()
     bool parseOk; //! true if text parses correctly, false otherwise. Set by parse(), used by paintEvent()
     QString data;
     QList<Pad*> pads;
     QGraphicsItemGroup *grid;
     bool showGrid;
     enum gridUnits gridIsDrawnIn; //! says which units the grid is currently drawn in
     qreal padOpacity; //! 0 = invisible, 1 = opaque
     Pip *measuringPip1;
     Pip *measuringPip2;
};

#endif /* MODVIEW_H_ */
