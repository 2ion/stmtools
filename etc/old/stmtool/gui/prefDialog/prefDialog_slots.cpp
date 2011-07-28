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

#include "prefDialog.h"

void prefDialog::slot_apply() {
	this->saveSettings();
	this->loadSettings();

}

void prefDialog::slot_cancel() {
	this->close();
}

void prefDialog::slot_tbtn_devices() {
	this->ui.le_devices->setText(this->browseForADirectory());
}

void prefDialog::slot_tbtn_viewers() {
	this->ui.le_viewers->setText(this->browseForADirectory());
}

void prefDialog::slot_tbtn_logs() {
	this->ui.le_logs->setText(this->browseForADirectory());
}

void prefDialog::slot_tbtn_settings() {
	this->ui.le_logs->setText(this->browseForADirectory());
}
