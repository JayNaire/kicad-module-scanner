/*
 * Pip.cpp
 *
 *  Created on: 24 May 2012
 *      Author: root
 */
#include <QtGui>
#include "Pip.h"

Pip::Pip(Qt::GlobalColor color) : QGraphicsItemGroup(), QObject() {
	// TODO Auto-generated constructor stub
	radius = 100;
	width = 0;
	QBrush brush(color);
	QPen pen(brush, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//	QGraphicsItemGroup *pip = new QGraphicsItemGroup();
	QGraphicsLineItem *hor = new QGraphicsLineItem(-radius,0,radius,0);
	QGraphicsLineItem *ver = new QGraphicsLineItem(0,-radius,0,radius);
	QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-radius, -radius, 2*radius, 2*radius);
	hor->setPen(pen);
	ver->setPen(pen);
	item->setPen(pen);
	hor->setParentItem(this);
	setZValue(100);
	ver->setParentItem(this);
	item->setParentItem(this);
	setFlags(QGraphicsItem::ItemIsMovable | ItemSendsGeometryChanges);
	setToolTip("Drag to measure a distance");
}

Pip::~Pip() {
	// TODO Auto-generated destructor stub
}

QVariant Pip::itemChange(GraphicsItemChange change, const QVariant &value){
	if (change == ItemPositionChange){
		QPointF newPos = value.toPointF();
		emit positionChanged(newPos);
//		qDebug() <<  "measuringPip: position : " << newPos;
	}
	return value;
}
