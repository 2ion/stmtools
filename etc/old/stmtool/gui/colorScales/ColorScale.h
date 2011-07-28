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

#ifndef COLORSCALE_H_
#define COLORSCALE_H_

/*!
 * Abstract class for color scales
 */

#include <QtPlugin>
#include <QtGlobal>
#include <QtGui/QColor>
#include <QtCore/QHash>

/*
struct index_range {
	quint32 min;
	quint32 max;
};
*/

/*!
 * \file ColorScale.h
 * Contains the ColorScale interface.
 *
 * \class ColorScale
 * \brief The interface plugins can provide color scales
 * resp. their construction algorithm through.
 * \note As for every interface, you should assure that your class
 * returns always <EM>proper and significant</EM> values, i.e. pick
 * the name for your color scale thoughtfully.
 *
 * @see ColorScaleLoader
 */

class ColorScale {
public:
	/* access methods */
	/*!
	 * @return The entire scale, ready for usage, as Key-Value resp.
	 * index-color pairs.
	 * Remarks:
	 * <OL>
	 * <LI>
	 * a. an arbitrary quint32-value shall be I;<BR>
	 * In the scaling process, f(I) shall be the scaled value.<BR>
	 * It shall be that if I(1) > I(2), f(I(1)) > f(I(2)) holds true.<BR>
	 * </LI>
	 * <LI>
	 * stepwidth of indizes = 1.
	 * </LI>
	 * <LI>
	 * c. indizes start by zero.
	 * </LI>
	 */
	virtual QHash<quint32,QColor> colors() = 0;
	/*!
	 * @return The number of members.
	 */
	virtual quint32 indizes() = 0;

	/*!
	 * @return The actual data held by the object.
	 */
	virtual QHash<quint32,QColor>* data() = 0;
	/*!
	 * @return A GOOD name.
	 */
	virtual QString name() = 0;

};
Q_DECLARE_INTERFACE(ColorScale,"iColorScale")

#endif /* ColorScale.h */
