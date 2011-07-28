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

#include "dsLWI.h"

dsLWI::dsLWI(devices::deviceID* deviceId) {
	if(deviceId != 0x00) {
		this->devId = deviceId;
		this->setText(this->devId->devName);
	}
}

dsLWI::~dsLWI() {
	//delete this->devId;
}

devices::deviceID* dsLWI::getDeviceId() {
	/* devices::deviceID id;
	id.devAuthor = new QString(*this->devId->devAuthor);
	id.devName = new QString(*this->devId->devName);
	id.devType = this->devId->devType;
	id.devVersion = new QString(*this->devId->devVersion);
	id.devPath = new QString(*this->devId->devPath);
	id.devDescription = new QString(*this->devId->devDescription);
	return id; */
	return this->devId;
}
