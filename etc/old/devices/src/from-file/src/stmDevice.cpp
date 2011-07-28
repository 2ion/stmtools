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

#include <QtGui>
#include "stmDevice.h"



devices::deviceID* stmDevice::Id() {
	devices::deviceID *stub = new devices::deviceID;
	stub->devName = QString(DEVICE_NAME);
	stub->devAuthor = QString(DEVICE_AUTHOR);
	stub->devVersion = QString(DEVICE_VERSION);
	stub->devDescription = QString(DEVICE_DESCR);
	stub->devPath = QString(DEVICE_PATH);
	stub->devType = SOFTWARE_DEV;
	return stub;
}

devices::deviceStatus stmDevice::status() {
	return f_status;
}

devices::deviceWidgets* stmDevice::widgets() {
	devices::deviceWidgets *dw = new devices::deviceWidgets;
	dw->controllingWidget = new ControllingWidget();
	dw->parametricWidgets = NULL;
	return dw;
}

/*
devices::bufferFormat stmDevice::bufferFormat() {

}
*/

devices::reply stmDevice::instruct(devices::instruction instruction) {
	using namespace devices;
	switch(instruction) {
	case INIT:
		f_status = READY;
		return OK;
		;
	case SHUTDOWN:
		f_status = DOWN;
		return OK;
		;
	default: break;;
	}
	return OK;
}

QList<devices::buffer*>* stmDevice::buffer() {
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////

bool stmDevice::txt_isValid(const QString &file) {

}

void stmDevice::slot_ui_txt_openFile() {

}

void stmDevice::slot_ui_txt_writeToBuffer() {

}

Q_EXPORT_PLUGIN2(from-file,stmDevice);
