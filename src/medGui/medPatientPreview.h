/* medPatientPreview.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct  8 19:44:38 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Oct  9 08:46:02 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef MEDPATIENTPREVIEW_H
#define MEDPATIENTPREVIEW_H

#include <QtGui>

class medPatientPreviewPrivate;

class medPatientPreview : public QWidget
{
    Q_OBJECT

public:
     medPatientPreview(QWidget *parent = 0);
    ~medPatientPreview(void);

    void setup(int patientId);

protected:
    void paintEvent(QPaintEvent *event);

private:
    medPatientPreviewPrivate *d;
};

#endif