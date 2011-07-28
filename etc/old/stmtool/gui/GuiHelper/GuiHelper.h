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

#ifndef GUIHELPER_H_
#define GUIHELPER_H_

/*!
 * \file GuiHelper.h
 * Implements GuiHelper.
 *
 * \class GuiHelper
 * \brief Provides GUI helpers via <CODE>const</CODE> member methods.
 */

#include <QtGui/QMessageBox>
#include <QtCore/QString>

class GuiHelper {
public:
	GuiHelper();
	~GuiHelper();

	static bool askForBoolean(const QString &windowTitle,
			const QString &text)  {
		QMessageBox::StandardButton btn = QMessageBox::question(NULL,
				windowTitle,
				text,
				QMessageBox::Yes | QMessageBox::No);
		switch(btn) {
		case QMessageBox::Yes:
			return true;
		;
		case QMessageBox::No:
			return false;
			;
		}
		return false;
	}
};

#endif /* GUIHELPER_H_ */
