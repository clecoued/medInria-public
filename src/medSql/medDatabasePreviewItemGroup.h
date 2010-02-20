/* medDatabasePreviewItemGroup.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Dec 15 09:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 15 09:43:14 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef MEDDATABASEPREVIEWITEMGROUP_H
#define MEDDATABASEPREVIEWITEMGROUP_H

#include <QtGui>

class medDatabasePreviewItem;
class medDatabasePreviewItemGroupPrivate;

class medDatabasePreviewItemGroup : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

    Q_INTERFACES(QGraphicsItem)

public:
     medDatabasePreviewItemGroup(QGraphicsItem *parent = 0);
    ~medDatabasePreviewItemGroup(void);

    void addItem(medDatabasePreviewItem *item);

    void clear(void);

    medDatabasePreviewItem *item(int index);

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    medDatabasePreviewItemGroupPrivate *d;
};

#endif // MEDDATABASEPREVIEWITEMGROUP_H