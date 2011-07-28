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

#ifndef STMDEVICE_H_
#define STMDEVICE_H_

/*
 * libqt
 */
#include <QtCore/QObject>
/*
 * watch out: nesting inclusion!
 */
#include "stmDevice.h"
/*
 * interfaces
 */
#include <iDevice.h>
/*
 * specific implementation
 */
#include <src/widgets/ControllingWidget.h>
#include <src/widgets/PrimaryParametricWidget.h>

class stmDevice : public QObject, iDevice {
	Q_OBJECT
	Q_INTERFACES(iDevice)
public:
	/* interface methods */
	devices::deviceID* Id();
	devices::deviceStatus status();
	devices::deviceWidgets* widgets();
	//devices::bufferFormat bufferFormat();
	devices::reply instruct(devices::instruction instruction);
	QList<devices::buffer*>* buffer();
private:
	devices::deviceStatus f_status;
};

#endif /* stmDevice.h */
