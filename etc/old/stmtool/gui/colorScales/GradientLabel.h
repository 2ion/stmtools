/*    
    stmtools - An ADE for practical Scanning Tunneling Microscopy
    Copyright (C) 2011 Jens Oliver John <jens.o.john@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GRADIENTLABEL_H
#define GRADIENTLABEL_H

#include <Qt>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QPen>
#include <QtCore/QLine>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtCore/QHash>
#include <QtCore/QHashIterator>
#include "ui_GradientLabel.h"

class GradientLabel : public QWidget {
		Q_OBJECT
public:
		struct paintInstruction {
			QPen aPen;
			QLine aLine;
			paintInstruction(const QColor aColor,
					int y,
					int x,
					int w) {
				aPen.setColor(aColor);
				aPen.setWidth(w);
				aLine.setLine(0,y,x,y);
			}
		};
		GradientLabel(QWidget *parent = 0);
		~GradientLabel();
public slots:
		void slot_displayScale(QHash<quint32,QColor> colors);
		void slot_setLineHeight(int px);
protected:
		void paintEvent(QPaintEvent *event);
private:
		Ui::GradientLabelClass ui;
		QHash<quint32,QColor> my_colors;
		int my_lineHeight;
};

#endif // GRADIENTLABEL_H
