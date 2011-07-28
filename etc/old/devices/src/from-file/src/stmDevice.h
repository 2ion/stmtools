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

#define DEVICE_NAME ("from-file")
#define DEVICE_AUTHOR ("Jens Oliver John <jens.o.john@gmail.com>")
#define DEVICE_VERSION __DATE__
#define DEVICE_DESCR ("Generates data streams from diverse filetypes:\n\
- Image formats supported by QImage & CImg\n\
- Text files containing lists of sampled data.\n\
This device also is capable of reading data from a TCP-stream\n\
produced by the to-network device.")
#define DEVICE_PATH ("localhost")
#define SOFTWARE_DEV (devices::SDRIVER)
#define HARDWARE_DEV (devices::HDRIVER)


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
	bool txt_isValid(const QString &file);
private slots:
	void slot_ui_txt_openFile();
	void slot_ui_txt_writeToBuffer();

};

#endif /* stmDevice.h */
