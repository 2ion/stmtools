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

#ifndef CSVDISPLAYDOCK_H_
#define CSVDISPLAYDOCK_H_

#include <QtGui/QDockWidget>

/*!
 * \class CSVDisplayDock
 * \brief Used by ColorScaleViewer to display immediate information on
 * certain events.
 *
 * This widget has to be kept floating, if needed upon the desktop
 * to remind the user of his arbitrary input generation.
 * For example, the Gradient* helper classes of ColorScaleViewer provide
 * a possible data source.
 *
 * Data will be put in using the range of slots whose names are suffix to
 * slot_io.
 * In order to hide unneccessary data fields,
 *
 * \fn CSVDisplayDock::slot_displayColor(QColor,QString)
 * \brief Displays QColor along with a description QString.
 * \param color A color.
 * \param descr A description.
 * \param index The corresponding color scale index.
 *
 * If QString == "", no description label will be displayed.
 */

class CSVDisplayDock : public QDockWidget {
	Q_OBJECT
public:
	enum ioFlags {
		WITH_COMPLEMENT = 1 << 2
	};

	CSVDisplayDock();
	~CSVDisplayDock();
public slots:
	void slot_io_displayColor(QColor color,QString descr, int index);
};

#endif /* CSVDISPLAYDOCK_H_ */
