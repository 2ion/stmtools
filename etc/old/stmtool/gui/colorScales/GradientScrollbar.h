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

#ifndef GRADIENTSCROLLBAR_H_
#define GRADIENTSCROLLBAR_H_

#include <QtGui/QScrollBar>
#include <QtGui/QFrame>
#include <QtGui/QPen>
#include <QtCore/QLine>
#include <QtGui/QColor>
#include <QtCore/QHash>
#include <QtCore/QHashIterator>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <cmath>


/*!
 * \class GradientScrollbar
 * \brief Upon which a gradient representation of a color scale is painted.
 * \see ColorScaleViewer
 *
 * This widget shall make the user's interaction with the color scale viewer/
 * editor easy; it can take mouse move events and display information on the
 * color the user has moved the cursor to, and thus adjust the list widget's
 * viewport.
 *
 * \todo Make it also a subclass of QFrame
 *
 * \fn void GradientScrollbar::slot_displayScale(QHash<quint32,QColor>)
 * \brief Whereto the data determined to be painted has to be delivered.
 *
 * \fn void GradientScrollbar::slot_setLineHeight(int)
 * \brief In the gradient representation, this is the height of a single line,
 * i.e. a line of a submitted color. If the specified value is less than 1,
 * it will default to 1, either.
 *
 *
 */

#ifndef GRADIENT_SCROLLBAR_LINEHEIGHT
#define GRADIENT_SCROLLBAR_LINEHEIGHT (1)
#endif

class GradientScrollbar : public QScrollBar {
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
			aLine.setLine(1,y,x,y);
		}
	};

	GradientScrollbar();
	~GradientScrollbar();
signals:
		void signal_outpointedColor(quint32 scale_index);
public slots:
		void slot_displayScale(QHash<quint32,QColor> colors);
		void slot_setLineHeight(int px);
protected:
		void paintEvent(QPaintEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
private:
		QHash<quint32,QColor> my_colors;
		int my_lineHeight;
		bool colors_dropped;
		QList<quint32> color_table;
};

#endif /* GRADIENTSCROLLBAR_H_ */
