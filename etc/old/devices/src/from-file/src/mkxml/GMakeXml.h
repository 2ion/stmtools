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

#ifndef GMAKEXML_H_
#define GMAKEXML_H_

/*!
 * \class GMakeXml
 * \brief Generic implementation of the MakeXml class.
 * \deprecated For I contemporaryly consider the generic approach an inadequate,
 * this stub may be removed soon.
 */

#include <Qt>
#include <QtGlobal>
#include <QtAlgorithms>
#include <QtDebug>
#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtGui/QImage>
#include <QtXml/QXmlStreamWriter>
#include <iDevice.h>
#include <stdlib.h>
#include <time.h>
#include <src/stmDevice.h>

#define ONESHIFTL(x) (1 << (x))
/*!
 * Produces a value addressed with (x,y) from a 2d-array.
 * pointer := pointer to 1st element of the array
 * x := column of value
 * y := line of value
 * columns := linewidth
 */
#define NARRAY_VAL(pointer,columns,x,y) *((pointer)+(x)+((y)*(columns)))

namespace mxml {
	enum ValueBase {
		Image,
		Random
	};

	enum PixelComponent {
		Raw,
		Red,
		Green,
		Blue,
		ArithmeticMean,
		HarmonicMean
	};

	struct ImageInput {
		QString source_image;
		qint32 anchor_x;
		qint32 anchor_y;
		bool flag_scale;
	};
}


class GMakeXml {
public:
	GMakeXml();
	~GMakeXml();
};


#endif /* GMAKEXML_H_ */
