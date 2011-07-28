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

#ifndef COLORSCALE_KODAK1_H_
#define COLORSCALE_KODAK1_H_

/* interface */
#include <ColorScale.h>
#include <QtPlugin>


class colorScale_KODAK1 : public QObject, public ColorScale {
	Q_OBJECT
	Q_INTERFACES(ColorScale)
public:
	colorScale_KODAK1();
	~colorScale_KODAK1();

	/* interface */
	QHash<quint32,QColor> colors();
	QHash<quint32,QColor>* data();
	quint32 indizes();
	QString name();
private:
	void build(void);
	quint32 next_index;
	QHash<quint32,QColor> scale;
};

#endif /* colorScale_KODAK1.h */
