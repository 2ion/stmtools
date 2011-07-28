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

#include "cwBoolean.h"

cwBoolean::cwBoolean(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	connect(this->ui.radioButton_true,
			SIGNAL(toggled(true)),
			this,
			SLOT(slot_toogle(bool)));
}

cwBoolean::~cwBoolean()
{

}

void cwBoolean::slot_toogle(bool value) {
	if (value) {
		emit this->signal_validValue(QVariant(true));
	} else {
		emit this->signal_validValue(QVariant(false));
	}
}
