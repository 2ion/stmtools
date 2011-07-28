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

#ifndef IDEVICE_H_
#define IDEVICE_H_

// stmTool device interface
// joj@17.02.2010
#include <QtPlugin>
#include <QtGui>
#include <QtCore>
//#include "stmData.h"

namespace devices {
	typedef enum deviceType {
		SDRIVER,HDRIVER
	} deviceType;

	typedef struct {
	} deviceLimits;

	typedef struct deviceID {
		deviceType devType;
		/*
		QString* devName;
		QString* devVersion;
		QString* devAuthor;
		QString* devDescription;
		QString* devPath;
		*/
		QString devName;
		QString devVersion;
		QString devAuthor;
		QString devDescription;
		QString devPath;
		deviceLimits devLimits;
	} deviceID;

	typedef enum deviceStatus {
		NOTCALLED = -1,
		NOTREADY = -2,
		READY = 0,
		WORKING = 1,
		DOWN
	} deviceStatus;

	typedef struct deviceWidgets {
		QWidget* controllingWidget;
		QHash<QString*,QWidget*>* parametricWidgets; // <DESCRIPTION*,WIDGET*>
	} deviceWidgets;

	typedef enum bufferFormat {
		CHAR,
		UNSIGNED_INT,
		INT,
		FLOAT,
		DOUBLE
	} bufferFormat;

	typedef enum instruction {
		INIT,
		SHUTDOWN
	} instruction;

	typedef enum reply {
		OK,
		ERROR,
		MECH_ERROR,
		SOFT_ERROR,
		MEM_ERROR,
		REPETITIVE
	} reply;

	typedef struct buffer {
		devices::bufferFormat 	format;
		/*!
		 * Data format:
		 * ((quint32) X,(quint32) Y,(<T>) Z)
		 * where <T> will be interpreted after
		 * the value of format.
		 * @see bufferFormat
		 */
		QByteArray 		data;
		quint32			x_size;
		quint32			y_size;
		QDateTime		timeUpdated;
		QString 		bufferName;
		QString 		description;
	} buffer;

	typedef struct runningDevice {
		QList<devices::buffer*>* buffers;
		devices::deviceStatus status;
		devices::deviceID* id;
	} runningDevice;
}

class iDevice  {
public:
	// Responding methods
	virtual devices::deviceID* Id() = 0;
	virtual devices::deviceStatus status() = 0;
	// returns

	virtual devices::deviceWidgets* widgets() = 0;

	/*
	 * OBSOLETE
	virtual devices::bufferFormat bufferFormat() = 0;
	*/

	// Instructing methods
	virtual devices::reply instruct(devices::instruction instruction) = 0;

	// Discovering methods
	virtual QList<devices::buffer*>* buffer() = 0;
};

Q_DECLARE_INTERFACE(iDevice,"deviceInterface")

#endif /* IDEVICE_H_ */
