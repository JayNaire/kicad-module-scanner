/*
 * Pip.h
 *
 *  Created on: 24 May 2012
 *      Author: root
 */

#ifndef PIP_H_
#define PIP_H_
#include <QtGui>
#include <qgraphicsitem.h>

class Pip: public QObject, public QGraphicsItemGroup {
	Q_OBJECT
public:
	Pip(Qt::GlobalColor color);
	virtual ~Pip();
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
	void positionChanged(QPointF position);

private:
	int radius;
	int width;

};

#endif /* PIP_H_ */
