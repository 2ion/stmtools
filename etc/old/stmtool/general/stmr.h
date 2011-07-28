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

#ifndef STMR_H_
#define STMR_H_

/*!
 * \class stmr
 * \brief A dying attempt to implement some low-level
 * convenience methods.
 *
 * \deprecated It will vanish. Surely.
 */

#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <cstdarg>

class stmr {
public:
	static bool dirExists(QString path) {
		QDir* tmp = new QDir(path);
		return tmp->exists() ? true : false;
	}

	// returns true, if {all given pointers} != NULL. the sequence has to be terminated by a pointer == 1
	static bool allPoint(void* null, ...) {
		quintptr pointer = 0x00;
		va_list argl;
		va_start(argl,2);
		while (pointer != 1) {
			pointer = va_arg(argl,quintptr);
			if(pointer == 0x00) {
				return false;
			}
		}
		va_end(argl);
		return true;
	}



};


#endif /* STMR_H_ */
