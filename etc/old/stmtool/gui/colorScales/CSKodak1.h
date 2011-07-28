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

#ifndef CSKODAK1_H_
#define CSKODAK1_H_

/*!
 * \file CSKodak1.h
 * A color scale plugin.
 *
 * \class CSKodak1
 * \brief A built-in color scale.
 * \deprecated Has been exported to a color scale plugin; hence it will be removed soon
 * and should not be put into use.
 */

#include <QtPlugin>
#include <gui/colorScales/ColorScale.h>

class CSKodak1 : public ColorScale {
public:
	CSKodak1();
	~CSKodak1();

	// interface ColorScale
	QHash<quint32,QColor> colors();
	QHash<quint32,QColor>* data();
	quint32 indizes();

private:
	void build();
	QHash<quint32,QColor> scale;
};

#endif /* CSKodak1.h */
