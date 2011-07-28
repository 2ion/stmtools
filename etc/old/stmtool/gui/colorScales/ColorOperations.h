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

#ifndef COLOROPERATIONS_H_
#define COLOROPERATIONS_H_

#include <QtGlobal>
#include <QtGui/QColor>
#include <QtCore/QList>
#include <QtCore/QHash>

#define INVERT_RGBA(color) QColor(255 - (color).red(),255 - (color).green(), 255 - (color).blue(), 255 - (color).alpha())
#define INVERT_RGB(color) QColor(255 - (color).red(),255 - (color).green(), 255 - (color).blue())

class ColorOperations {
public:
	enum mixAlgorithmus {
		ARITHMETISCHES_MITTEL,
		HARMONISCHES_MITTEL
	};

	enum rgbColors {
		RED, GREEN, BLUE
	};

	enum adjustmentLevel {
		AGGRESSIVE,
		MODERATE,
		FINE
	};

	enum adjustmentLevelModWords {
		END,
		BEGINNING
	};

	struct adjustmentLevelMod {
		enum adjustmentLevelModWords START;
	};

	QColor mix(const QList<QColor> &colors, enum mixAlgorithmus calculus)  {
		QColor result;
		return result;
	}

	QColor complement(const QColor &color)  {
		QColor result;
		return result;
	}

	static inline QColor invert(const QColor &color)  {
		QColor result;
		result.setHsv(360 - color.hue(),color.saturation(),color.value());
		return result;
	}

	/*!
	 * Takes a scale produced by ColorScale and adjusts the number of colors being held.
	 * @param colors If the specified number is equal to the size of scale, only a copy
	 * will be returned. Else, the resulting color scale will be of size colors.
	 * @param level This determines the adjustment algorithm and hence the complexity
	 * of the calculations.
	 * On level aggressive, the most primitive method will be used: starting in the middle
	 */
	QHash<quint32,QColor> adjustColorScale(const QHash<quint32,QColor> &scale,
			quint32 colors,
			enum adjustmentLevel level,
			struct adjustmentLevelMod *parameters)  {

	}

	QColor weightedComplement(const QColor &color)  {
		qint32 red = color.red();
		qint32 green = color.green();
		qint32 blue = color.blue();
		float average = (float) (red + green + blue) / 3.0;
		float dRed = average - red;
		float dGreen = average - green;
		float dBlue = average - blue;
		enum rgbColors toweight;
		if(dRed >= dGreen && dRed >= dBlue ) {
			toweight = RED;
		} else {
			if(dGreen >= dRed && dGreen >= dBlue) {
				toweight = GREEN;
			} else {
				toweight = BLUE;
			}
		}
		QColor to_return;
		switch (toweight) {
		case RED:
			to_return.setRed(255 - red);
			to_return.setGreen((255 - (int) red/dRed) - green);
			to_return.setBlue((255 - (int) red/dRed) - blue);
			return to_return;
			;
		case GREEN:
			to_return.setRed((255 - (int) green/dGreen) - red);
			to_return.setGreen(255 - green);
			to_return.setBlue((255 - (int) green/dGreen) - blue);
			return to_return;
		case BLUE:
			to_return.setRed((255 - (int) blue/dBlue) - red);
			to_return.setGreen((255 - (int) blue/dBlue) - green);
			to_return.setBlue(255 - blue);;
		}
		return to_return;
	}
};


#endif /* ColorOperations.h */
