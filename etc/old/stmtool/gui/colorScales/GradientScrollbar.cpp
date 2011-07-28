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

#include "GradientScrollbar.h"

GradientScrollbar::GradientScrollbar() {
	my_lineHeight = 1;
	colors_dropped = false;
	setMouseTracking(true);
}

GradientScrollbar::~GradientScrollbar() {
}

void GradientScrollbar::slot_displayScale(QHash<quint32,QColor> colors) {
	my_colors = colors;
	update();
}

void GradientScrollbar::slot_setLineHeight(int px) {
	my_lineHeight = px >= 1 ? px : GRADIENT_SCROLLBAR_LINEHEIGHT;
}

void GradientScrollbar::paintEvent(QPaintEvent *event) {
	if(my_colors.size() != 0) {
		QPainter painter(this);
		QList<struct paintInstruction*> instructions;
		struct paintInstruction *stub = NULL;

		if(my_colors.size()*my_lineHeight > size().height()) {
			color_table.clear();
			colors_dropped = true;
			int stepwidth = (int) std::ceil((double)(my_colors.size()*my_lineHeight)/(double) size().height());
			QList<quint32> targets = my_colors.keys();
			for(int index,line = 0; index < targets.size(); index = index + stepwidth) {
				stub = new paintInstruction(
						my_colors.value((quint32)index),
						line++,
						size().width()-1,
						my_lineHeight);
				instructions.append(stub);
				color_table.append(index);
			}
		} else {
			colors_dropped = false;
			QHashIterator<quint32,QColor> colorIter(my_colors);
			while(colorIter.hasNext()) {
				colorIter.next();
				stub = new paintInstruction(
						colorIter.value(),
						(int)colorIter.key(),
						size().width()-1,
						my_lineHeight);
				instructions.append(stub);
			}
			for(int fLine = my_lineHeight*my_colors.size(); fLine < size().height(); ++fLine) {
				stub = new paintInstruction(
						fLine,
						Qt::white,
						size().width()-1,
						1);
				instructions.append(stub);
			}
		}

		QListIterator<struct paintInstruction*> iiter(instructions);
		while(iiter.hasNext()) {
			stub = iiter.next();
			painter.setPen(stub->aPen);
			painter.drawLine(stub->aLine);
		}
	} else {
		QList<struct paintInstruction*> instr;
		for(int y1 = 0; y1 < size().height(); ++y1) {
			instr.append(new struct paintInstruction(
					y1,
					Qt::white,
					size().width()-1,
					1));
		}
		QPainter aPainter(this);
		QListIterator<struct paintInstruction*> anIter(instr);
		while(anIter.hasNext()) {
			struct paintInstruction *aStub = anIter.next();
			aPainter.setPen(aStub->aPen);
			aPainter.drawLine(aStub->aLine);
		}
	}
}

void GradientScrollbar::mouseMoveEvent(QMouseEvent *event) {
	// determine index of color
	/*! \todo Is this if disposable?*/
	if(my_colors.size() == 0)
		return;
	quint32 index = colors_dropped ? color_table.value(event->pos().y()) : (quint32) event->pos().y();
	emit signal_outpointedColor(index);
}

