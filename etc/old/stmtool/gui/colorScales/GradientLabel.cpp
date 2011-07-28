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

#include "GradientLabel.h"

GradientLabel::GradientLabel(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	//setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
	my_lineHeight = 1;
}

GradientLabel::~GradientLabel()
{

}

void GradientLabel::slot_displayScale(QHash<quint32,QColor> colors) {
	my_colors = colors;
	update();
}

void GradientLabel::paintEvent(QPaintEvent *event) {
	if(my_colors.size() != 0) {
		QPainter painter(this);
		QList<struct paintInstruction*> instructions;
		struct paintInstruction *stub = NULL;
		resize(size().width(),my_colors.size()*my_lineHeight);
		QHashIterator<quint32,QColor> colorIter(my_colors);
		while(colorIter.hasNext()) {
			colorIter.next();
			stub = new paintInstruction(
					colorIter.value(),
					(int)colorIter.key(),
					size().width(),
					my_lineHeight);
			instructions.append(stub);
		}
		QListIterator<struct paintInstruction*> iiter(instructions);
		while(iiter.hasNext()) {
			stub = iiter.next();
			painter.setPen(stub->aPen);
			painter.drawLine(stub->aLine);
		}
	}
}

void GradientLabel::slot_setLineHeight(int px) {
	my_lineHeight = px;
}
