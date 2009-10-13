/* medDatabaseItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 17 12:08:53 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 28 16:04:30 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 62
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <medSql/medDatabaseItem.h>

class medDatabaseItemPrivate
{
public:
          medDatabaseItem * parentItem;
    QList<medDatabaseItem *> childItems;

    QString            table;
    QList<QVariant> attrData;
    QList<QVariant> itemData;
};

medDatabaseItem::medDatabaseItem(const QString& table, const QList<QVariant>& attributes, const QList<QVariant>& data, medDatabaseItem *parent) : d(new medDatabaseItemPrivate)
{
    d->table = table;
    d->attrData = attributes;
    d->itemData = data;
    d->parentItem = parent;
}

medDatabaseItem::~medDatabaseItem(void)
{
    qDeleteAll(d->childItems);

    delete d;
}

medDatabaseItem *medDatabaseItem::child(int row)
{
    return d->childItems.value(row);
}

medDatabaseItem *medDatabaseItem::parent(void)
{
    return d->parentItem;
}

void medDatabaseItem::append(medDatabaseItem *item)
{
    d->childItems.append(item);
}

int medDatabaseItem::row(void) const
{
    if (d->parentItem)
        return d->parentItem->d->childItems.indexOf(const_cast<medDatabaseItem*>(this));
    
    return 0;
}

int medDatabaseItem::childCount(void) const
{
    return d->childItems.count();
}

int medDatabaseItem::childNumber(void) const
{
    if (d->parentItem)
        return d->parentItem->d->childItems.indexOf(const_cast<medDatabaseItem *>(this));

    return 0;
}

int medDatabaseItem::columnCount(void) const
{
    return d->itemData.count();
}

QVariant medDatabaseItem::data(int column) const
{
    return d->itemData.value(column);
}

bool medDatabaseItem::insertChildren(int position, int count, int columns)
{
    Q_UNUSED(columns);

    if (position < 0 || position > d->childItems.size())
        return false;

    for (int row = 0 ; row < count ; ++row) {
        QString table;
        QList<QVariant> attr;
        QList<QVariant> data;
        medDatabaseItem * item = new medDatabaseItem(table, attr, data, this);
        d->childItems.insert(position, item);
    }

    return true;
}

bool medDatabaseItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > d->itemData.size())
        return false;

    for (int column = 0 ; column < columns ; ++column)
        d->itemData.insert(position, QVariant());

    foreach (medDatabaseItem *child, d->childItems)
        child->insertColumns(position, columns);

    return true;
}

bool medDatabaseItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > d->childItems.size())
        return false;

    for (int row = 0 ; row < count ; ++row)
        delete d->childItems.takeAt(position);

    return true;
}

bool medDatabaseItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > d->itemData.size())
        return false;

    for (int column = 0 ; column < columns ; ++column)
        d->itemData.removeAt(position);

    foreach (medDatabaseItem *child, d->childItems)
        child->removeColumns(position, columns);

    return true;
}

bool medDatabaseItem::setData(int column, const QVariant& value)
{
    if (column < 0 || column >= d->itemData.size())
        return false;

    d->itemData[column] = value;

    return true;
}

QVariant medDatabaseItem::table(void)
{
    return d->table;
}

QVariant medDatabaseItem::attribute(int column)
{
    if(column > d->attrData.size())
        return QVariant();

    return d->attrData.at(column);
}

QVariant medDatabaseItem::value(int column)
{
    if(column > d->itemData.size())
        return QVariant();

    return d->itemData.at(column);
}